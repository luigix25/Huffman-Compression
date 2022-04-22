#pragma once
#include "util.h"

class Encode{
    private:
        huffman_map encoding;
        const string plaintext;

        my_queue count_occurencies();
        void generate_huffmann_code(my_queue &occorrenze);
        
        //Util
        void get_codes_tree_and_free(leaf *node, const string &code);
        void print_queue(my_queue sorted);

    public:
        Encode(const string &plain): plaintext(plain){
            my_queue occourencies = count_occurencies();
            generate_huffmann_code(occourencies);
        }

        huffman_map getHuffmanCode(){
            return encoding;
        }

        string getEncoding();
        Data getEncodingBinary();

};
