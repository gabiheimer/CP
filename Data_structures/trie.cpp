#include<bits/stdc++.h>
#define endl '\n'
#define ll long long

using namespace std;

struct Node {
    char digit;
    char value;
    bool hasValue;
    Node *left, *right;

    Node(char digit) {
        this->digit = digit;
        this->hasValue = false;
        this->left = NULL, this->right = NULL;
    }
};

class Trie {
    public:
    Node *root;

    Trie() { this->root = new Node('*'); }

    void insertWord(char &decodedValue, string &encodedValue) {
        Node *cur = root;
        for(auto c : encodedValue) {
            if(c == '0') {
                if(!cur->left) cur->left = new Node('0');
                cur = cur->left;
            } else {
                if(!cur->right) cur->right = new Node('1');
                cur = cur->right;
            }
        }

        cur->hasValue = true;
        cur->value = decodedValue;
    }
};

// funcao para descobrir se uma codificacao eh ambigua
bool isAmbiguous(int pos, string &curDecoded, string &encoded, string &original, Node *root, Trie *trie) {
    if(pos == encoded.size()) {
        if(root != trie->root) return false;
        return curDecoded != original;
    }

    Node *next;
    // vejo se consigo continuar com a letra atual
    if(encoded[pos] == '0') {
        if(!root->left) return false;
        next = root->left;
    } else {
        if(!root->right) return false;
        next = root->right;
    }

    // se esse no tem valor, eu adiciono ele na string e reinicio o root
    if(next->hasValue) {
        curDecoded += next->value;
        bool isAmb = isAmbiguous(pos+1, curDecoded, encoded, original, trie->root, trie);
        curDecoded.pop_back();

        if(isAmb) return true;
    }

    // eu vou pra a proxima posicao, continuando o caminho da trie
    bool isAmb = isAmbiguous(pos+1, curDecoded, encoded, original, next, trie);
    
    return isAmb;
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);

    int n;
    string a;
    char b;
    cin >> n;

    Trie *trie = new Trie();
    map<char,string> encodeTable;
    string encoded = "", decoded;

    for(int i = 0; i < n; i++) {
        cin >> a >> b;
        encodeTable[b] = a;
        trie->insertWord(b, a);
    }

    cin >> decoded;
    for(auto c : decoded) 
        encoded += encodeTable[c];

    string cur = "";

    if(isAmbiguous(0, cur, encoded, decoded, trie->root, trie)) cout << "Yes" << endl;
    else cout << "No" << endl;
}