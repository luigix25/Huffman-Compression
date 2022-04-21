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
    leaf(TIPO_1 key, TIPO_2 value, leaf *left, leaf *right) : left(left), right(right),key(key),value(value){}

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

void print_queue(my_queue coda);
string decode(const huffman_map &code,const string &encoded);

my_queue count_occurencies(string str);
huffman_map huffmann_code(my_queue occorrenze);


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
    huffman_map codice = huffmann_code(occorrenze); 
    
    for (auto pair: codice) {
		cout << pair.first << " " << pair.second << '\n';
	}

    string encoded;
    int conta =0;
    for(char c: line){
        encoded += codice[c];
    } 

    //cout<<encoded<<endl;

    string decoded = decode(codice,encoded);

    cout<<decoded<<endl;

}

string decode(const huffman_map &code,const string &encoded){
    
    huffman_map_inverted code_inverted;
    size_t max_length = 0;


    for(const auto p : code){
        code_inverted[p.second] = p.first; 
        size_t dim = p.second.length();
        if(dim > max_length)
            max_length = dim;
    }

    string decoded;
    uint32_t index = 0;

    while(index < encoded.length()) {
        for(uint32_t i=1; i < max_length+1; i++){

            auto search = code_inverted.find(encoded.substr(index,i));
            
            if(search != code_inverted.end()){
                decoded += search->second;
                index += search->first.length();
                break;
            }
        }
    }
    
   return decoded;
}

void visit_tree(leaf *node,string code, huffman_map &codes){
    if(node == NULL)
        return;

    if(node->left == NULL && node->right == NULL){
        //cout<<"'"<<node->key<<"': ";
        //cout<<code<<endl;
        codes[node->key] = code;
        return;
    }

    visit_tree(node->left,code +"0",codes);
    visit_tree(node->right,code +"1",codes);

}

huffman_map huffmann_code(my_queue occorrenze){

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
    string empty;

    huffman_map return_map;

    visit_tree(root,empty,return_map);

    return return_map;

}


my_queue count_occurencies(string str){

    my_map dictionary(21); //init to 0

    for (const char &c: str) {
        dictionary[c]++;
    }

    //TODO: sta roba fa trashing
    my_queue sorted;

    for (auto &e: dictionary) {
        leaf *f = new leaf(e.first,e.second);
        sorted.push(f);
    }


    //print_queue(sorted);

    return sorted;

}

void print_queue(my_queue sorted){

    while (!sorted.empty()){
        leaf *p = sorted.top();
        cout<<p->key<<" '"<<p->value<<"'"<<endl;
        sorted.pop();
    }

}