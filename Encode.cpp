#include "Encode.h"
#include <bitset>
#include <iostream>

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
    uint8_t padding = 0;

    //Encoded text is not multiple of 8 bits
    if((str_length % 8) != 0){
        padding = 8 - (str_length % 8);
        for(int i=0;i<padding;i++)
            encoded += "0";
    }

    const uint32_t padded_str_length = encoded.length();

    Data d(padded_str_length/8);

    uint32_t index = 0;
    uint8_t *ptr = &d.data[0];

    while(index < padded_str_length){
        *ptr = bitset<8>(encoded,index,8).to_ulong();
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

    get_codes_tree_and_free(root,string());

}

void Encode::get_codes_tree_and_free(leaf *node, const string &code){
    if(node == nullptr)
        return;

    if(node->left == nullptr && node->right == nullptr){
        this->encoding[node->key] = code;
        delete node;
        return;
    }

    get_codes_tree_and_free(node->left,code +"0");
    get_codes_tree_and_free(node->right,code +"1");

    delete node;

}

void Encode::print_queue(my_queue sorted){

    while (!sorted.empty()){
        leaf *p = sorted.top();
        cout<<p->key<<" '"<<p->value<<"'"<<endl;
        sorted.pop();
    }
}