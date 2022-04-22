#include "Encode.h"

string Encode::getEncoding(){
    string encoded;

    for(char c: plaintext){
        encoded += this->encoding[c];
    }

    return encoded;

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