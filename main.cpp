#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <unordered_map>

using namespace std;

#define TIPO_1 char
#define TIPO_2 uint16_t

vector<pair<TIPO_1,TIPO_2>> count_occurencies(string str);

int main(){

    ifstream file("lorem.txt");
    string line;
    if (!file.is_open()){
        cout<<"errore";
        return -1;
    }

    getline (file,line);

    count_occurencies(line);

    file.close();
    

}

bool cmp(pair<TIPO_1, TIPO_2> uno, pair<TIPO_1, TIPO_2> due){

    if(uno.second > due.second)
        return true;
    
    return false;

}

vector<pair<TIPO_1,TIPO_2>> count_occurencies(string str){

    unordered_map<TIPO_1,TIPO_2> dictionary(21); //init to 0

    for (const char &c: str) {
        dictionary[c]++;
    }

    vector<pair<TIPO_1,TIPO_2>> sorted(21);

    for (auto &e: dictionary) {
        pair<TIPO_1,TIPO_2> p(e.first,e.second);
        sorted.push_back(p);
        cout << '{' << e.first << ", " << e.second << '}' << endl;
    }

    cout<<"-----------------"<<endl;


    sort(sorted.begin(),sorted.end(),cmp);

    for (auto &e: sorted) {
        cout << '{' << e.first << ", " << e.second << '}' << endl;
    }

    return sorted;

}