#include <iostream>
#include <string>
#include <fstream>

using namespace std;

class Trie {
public:
    Trie* deca[27];
    bool zbor;
    Trie () {
        for (int i=0; i<27; i++) {
        deca[i]=nullptr;
        }
        zbor=false;
    }
};
void insert (Trie* root, string a) {
    for (int i=0; i<a.size(); i++) {
        if (isalpha(a[i])==0) {
            if (root->deca[0]==nullptr) {
                Trie* tmp= new Trie();
                root->deca[0]=tmp;
                root=tmp;
            }
            else root=root->deca[0];
        }
        else {
            if (root->deca[tolower(a[i])-'a'+1]==nullptr) {
                Trie* tmp=new Trie();
                root->deca[tolower(a[i])-'a'+1]=tmp;
                root=tmp;
            }
            else root=root->deca[tolower(a[i])-'a'+1];
        }
    }
    root->zbor=true;
}
bool prebaraj (Trie* root, string a) {
    for (int i=0; i<a.size(); i++) {
        if (isalpha(a[i])==0) {
            if (root->deca[0]!=nullptr) {
                root=root->deca[0];
            }
            else return false;
        }
        else if (root->deca[tolower(a[i])-'a'+1]!=nullptr) {
            root=root->deca[tolower(a[i])-'a'+1];
        }
        else return false;
    }
    if (root->zbor==false) { return false; }
    return true;
}
int main () {
    Trie* a= new Trie;
    ifstream in ("wiki-100k.txt");
    int zborovi=0;
    while (1) {
        string line;
        getline(in, line);
        if (line[0]=='#') { continue; }
        insert(a,line);
        cout<<line<<endl;
        zborovi++;
        if (zborovi==10000) { break; }
    }
}