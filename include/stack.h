#pragma once
#include <iostream>
#include <fstream>
#include <string>
using namespace std;

class Stack{
private:
    struct StackNode {
        string data;
        StackNode* next;
    };

    StackNode* head;

public:
    Stack();
    ~Stack();
    bool isEmptyS();
    void pushS(string value);
    string popS();
    string top();
    //string topS(Stack* st);
    void printS();
    void clearS();
    void loadS(const string& filename);
    void saveS(const string& filename);
    void saveBinS(const string& filename);
    void loadBinS(const string& filename);

};