#pragma once
#include <iostream>
#include <fstream>
#include <string>
using namespace std;


class Queue{
private:
    struct QueueNode {
        string data;
        QueueNode* next; //следующий элемент
    };

    QueueNode* front; //первый элемент
    QueueNode* rear;//последний элемент

public:
    Queue();
    ~Queue();
    void pushQ(string value);
    string popQ();
    bool isEmptyQ();
    void printQ();
    void loadQ(const string& filename);
    void saveQ(const string& filename);
    void saveBinQ(const string& filename);
    void loadBinQ(const string& filename);

};