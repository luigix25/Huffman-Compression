#include "Encode.h"

string Encode::encode(){
    string encoded;

    for(char c: plaintext){
        encoded += code[c];
    }

    return encoded;

}

my_queue Encode::countOccurencies(){

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