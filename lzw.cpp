#include "lzw.h"
#include <iostream>
#include <unordered_map>
#include <vector>
#include <string>

std::vector<int> compress(const std::string& text) {
    std::unordered_map<std::string, int> dictionary;
    std::vector<int> compressed;
    for (int i = 0; i < 256; ++i) {
        dictionary[std::string(1, char(i))] = i;
    }
    std::string current;
    for (char c : text) {
        std::string combined = current + c;
        if (dictionary.find(combined) != dictionary.end()) {
            current = combined;
        }
        else {
            compressed.push_back(dictionary[current]);
            dictionary[combined] = dictionary.size();
            current = std::string(1, c);
        }
    }
    if (!current.empty()) {
        compressed.push_back(dictionary[current]);
    }
    return compressed;
}

std::string decompress(const std::vector<int>& compressed) {
    std::unordered_map<int, std::string> dictionary;
    std::string decompressed;
    for (int i = 0; i < 256; ++i) {
        dictionary[i] = std::string(1, char(i));
    }
    std::string previous(1, char(compressed[0]));
    std::string current;
    current += previous;
    decompressed += previous;
    int code;
    for (size_t i = 1; i < compressed.size(); ++i) {
        code = compressed[i];
        if (dictionary.find(code) == dictionary.end()) {
            current = previous + previous[0];
        }
        else {
            current = dictionary[code];
        }
        decompressed += current;
        dictionary[dictionary.size()] = previous + current[0];
        previous = current;
    }
    return decompressed;
}