#include "huffman.h"
#include <iostream>
#include <string>
#include <queue>
#include <map>

struct Tree {
    char symbol;
    int count;
    Tree* left;
    Tree* right;
    Tree(char symbol, int count) : symbol(symbol), count(count), left(nullptr), right(nullptr) {}
    struct Compare {
        bool operator()(Tree* left, Tree* right) {
            return left->count > right->count;
        }
    };
};
Tree* build(const std::string& text) {
    std::map<char, int> letters;
    for (char c : text) {
        letters[c]++;
    }
    std::priority_queue<Tree*, std::vector<Tree*>, Tree::Compare> pq;
    for (const auto& entry : letters) {
        pq.push(new Tree(entry.first, entry.second));
    }
    while (pq.size() > 1) {
        Tree* left = pq.top(); pq.pop();
        Tree* right = pq.top(); pq.pop();
        Tree* tree = new Tree('\0', left->count + right->count);
        tree->left = left;
        tree->right = right;
        pq.push(tree);
    }
    return pq.top();
}
void Codes(Tree* root, const std::string& code, std::map<char, std::string>& codes) {
    if (root->left == nullptr && root->right == nullptr) {
        codes[root->symbol] = code;
        return;
    }
    Codes(root->left, code + "0", codes);
    Codes(root->right, code + "1", codes);
}
std::string encode(const std::string& text) {
    std::string encoded = "";
    Tree* root = build(text);
    std::map<char, std::string> codes;
    Codes(root, "", codes);
    for (char c : text) {
        encoded += codes[c];
    }
    return encoded;
}
std::string decode(std::string& str, std::map<char, std::string>& codes) {
    std::string out = "";
    std::string code;
    std::map<std::string, char> codes_rev;
    for (std::map<char, std::string>::iterator it = codes.begin(); it != codes.end(); it++)
        codes_rev[it->second] = it->first;
    for (int i = 0; i < str.length(); i++) {
        code.push_back(str[i] == '0' ? false : true);
        if (codes_rev[code]) {
            out += codes_rev[code];
            code.clear();
        }
    }
    return out;
}