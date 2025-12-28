#include <iostream>
#include <vector>
#include <string>
#include <set>

using namespace std;

int main () {
    string a,b;
    int n;
    cin>>a>>b;
    cin>>n;
    vector<char> c;
    for (int i = 0; i < 26; i++) {
        if (b[i]=='1') c.push_back(char(i+'a'));
    }
    vector<int> d(a.size(), -1);
    for (int i = 0; i < a.size(); i++) {
        bool t=0;
        for (char x : c) {
            if (a[i]==x) {
                t=1;
                break;
            }
        }
        if (t==1) { d[i]=0; }
        else d[i]=1;
    }
    set<string> r;
    for (int i=0; i<a.size(); i++) {
        int bad=0;
        string cur= "";
        for (int j=i; j<a.size(); j++) {
            cur+=a[j];
            if (d[j] == 1) { bad++; }
            if (bad>n) { break; }
            r.insert(cur);
        }
    }
    cout << r.size() << endl;
}