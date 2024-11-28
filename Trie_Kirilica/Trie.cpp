#include <bits/stdc++.h>
#include <fstream>
using namespace std;
const int ALPHABET = 31;

wstring IndexToLetter(int i){
        const wstring str [31]={L"\u00d0\u00b0", L"\u00d0\u00b1", L"\u00d0\u00b2", L"\u00d0\u00b3", L"\u00d0\u00b4", L"\u00d1\u0093", L"\u00d0\u00b5", L"\u00d0\u00b6", L"\u00d0\u00b7", L"\u00d1\u0095", L"\u00d0\u00b8", L"\u00d1\u0098", L"\u00d0\u00ba", L"\u00d0\u00bb", L"\u00d1\u0099", L"\u00d0\u00bc", L"\u00d0\u00bd", L"\u00d1\u009a", L"\u00d0\u00be", L"\u00d0\u00bf", L"\u00d1\u0080", L"\u00d1\u0081", L"\u00d1\u0082", L"\u00d1\u009c", L"\u00d1\u0083", L"\u00d1\u0084", L"\u00d1\u0085", L"\u00d1\u0086", L"\u00d1\u0087", L"\u00d1\u009f", L"\u00d1\u0088"};
        return str[i];
    }
    
    int LetterToIndex(wchar_t second_half) {
        switch (second_half)
        {
        case  L'\u00b0':
            return 0;
        case  L'\u00b1':
            return 1;
        case  L'\u00b2':
            return 2;
        case  L'\u00b3':
            return 3;
        case  L'\u00b4':
            return 4;
        case  L'\u0093':
            return 5;
        case  L'\u00b5':
            return 6;
        case  L'\u00b6':
            return 7;
        case  L'\u00b7':
            return 8;
        case  L'\u0095':
            return 9;
        case  L'\u00b8':
            return 10;
        case  L'\u0098':
            return 11;
        case  L'\u00ba':
            return 12;
        case  L'\u00bb':
            return 13;
        case  L'\u0099':
            return 14;
        case  L'\u00bc':
            return 15;
        case  L'\u00bd':
            return 16;
        case  L'\u009a':
            return 17;
        case  L'\u00be':
            return 18;
        case  L'\u00bf':
            return 19;
        case  L'\u0080':
            return 20;
        case  L'\u0081':
            return 21;
        case  L'\u0082':
            return 22;
        case  L'\u009c':
            return 23;
        case  L'\u0083':
            return 24;
        case  L'\u0084':
            return 25;
        case  L'\u0085':
            return 26;
        case  L'\u0086':
            return 27;
        case  L'\u0087':
            return 28;
        case  L'\u009f':
            return 29;
        case  L'\u0088':
            return 30;
        default:
            return 31;
        }
    }

    wstring TransformString(wstring word){    
        wstring rez;                         
        for(int i=1;i<word.size();i+=2)     
            rez+=word[i];
        return rez;
    }

class TrieNode {
public:
    TrieNode *child[ALPHABET + 1];

    TrieNode() {
        for (auto &a : child) a = nullptr;
    }
};

class Trie {
    TrieNode* root;

    void print(TrieNode *p ,wostream& izlez, wstring str){
        if(p->child[ALPHABET])
            izlez << str << endl;
        for(int i=0; i<ALPHABET; i++){
            if(p->child[i]) print(p->child[i], izlez, str + IndexToLetter(i));
        }
    }

public:
    Trie() {
        root = new TrieNode();
    }

    void insert(wstring word) {
        word=TransformString(word);
        TrieNode *p = root;
        for (int i = 0; i<word.size();i++) {
            int index = LetterToIndex(word[i]);
            if (!p->child[index]) p->child[index] = new TrieNode();
            p = p->child[index];
        }

        if (!p->child[ALPHABET]) p->child[ALPHABET] = new TrieNode();
    }

    bool search(wstring key, bool prefix = false) {
        key=TransformString(key);
        TrieNode *p = root;
        for (int i = 0;i<key.size(); i++) {
            int index = LetterToIndex(key[i]);
            if (!p->child[index]) return false;
            p = p->child[index];
        }

        if (!prefix && !p->child[ALPHABET]) return false;
        return true;
    }
    void print(wofstream &izlez){
        wstring str;
        print(root, izlez, str);
    }
};

int main() {
    
    wifstream vlez;
    wofstream izlez;
    vlez.open("zborovi.txt");
    wstring s,tmp;
    izlez.open("ispechateno");
    //izlez<<s;
    Trie trie;
    //int i = 0, n = 5;
    while(vlez>>s /*&& i<=n*/){
        trie.insert(s);
        //i++;
        /*if(i==n-2){
            vlez>>tmp;
            trie.insert(tmp);
        }*/
    }
    //vlez>>s;
    trie.print(izlez);
    //izlez<<endl<<tmp;
    /*if(trie.search(tmp)){
    izlez << endl << "True";        
    }
    else izlez << endl << "false";
    */

    vlez.close();
    izlez.close();
    return 0;
}
