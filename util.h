#pragma once
#include <queue>
#include <vector>
#include <unordered_map>

using namespace std;

#define TIPO_1 char
#define TIPO_2 uint16_t

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
    uint32_t length;
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

typedef priority_queue<leaf*,vector<leaf*>,Compare> my_queue;
typedef unordered_map<TIPO_1,TIPO_2> my_map;

typedef unordered_map<char,string> huffman_map;
typedef unordered_map<string,char> huffman_map_inverted;