#pragma once
#include <iostream>
#include <fstream>
#include <string>
using namespace std;


class DoublyList{
private:
    struct NodeDoublyList {
        string data;
        NodeDoublyList* prev;
        NodeDoublyList* next;
    };

    NodeDoublyList* head;
    NodeDoublyList* tail;

public:

    DoublyList();
    ~DoublyList();
    void AddHeadDL(string value);
    void AddTailDL( string value);
    NodeDoublyList* FindDL(string value);
    void AddAfterDL(const string& target, const string& value);
    void AddBeforeDL(const string& target, const string& value);
    void DeleteHeadDL();
    void DeleteTailDL();
    void DeleteAfterDL(const string& target);
    void DeleteBeforeDL(const string& target);
    void DeleteByValueDL(string value);
    void printForwardDL();
    void printBackwardDL();
    void saveDL(const string& filename);
    void loadDL(const string& filename);
    void saveBinDL(const string& filename);
    void loadBinDL(const string& filename);
};
