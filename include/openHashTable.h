#pragma once
#include <string>
#include <iostream>
using namespace std;

constexpr int OPEN_TABLE_SIZE = 16;

class HashTableOpen {
private:
    struct Node {
        string key;
        string value;
        bool used = false;
    };

    Node table[OPEN_TABLE_SIZE];

    int hashFun(const string& str) const {
        long hash = 5381;
        for (char c : str)
            hash = hash * 33 + c;
        return hash % OPEN_TABLE_SIZE;
    }

public:
    HashTableOpen();

    bool insert(const string& value, const string& key);

    string get(const string& key) const;
    bool contains(const string& key) const;
    bool remove(const string& key);
    void printTable() const ;

    // вспомогательное: индекс для тестов
    int debugIndex(const string& key) const ;
};