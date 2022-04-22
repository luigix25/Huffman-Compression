#include <iostream>
#include <fstream>
#include <bitset>
#include <filesystem>

#include "Encode.h"


void print_queue(my_queue coda);
string decode(const huffman_map &code,const string &encoded);

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

   
    uint8_t to_write;
    
    uint32_t index = 0;
    const uint32_t str_length = encoded.length();

    while(index < str_length){
        if(str_length - index < 8){ //TODO: ultima iterazione
            cout<<"ultima iterzione"<<endl;
            break;
        }

        to_write = bitset<8>(encoded,index,8).to_ulong();
        out<<to_write;
        index += 8;
        
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

    string decoded = decode(enc.getHuffmanCode(),encoded);

    cout<<decoded<<endl;

}




string decode(const huffman_map &code,const string &encoded){
    
    huffman_map_inverted code_inverted;
    size_t max_length = 0;


    for(const auto p : code){
        code_inverted[p.second] = p.first; 
        size_t dim = p.second.length();
        if(dim > max_length)
            max_length = dim;
    }

    string decoded;
    uint32_t index = 0;

    while(index < encoded.length()) {
        uint32_t i;
        for(i=1; i < max_length+1; i++){

            auto search = code_inverted.find(encoded.substr(index,i));
            
            if(search != code_inverted.end()){
                decoded += search->second;
                index += search->first.length();
                break;
            }
        }

        if(i==max_length+1){
            cout<<"something went terribly wrong"<<endl;
            exit(-1);
        }
    }
    
   return decoded;
}



void print_queue(my_queue sorted){

    while (!sorted.empty()){
        leaf *p = sorted.top();
        cout<<p->key<<" '"<<p->value<<"'"<<endl;
        sorted.pop();
    }

}