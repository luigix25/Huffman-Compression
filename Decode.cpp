#include "Decode.h"
#include <iostream>

Decode::Decode(huffman_map &code,const string &encoded, uint32_t padding):encoded(encoded),padding(padding){

    max_length_code = 0;
    min_length_code = SIZE_MAX;

    for(const auto &p : code){
        this->encoding[p.second] = p.first; 
        size_t dim = p.second.length();
        if(dim > this->max_length_code)
            this->max_length_code = dim;
        if(dim < this->min_length_code)
            this->min_length_code = dim;
    }

}

string Decode::getDecoded(){

    uint32_t index = 0;
    const uint32_t str_length = encoded.length() - padding;

    string decoded;

    while(index < str_length) {
        uint32_t i;
        for(i=this->min_length_code; i < this->max_length_code+1; i++){

            auto search = this->encoding.find(encoded.substr(index,i));
            
            if(search != this->encoding.end()){
                decoded += search->second;
                index += search->first.length();
                break;
            }
        }

        if(i==max_length_code+1){
            std::cout<<"something went terribly wrong"<<std::endl;
            exit(-1);
        }
    }

    return decoded;

}
