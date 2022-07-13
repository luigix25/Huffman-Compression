#pragma once
#include "util.h"

class Decode{
    private:
        huffman_map_inverted encoding;
        const string encoded;

        size_t min_length_code;
        size_t max_length_code;

        uint32_t padding;

    public:
        Decode(huffman_map &code,const string &encoded, uint32_t padding);

        string getDecoded();

};
