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

int32_t compress(const char *,const char *,const char *);
int32_t extract(const char *,const char *,const char *);

int main(int argc, const char **argv){

    if(argc < 5){
        cout<<"usage: infile outfile codefile [c/x]"<<endl;
        return -1;
    }
   
    const char *in_filename = argv[1];
    const char *out_filename = argv[2];
    const char *code_filename = argv[3];

    const char c = *(argv[4]);

    if(c == 'c'){
        return compress(in_filename,code_filename,out_filename);
    } else if(c=='x'){
        return extract(in_filename,code_filename,out_filename);
    } else {
        cout<<"Wrong Parameter"<<endl;
        return -1;
    }

}

int32_t compress(const char *filename, const char *code_filename,const char *out_filename){

    int32_t fd = open(filename, O_RDONLY);
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
    int32_t ret_val = munmap((void*)in_buffer,fsize);
    if(ret_val != 0){
        cout<<"error munmap "<<errno<<endl;
        return errno;
    }

    Encode enc(plaintext);
    //Write the encoded string to the file
    ofstream out(out_filename,ios::binary);
    Data d = enc.getEncodingBinary();
    
    for(uint32_t i=0;i<d.length;i++){
        out<<d.data[i];
    }

    out.close();
    
    //writing encoding infos
    vector<my_pair> code = enc.getEncodingLengths();

    //writing info (in binary) for recostruting huffman tree: first padding, then bitlength

    ofstream out_enc(code_filename,ios::binary);
    uint8_t padding = enc.getPadding();
    out_enc.write((const char*)&padding,sizeof(padding));

    for(const auto &pair : code){
        out_enc.write((const char*)&pair.second,sizeof(pair.second));
    }

    out_enc.close();
    return 0;

}

int32_t extract(const char *filename, const char *code_filename,const char *out_filename){
    int32_t fd = open(filename, O_RDONLY); //compressed file
    if(fd < 0 ){
        cout<<"fd < 0"<<endl;
        return fd;
    }

    off_t fsize = lseek(fd, 0, SEEK_END);
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
    int32_t ret_val = munmap((void*)out_buffer,fsize);
    if(ret_val != 0){
        cout<<"error munmap "<<errno<<endl;
        return errno;
    }

    string encoded;

    for(char c: encoded_text){
        bitset<8> bit((uint8_t)c);
        encoded += bit.to_string();   
    }

    ifstream encoding_file(code_filename,ios::binary);

    uint8_t padding;
    encoding_file.read((char*)&padding,sizeof(padding));

    vector<my_pair> v;
    for(uint16_t i=0;i<256;i++){
        my_pair p;
        p.first = i;
        encoding_file.read((char*)&p.second,sizeof(p.second));

        v.push_back(p);
    }


    encoding_file.close();

    Decode dec(v,encoded,padding);

    string decoded = dec.getDecoded();

    ofstream of(out_filename,ios::out);
    of<<decoded;
    of.close();

    return 0;
}