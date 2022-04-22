#pragma once
#include "util.h"

class Encode{
    private:
        huffman_map code;
        const string plaintext;

        my_queue countOccurencies();

    public:
        Encode(const string &plain): plaintext(plain){}        
        string encode();

};
