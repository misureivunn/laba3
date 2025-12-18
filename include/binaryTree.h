#pragma once
#include <iostream>
#include <fstream>
#include <queue>

using namespace std;

class CompleteBinaryTree {
public:
    struct TreeNode {
        int data;
        TreeNode* left;
        TreeNode* right;
        TreeNode(int val) : data(val), left(nullptr), right(nullptr) {}
    };

    CompleteBinaryTree();
    ~CompleteBinaryTree();

    void tInsert(int value);
    bool tSearch(int value) const;
    bool isComplete() const;

    void printT() const;
    void saveT(const string& filename) const;
    void loadT(const string& filename);

private:
    TreeNode* root;

    void clear(TreeNode* node);
    void printTNode(TreeNode* node, int indent) const;
    void saveBinCBT(const string& filename) const;
    void loadBinCBT(const string& filename);
};