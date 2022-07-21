#pragma once
#include "util.h"
using namespace std;

class Encode{
    private:
        huffman_map encoding;
        vector<my_pair> vector_encoding_length;

        const string plaintext;
        uint8_t padding;

        my_queue count_occurencies();
        void generate_huffmann_code(my_queue &occorrenze);
        void generate_huffman_canonical();
        
        //Util
        void get_encoding_length_and_free(leaf *node, uint64_t);
        void print_queue(my_queue sorted);

    public:
        Encode(const string &plain): plaintext(plain){
            my_queue occourencies = count_occurencies();
            generate_huffmann_code(occourencies);
        }

        huffman_map getHuffmanCode(){
            return encoding;
        }

        vector<my_pair> getEncodingLengths(){
            return vector_encoding_length;
        }        

        uint8_t getPadding(){
            return padding;
        }

        string getEncoding();
        Data getEncodingBinary();

};

bool comparePair(my_pair i1, my_pair i2);
