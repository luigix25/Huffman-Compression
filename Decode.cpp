#include "Decode.h"
#include <iostream>

Decode::Decode(const vector<my_pair> &vector_encoding_length,const string &encoded, uint32_t padding):vector_encoding_length(vector_encoding_length),encoded(encoded),padding(padding){

    generate_huffman_coding();

    max_length_code = 0;
    min_length_code = SIZE_MAX;

    for(const auto &p : this->encoding){
        size_t dim = p.first.length();
        if(dim > this->max_length_code)
            this->max_length_code = dim;
        if(dim < this->min_length_code)
            this->min_length_code = dim;
    }

}

void Decode::generate_huffman_coding(){

    uint64_t counter =0;
    uint64_t old_bitlen = vector_encoding_length[0].second;

    for (const auto &x : this->vector_encoding_length){
        //first increment then shift to the left
        counter = counter << (x.second - old_bitlen);
        this->encoding[numberToBitString(counter,x.second)] = x.first;
        counter = (counter + 1);
        old_bitlen = x.second;
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
