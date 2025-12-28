#include <iostream>
#include <string>
#include <map>
#include <vector>
#include <algorithm>

#ifdef _WIN32
#include <windows.h>
#endif

using namespace std;

struct PatriciaNode {
    string label;
    bool isWord;
    map<char, PatriciaNode*> children;

    PatriciaNode(string l = "", bool w = false) : label(l), isWord(w) {}

    ~PatriciaNode() {
        for (auto const& [key, val] : children) {
            delete val;
        }
    }
};

class PatriciaTrie {
private:
    PatriciaNode* root;

    int getCommonPrefixLen(const string& s1, const string& s2) {
        int len = 0;
        int minLen = min(s1.length(), s2.length());
        while (len < minLen && s1[len] == s2[len]) {
            len++;
        }
        return len;
    }

    void printRecursive(PatriciaNode* node, int level) {
        for (auto const& [key, child] : node->children) {
            for (int i = 0; i < level; i++) cout << "    ";
            cout << "|-- " << child->label;
            if (child->isWord) cout << " (KRAJ)";
            cout << endl;
            printRecursive(child, level + 1);
        }
    }

public:
    PatriciaTrie() {
        root = new PatriciaNode();
    }

    ~PatriciaTrie() {
        delete root;
    }

    void insert(string word) {
        PatriciaNode* node = root;
        
        while (!word.empty()) {
            char firstChar = word[0];

            if (node->children.find(firstChar) == node->children.end()) {
                node->children[firstChar] = new PatriciaNode(word, true);
                return;
            }

            PatriciaNode* child = node->children[firstChar];
            int commonLen = getCommonPrefixLen(child->label, word);

            if (commonLen == child->label.length()) {
                word = word.substr(commonLen);
                node = child;
                if (word.empty()) {
                    child->isWord = true;
                    return;
                }
                continue;
            }

            string commonPart = child->label.substr(0, commonLen);
            string childRemainder = child->label.substr(commonLen);
            string wordRemainder = word.substr(commonLen);

            child->label = commonPart;

            PatriciaNode* newSplitChild = new PatriciaNode(childRemainder, child->isWord);
            newSplitChild->children = child->children;

            child->children.clear();
            child->children[childRemainder[0]] = newSplitChild;
            child->isWord = false;

            if (!wordRemainder.empty()) {
                child->children[wordRemainder[0]] = new PatriciaNode(wordRemainder, true);
            } else {
                child->isWord = true;
            }
            return;
        }
        node->isWord = true;
    }

    bool search(string word) {
        PatriciaNode* node = root;
        
        while (!word.empty()) {
            char firstChar = word[0];
            if (node->children.find(firstChar) == node->children.end()) {
                return false;
            }

            PatriciaNode* child = node->children[firstChar];
            
            if (word.length() < child->label.length() || 
                word.substr(0, child->label.length()) != child->label) {
                return false;
            }

            word = word.substr(child->label.length());
            node = child;
        }
        return node->isWord;
    }

    void display() {
        cout << "ROOT" << endl;
        printRecursive(root, 0);
    }
};

int main() {
    #ifdef _WIN32
    SetConsoleOutputCP(65001);
    #endif

    PatriciaTrie trie;

    vector<string> zborovi = {
        "татко", 
        "татина", 
        "татковина", 
        "јаболко", 
        "јаготка", 
        "леб", 
        "лебед"
    };

    cout << "--- Vnesuvanje zborovi ---" << endl;
    for (const string& z : zborovi) {
        trie.insert(z);
        cout << "Vnesen: " << z << endl;
    }

    cout << "\n--- Struktura na drvoto ---" << endl;
    trie.display();

    cout << "\n--- Prebaruvanje ---" << endl;
    vector<string> testZborovi = {"татко", "автомобил", "леб", "јабол"};
    
    for (const string& z : testZborovi) {
        if (trie.search(z)) {
            cout << "Zborot '" << z << "' POSTOI." << endl;
        } else {
            cout << "Zborot '" << z << "' NE postoi." << endl;
        }
    }

    return 0;
}