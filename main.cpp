#include <iostream>
#include <fstream>
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
    leaf(TIPO_1 key, TIPO_2 value) : left(NULL), right(NULL),key(key),value(value){}
//    leaf(my_pair p) : left(NULL), right(NULL),key(p.first),value(p.second){}
    leaf(TIPO_1 key, TIPO_2 value, leaf *left, leaf *right) : left(left), right(right),key(key),value(value){}

};

class Compare
{
public:
    bool operator() (leaf uno, leaf due)
    {
        if(uno.value < due.value)
            return true;
        return false;
    }
};



typedef priority_queue<leaf,vector<leaf>,Compare> my_queue;
void print_queue(my_queue coda);

my_queue count_occurencies(string str);
unordered_map<TIPO_1,TIPO_2> huffmann_code(my_queue occorrenze);


int main(){

    ifstream file("lorem.txt");
    string line;
    if (!file.is_open()){
        cout<<"errore";
        return -1;
    }

    getline (file,line);
    file.close();

    my_queue occorrenze = count_occurencies(line);

    unordered_map<TIPO_1,TIPO_2> codice = huffmann_code(occorrenze); 
    

}


unordered_map<TIPO_1,TIPO_2> huffmann_code(my_queue occorrenze){

    while(occorrenze.size() > 1){
        leaf uno = occorrenze.top();
        occorrenze.pop();
        leaf due = occorrenze.top();
        occorrenze.pop();

        leaf parent;

        parent.left = &uno;
        parent.right = &due;
        parent.value = uno.value + due.value;

        occorrenze.push(parent);

        //cout<<"n: "<<occorrenze.size()<<endl;
    }

    leaf root = occorrenze.top();


    unordered_map<TIPO_1,TIPO_2> a;
    return a;

}


my_queue count_occurencies(string str){

    unordered_map<TIPO_1,TIPO_2> dictionary(21); //init to 0

    for (const char &c: str) {
        dictionary[c]++;
    }

    //TODO: sta roba fa trashing
    my_queue sorted;

    for (auto &e: dictionary) {
        sorted.push(leaf(e.first,e.second));
    }

    print_queue(sorted);

    return sorted;

}

void print_queue(my_queue sorted){

    while (!sorted.empty()){
        leaf p = sorted.top();
        cout<<p.key<<" '"<<p.value<<"'"<<endl;
        sorted.pop();
    }

}