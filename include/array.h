#pragma once
#include <iostream>
#include <fstream>
#include <string>
using namespace std;

class Array {
private:
    string* data;
    int size;
    int capacity;

    void resize(int newCapacity);

public:
    Array();
    ~Array();

    
    void deleteM(int index);
    void pushBackM(const string& value);
    void insertM(int index, const string& value);
    // void removeAtM(int*& arr, int& size, int index);
    string getM(int index);
    void replaceM(int index, string value);
    void printM();
    int lengthM();
    void loadM(const string& filename);
    void saveM(const string& filename);
    void saveBinM(const string& filename);
    void loadBinM(const string& filename);
};