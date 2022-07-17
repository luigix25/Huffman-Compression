#pragma once

#include <queue>
#include <vector>
#include <unordered_map>
#include <string>

using namespace std;

#define TIPO_1 char
#define TIPO_2 uint64_t

struct leaf{
    TIPO_1 key;
    TIPO_2 value;
    leaf *left, *right;
    leaf(){}
    leaf(TIPO_1 key, TIPO_2 value) : key(key),value(value),left(NULL), right(NULL){}
    leaf(TIPO_1 key, TIPO_2 value, leaf *left, leaf *right) : key(key),value(value),left(left), right(right){}

};

struct Data{
    uint8_t *data;
    const uint32_t length;
    Data(uint32_t length) : length(length){
        this->data = new uint8_t[length];
    }
    ~Data(){
        delete[] data;
    }
};

class Compare
{
    public:
        bool operator() (leaf *uno, leaf *due)
        {
            if(uno->value > due->value)
                return true;
            return false;
        }
};

string numberToBitString(uint64_t number, uint64_t n_bits);
typedef priority_queue<leaf*,vector<leaf*>,Compare> my_queue;
typedef unordered_map<TIPO_1,TIPO_2> my_map;

typedef pair<unsigned char,uint64_t> my_pair;

typedef unordered_map<char,string> huffman_map;
typedef unordered_map<string,char> huffman_map_inverted;