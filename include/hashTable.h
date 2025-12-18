#pragma once
#include <iostream>
#include <string>

using namespace std;

const int CHAIN_TABLE_SIZE = 101;

class ChainHashTable {
private:
    struct Node {
        string key;
        string value;
        Node* next;
        Node(const string& k, const string& v) : key(k), value(v), next(nullptr) {}
    };

    Node* table[CHAIN_TABLE_SIZE];

    int hashFun(const string& key) {
        long hash = 5381;
        for (char c : key) hash = hash * 33 + c;
        return hash % CHAIN_TABLE_SIZE;
    }

public:
    ChainHashTable();
    ~ChainHashTable();
    bool contains(const string& key);
    string get(const string& key);
    bool insert(const string& key, const string& value);
    void remove(const string& key);
    void saveBinCHT(const string& filename);
    void loadBinCHT(const string& filename);   

};