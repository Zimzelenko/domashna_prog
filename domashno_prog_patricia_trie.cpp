#include <bits/stdc++.h>
using namespace std;

const int ALPHABET = 26;

struct TrieNode {
    TrieNode* child[ALPHABET + 1];
    string prefix;

    TrieNode(string p = "") : prefix(p) {
        for (int i = 0; i <= ALPHABET; i++) {
            child[i] = nullptr;
        }
    }

    ~TrieNode() {
        for (int i = 0; i <= ALPHABET; i++) {
            if (child[i] != nullptr)
                delete child[i];
        }
    }
};

class PatriciaTrie {
    TrieNode* root;

public:
    PatriciaTrie() {
        root = new TrieNode();
    }

    ~PatriciaTrie() {
        delete root;
    }

    void insert(string word) {
        word += '$';
        TrieNode* current = root;
        int i = 0;

        while (i < word.length()) {
            char ch = word[i];
            int index = (ch == '$') ? ALPHABET : (ch - 'a');

            if (current->child[index] == nullptr) {
                current->child[index] = new TrieNode(word.substr(i));
                return;
            }

            string label = current->child[index]->prefix;
            int j = 0;

            while (j < label.length() && i < word.length() && label[j] == word[i]) {
                i++;
                j++;
            }

            if (j == label.length()) {
                current = current->child[index];
            } else {
                TrieNode* existingChild = current->child[index];
                string remainingLabel = label.substr(j);
                string remainingWord = word.substr(i);

                TrieNode* newNode = new TrieNode(label.substr(0, j));
                current->child[index] = newNode;

                existingChild->prefix = remainingLabel;
                newNode->child[remainingLabel[0] == '$' ? ALPHABET : (remainingLabel[0] - 'a')] = existingChild;

                if (!remainingWord.empty()) {
                    newNode->child[remainingWord[0] == '$' ? ALPHABET : (remainingWord[0] - 'a')] = new TrieNode(remainingWord);
                }
                return;
            }
        }
    }

    bool search(string word) {
        word += '$';
        TrieNode* current = root;
        int i = 0;

        while (i < word.length()) {
            char ch = word[i];
            int index = (ch == '$') ? ALPHABET : (ch - 'a');

            if (current->child[index] == nullptr) {
                return false; 
            }

            string label = current->child[index]->prefix;
            int j = 0;

            while (j < label.length() && i < word.length() && label[j] == word[i]) {
                i++;
                j++;
            }

            if (j < label.length()) {
                return false; 
            }

            current = current->child[index];
        }

        return true; 
    }

    void print(TrieNode* node, string prefix) {

        for (int i = 0; i <= ALPHABET; i++) {
            if (node->child[i] != nullptr) {
                string nextPrefix = prefix + node->child[i]->prefix;

                if (node->child[i]->prefix.find('$') != string::npos) { //dali ima $ vo stringot (string::npos e ako go nema vo stringot)
                    cout << nextPrefix.substr(0, nextPrefix.length() - 1) << endl;
                }

                print(node->child[i], nextPrefix);
            }
        }
    }

    void print() {
        print(root, "");
    }
};

int main() {
    PatriciaTrie trie;

    trie.insert("facebook");
    trie.insert("face");
    trie.insert("this");
    trie.insert("there");
    trie.insert("then");
    trie.insert("therei");

    trie.print();

    cout << boolalpha; //pechati boolean kako tekst
    cout << "Search 'face': " << trie.search("face") << endl;       
    cout << "Search 'facebook': " << trie.search("facebook") << endl; 
    cout << "Search 'therein': " << trie.search("therein") << endl;   
    cout << "Search 'fab': " << trie.search("fab") << endl;           

    return 0;
}
