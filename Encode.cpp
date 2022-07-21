#include "Encode.h"
#include <algorithm>
#include <iostream>
#include <bitset>

bool comparePair(my_pair i1, my_pair i2){
    if(i1.second < i2.second)
        return true;
    else if(i1.second == i2.second){
        return i1.first < i2.first;
    }
    return false;
}

string Encode::getEncoding(){
    string encoded;

    for(char c: plaintext){
        encoded += this->encoding[c];
    }

    return encoded;

}

Data Encode::getEncodingBinary(){
    string encoded;

    for(char c: plaintext){
        encoded += this->encoding[c];
    }

    const uint32_t str_length = encoded.length();
    this->padding = 0;

    //Encoded text is not multiple of 8 bits
    if((str_length % 8) != 0){
        this->padding = 8 - (str_length % 8);
        for(uint32_t i=0;i<padding;i++)
            encoded += "0";
    }

    const uint32_t padded_str_length = encoded.length();

    Data d(padded_str_length/8);

    uint32_t index = 0;
    uint8_t *ptr = &d.data[0];

    while(index < padded_str_length){
        *ptr = (uint8_t)bitset<8>(encoded,index,8).to_ulong();
        ptr++;
        index += 8;        
    }

    return d;
    
}

my_queue Encode::count_occurencies(){

    my_map dictionary(256); //already initialized to 0; 255 for 8 bit

    for (const char &c: plaintext) {
        dictionary[c]++;
    }

    my_queue sorted;

    for (auto &e: dictionary) {
        leaf *f = new leaf(e.first,e.second);
        sorted.push(f);
    }

    return sorted;

}

void Encode::generate_huffmann_code(my_queue &occorrenze){

    while(occorrenze.size() > 1){
        leaf *uno = occorrenze.top();
        occorrenze.pop();
        
        leaf *due = occorrenze.top();
        occorrenze.pop();

        leaf *parent = new leaf;

        parent->left = uno;
        parent->right = due;
        parent->value = uno->value + due->value;

        occorrenze.push(parent);
    }

    leaf *root = occorrenze.top();
    occorrenze.pop();

    get_encoding_length_and_free(root,0);
    generate_huffman_canonical();
}

void Encode::generate_huffman_canonical(){
    
    sort(this->vector_encoding_length.begin(), this->vector_encoding_length.end(), comparePair);
    uint64_t counter =0;
    uint64_t old_bitlen = vector_encoding_length[0].second;

    for (const auto &x : this->vector_encoding_length){
        //first increment then shift to the left
        counter = counter << (x.second - old_bitlen);
        this->encoding[x.first] = numberToBitString(counter,x.second);
        counter = (counter + 1);
        old_bitlen = x.second;
    }

}

void Encode::get_encoding_length_and_free(leaf *node, uint64_t length){
    if(node == nullptr)
        return;

    if(node->left == nullptr && node->right == nullptr){
        my_pair p(node->key,length);
        this->vector_encoding_length.push_back(p);
        delete node;
        return;
    }

    get_encoding_length_and_free(node->left,length+1);
    get_encoding_length_and_free(node->right,length+1);

    delete node;

}

void Encode::print_queue(my_queue sorted){

    while (!sorted.empty()){
        leaf *p = sorted.top();
        cout<<p->key<<" '"<<p->value<<"'"<<endl;
        sorted.pop();
    }
}