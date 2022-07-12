#include <iostream>
#include <fstream>
#include <sstream>
#include <filesystem>
#include <bitset>

#include "Encode.h"
#include "Decode.h"

int main(){

    ifstream file("lorem.txt");
    string line;
    if (!file.is_open()){
        cout<<"errore";
        return -1;
    }

    getline (file,line);
    file.close();

    Encode enc(line);
    string encoded = enc.getEncoding();

    ofstream out("encoded.txt",ios::binary);

    Data d = enc.getEncodingBinary();

    for(uint32_t i=0;i<d.length;i++){
        out<<d.data[i];
    }

    out.close();

    line.clear();

    file = ifstream("encoded.txt",ios::binary);
    stringstream buffer;
    buffer << file.rdbuf();
    line = buffer.str();
    
    file.close();

    encoded.clear();

    for(char c: line){
        bitset<8> bit((uint8_t)c);
        //cout<<bit<<endl;
        encoded += bit.to_string();   
    }


    Decode dec(enc.getHuffmanCode(),encoded);

    string decoded = dec.getDecoded();

    cout<<decoded<<endl;

}



