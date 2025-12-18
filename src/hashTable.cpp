#include "hashTable.h"
    
ChainHashTable::ChainHashTable() {
    for (int i = 0; i < CHAIN_TABLE_SIZE; i++) table[i] = nullptr;
}

ChainHashTable::~ChainHashTable() {
    for (int i = 0; i < CHAIN_TABLE_SIZE; i++) {
        Node* curr = table[i];
        while (curr) {
            Node* tmp = curr;
            curr = curr->next;
            delete tmp;
        }
    }
}

bool ChainHashTable::contains(const string& key) {
    int h = hashFun(key);
    Node* curr = table[h];
    while (curr) {
        if (curr->key == key) return true;
        curr = curr->next;
    }
    return false;
}

string ChainHashTable::get(const string& key) {
    int h = hashFun(key);
    Node* curr = table[h];
    while (curr) {
        if (curr->key == key) return curr->value;
        curr = curr->next;
    }
    return "";
}

bool ChainHashTable::insert(const string& key, const string& value) {
    if (contains(key)) return false;
    int h = hashFun(key);
    Node* newNode = new Node(key, value);
    newNode->next = table[h];
    table[h] = newNode;
    return true;
}

void ChainHashTable::remove(const string& key) {
    int h = hashFun(key);
    Node* curr = table[h];
    Node* prev = nullptr;
    while (curr) {
        if (curr->key == key) {
            if (prev) prev->next = curr->next;
            else table[h] = curr->next;
            delete curr;
            return;
        }
        prev = curr;
        curr = curr->next;
    }
}