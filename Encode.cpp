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

    Data d;
    d.length = str_length/8;

    if((str_length % 8) != 0)
        d.length++;
    
    d.data = new uint8_t[d.length];
    uint32_t index = 0;
    uint8_t *ptr = &d.data[0];

    while(index < str_length){
        if(str_length - index < 8){ //TODO: ultima iterazione
            std::cout<<"ultima iterzione"<<std::endl;
            break;
        }

        *ptr = bitset<8>(encoded,index,8).to_ulong();
        ptr++;
        index += 8;
        
    }

    return d;
    
}

my_queue Encode::count_occurencies(){

    my_map dictionary(21); //already initialized to 0

    for (const char &c: plaintext) {
        dictionary[c]++;
    }

    my_queue sorted;

    //TODO: sta roba fa trashing

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
    if(node == NULL)
        return;

    if(node->left == NULL && node->right == NULL){
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