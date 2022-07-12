#include <iostream>
#include <fstream>
#include <sstream>
#include <filesystem>
#include <bitset>

#include <sys/mman.h>
#include <fcntl.h>
#include <unistd.h>

#include "Encode.h"
#include "Decode.h"

int main(int argc, const char **argv){

    if(argc < 3){
        cout<<"usage: infile outfile"<<endl;
        return -1;
    }
   
    const char *in_filename = argv[1];
    const char *out_filename = argv[2];

    int32_t fd = open(in_filename, O_RDONLY);
    if(fd < 0 ){
        cout<<"fd < 0"<<endl;
        return fd;
    }

    off_t fsize = lseek(fd, 0, SEEK_END);
    if(fsize == -1){
        cout<<"errore fsize "<<errno<<endl;
        return errno;
    }

    const char *in_buffer = (const char *)mmap(NULL, (size_t)fsize, PROT_READ, MAP_PRIVATE, fd, 0);
    if(in_buffer == NULL){
        cout<<"errore mmap "<<errno<<endl;
        return errno;
    }
    
    fd = close(fd);
    if(fd < 0){
        cout<<"errore close "<<errno<<endl;
        return errno;
    }

    string plaintext(in_buffer,fsize);
    munmap((void*)in_buffer,fsize);

    Encode enc(plaintext);

    //Write the encoded string to the file
    ofstream out(out_filename,ios::binary);

    Data d = enc.getEncodingBinary();

    for(uint32_t i=0;i<d.length;i++){
        out<<d.data[i];
    }

    out.close();

    //LETTURA E DECODIFICA

    fd = open(out_filename, O_RDONLY);
    if(fd < 0 ){
        cout<<"fd < 0"<<endl;
        return fd;
    }

    fsize = lseek(fd, 0, SEEK_END);
    if(fsize == -1){
        cout<<"errore fsize "<<errno<<endl;
        return errno;
    }

    const char *out_buffer = (const char *)mmap(NULL, (size_t)fsize, PROT_READ, MAP_PRIVATE, fd, 0);
    if(out_buffer == NULL){
        cout<<"errore mmap "<<errno<<endl;
        return errno;
    }
    
    fd = close(fd);
    if(fd < 0){
        cout<<"errore close "<<errno<<endl;
        return errno;
    }

    string encoded_text(out_buffer,fsize);
    munmap((void*)out_buffer,fsize);

    string encoded;

    for(char c: encoded_text){
        bitset<8> bit((uint8_t)c);
        encoded += bit.to_string();   
    }


    Decode dec(enc.getHuffmanCode(),encoded,enc.getPadding());

    string decoded = dec.getDecoded();

    cout<<decoded<<endl;

}



