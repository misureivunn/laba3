#include "catch.hpp"
#include "array.h"
#include "binaryTree.h"
#include "DoublyList.h"
#include "ForwardList.h"
#include "queue.h"
#include "stack.h"
#include "hashTable.h"
#include "openHashTable.h"

void Array::saveBinM(const string& filename) {
    ofstream out(filename, ios::binary);
    out.write((char*)&size, sizeof(size));

    for (int i = 0; i < size; i++) {
        size_t len = data[i].size();
        out.write((char*)&len, sizeof(len));
        out.write(data[i].c_str(), len);
    }
    out.close();
}

void Array::loadBinM(const string& filename) {
    ifstream in(filename, ios::binary);
    if (!in) return;

    delete[] data;

    in.read((char*)&size, sizeof(size));
    capacity = size > 0 ? size : 2;
    data = new string[capacity];

    for (int i = 0; i < size; i++) {
        size_t len;
        in.read((char*)&len, sizeof(len));
        data[i].resize(len);
        in.read(&data[i][0], len);
    }
    in.close();
}


void ForwardList::saveBinFL(const string& filename) {
    ofstream out(filename, ios::binary);
    NodeSinglyList* cur = head;

    while (cur) {
        size_t len = cur->data.size();
        out.write((char*)&len, sizeof(len));
        out.write(cur->data.c_str(), len);
        cur = cur->next;
    }
    out.close();
}

void ForwardList::loadBinFL(const string& filename) {
    ifstream in(filename, ios::binary);
    if (!in) return;

    clear();
    while (in.peek() != EOF) {
        size_t len;
        in.read((char*)&len, sizeof(len));
        if (!in) break;

        string value(len, '\0');
        in.read(&value[0], len);
        AddTailFL(value);
    }
    in.close();
}

void DoublyList::saveBinDL(const string& filename) {
    ofstream out(filename, ios::binary);
    NodeDoublyList* cur = head;

    while (cur) {
        size_t len = cur->data.size();
        out.write((char*)&len, sizeof(len));
        out.write(cur->data.c_str(), len);
        cur = cur->next;
    }
    out.close();
}

void DoublyList::loadBinDL(const string& filename) {
    ifstream in(filename, ios::binary);
    if (!in) return;

    head = tail = nullptr;

    while (in.peek() != EOF) {
        size_t len;
        in.read((char*)&len, sizeof(len));
        if (!in) break;

        string value(len, '\0');
        in.read(&value[0], len);
        AddTailDL(value);
    }
    in.close();
}

void Stack::saveBinS(const string& filename) {
    ofstream out(filename, ios::binary);
    StackNode* cur = head;

    while (cur) {
        size_t len = cur->data.size();
        out.write((char*)&len, sizeof(len));
        out.write(cur->data.c_str(), len);
        cur = cur->next;
    }
    out.close();
}

void Stack::loadBinS(const string& filename) {
    ifstream in(filename, ios::binary);
    if (!in) return;

    clearS();
    vector<string> temp;

    while (in.peek() != EOF) {
        size_t len;
        in.read((char*)&len, sizeof(len));
        if (!in) break;

        string value(len, '\0');
        in.read(&value[0], len);
        temp.push_back(value);
    }

    for (auto it = temp.rbegin(); it != temp.rend(); ++it)
        pushS(*it);

    in.close();
}

void Queue::saveBinQ(const string& filename) {
    ofstream out(filename, ios::binary);
    QueueNode* cur = front;

    while (cur) {
        size_t len = cur->data.size();
        out.write((char*)&len, sizeof(len));
        out.write(cur->data.c_str(), len);
        cur = cur->next;
    }
    out.close();
}

void Queue::loadBinQ(const string& filename) {
    ifstream in(filename, ios::binary);
    if (!in) return;

    while (!isEmptyQ()) popQ();

    while (in.peek() != EOF) {
        size_t len;
        in.read((char*)&len, sizeof(len));
        if (!in) break;

        string value(len, '\0');
        in.read(&value[0], len);
        pushQ(value);
    }
    in.close();
}

void ChainHashTable::saveBinCHT(const string& filename) {
    ofstream out(filename, ios::binary);

    for (int i = 0; i < CHAIN_TABLE_SIZE; i++) {
        Node* cur = table[i];
        while (cur) {
            size_t klen = cur->key.size();
            size_t vlen = cur->value.size();
            out.write((char*)&klen, sizeof(klen));
            out.write(cur->key.c_str(), klen);
            out.write((char*)&vlen, sizeof(vlen));
            out.write(cur->value.c_str(), vlen);
            cur = cur->next;
        }
    }
    out.close();
}

void ChainHashTable::loadBinCHT(const string& filename) {
    ifstream in(filename, ios::binary);
    if (!in) return;

    string key, value;
    while (in.peek() != EOF) {
        size_t klen, vlen;
        in.read((char*)&klen, sizeof(klen));
        if (!in) break;

        key.resize(klen);
        in.read(&key[0], klen);

        in.read((char*)&vlen, sizeof(vlen));
        value.resize(vlen);
        in.read(&value[0], vlen);

        insert(key, value);
    }
    in.close();
}

void CompleteBinaryTree::saveBinCBT(const string& filename) const {
    ofstream out(filename, ios::binary);
    queue<TreeNode*> q;
    if (root) q.push(root);

    while (!q.empty()) {
        TreeNode* cur = q.front(); q.pop();
        out.write((char*)&cur->data, sizeof(cur->data));
        if (cur->left) q.push(cur->left);
        if (cur->right) q.push(cur->right);
    }
    out.close();
}

void CompleteBinaryTree::loadBinCBT(const string& filename) {
    ifstream in(filename, ios::binary);
    if (!in) return;

    clear(root);
    root = nullptr;

    int value;
    while (in.read((char*)&value, sizeof(value))) {
        tInsert(value);
    }
    in.close();
}