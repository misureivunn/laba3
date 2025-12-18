#pragma once
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
using namespace std;

class ForwardList{
private:
    struct NodeSinglyList{
        string data;
        NodeSinglyList* next;
    };
    NodeSinglyList* head;

public:
    ForwardList();
    ~ForwardList();
    bool contains(const std::string& value) const;
    std::vector<std::string> toVector() const;

    void AddNodeFL(NodeSinglyList* ptr, const string& data);
    void AddHeadFL(const string& data);
    void AddTailFL(const string& data);
    void AddAfterFL( const string& target, const string& data);
    void AddBeforeFL(const string& target, const string& data);
    void DeleteHeadFL();
    void DeleteTailFL();
    void DeleteAfterFL( const string& target);
    void DeleteBeforeFL(const string& target);
    void DeleteValueFL(const string& data);
    NodeSinglyList* FindFL(const string& data);
    void printFL();
    void printByValueFL(const string& data);
    void printReverseFL(NodeSinglyList* ptr);
    void saveFL(const string& filename);
    void loadFL(const string& filename);
    void clear();
    void saveBinFL(const string& filename);
    void loadBinFL(const string& filename);
};