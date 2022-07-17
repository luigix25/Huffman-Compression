#include "util.h"
string numberToBitString(uint64_t number, uint64_t n_bits){
    n_bits--;

    uint64_t mask = 1<<n_bits;

        string s;

        while(mask != 0){
                if(((number & mask) >> n_bits))
                        s+="1";
                else
                        s+="0";
                n_bits--;
                mask = mask >> 1;
        }
    return s;
}