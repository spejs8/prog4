#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

struct Node {
    string edge;
    bool zbor;
    vector<Node*> children;

    Node(string e = "", bool w = false) : edge(e), zbor(w) {}
};

int najdolg_prefix (string a,string b) {
    int i = 0;
    while (i < a.size() && i < b.size() && a[i] == b[i]) {
        i++;
    }
    return i;
}

void insert(Node* root,string word) {
    string s = word;
    for (Node* child : root->children) {
        int tmp=najdolg_prefix(s, child->edge);
        if (tmp==0) { continue; }
        if (tmp==child->edge.size()) {
            insert(child, s.substr(tmp));
            return;
        }
        Node* mid=new Node(child->edge.substr(0, tmp));
        child->edge=child->edge.substr(tmp);
        mid->children.push_back(child);
        string suf = s.substr(tmp);
        if (suf.size()==0) { mid->zbor=true; } 
        else {
            Node* newNode=new Node(suf, true);
            mid->children.push_back(newNode);
        }
        root->children.erase(find(root->children.begin(), root->children.end(), child));
        root->children.push_back(mid);
        return;
    }
    root->children.push_back(new Node(s, true));
}

bool search(Node* root, const string &word) {
    string s = word;
    for (Node* child : root->children) {
        int tmp=najdolg_prefix(s, child->edge);
        if (tmp==0) continue;
        if (tmp==child->edge.size()) {
            if (tmp==s.size())
                return child->zbor;
            return search(child, s.substr(tmp));
        }
        return false;
    }
    return false;
}
int main() {
    Node* root = new Node();
    insert(root, "banana");
    insert(root, "band");
    insert(root, "bank");
    insert(root, "bandit");
    cout << search(root, "ban") << endl;
    cout << search(root, "banana") << endl;
    return 0;
}