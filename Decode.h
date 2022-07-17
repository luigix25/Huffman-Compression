#pragma once
#include "util.h"

class Decode{
    private:
        vector<my_pair> vector_encoding_length;

        const string encoded;

        size_t min_length_code;
        size_t max_length_code;

        uint32_t padding;

        huffman_map_inverted encoding;

        void generate_huffman_coding();

    public:
        Decode(const vector<my_pair> &vector_encoding_length,const string &encoded, uint32_t padding);

        string getDecoded();

};
