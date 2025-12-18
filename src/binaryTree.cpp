#include "binaryTree.h"

CompleteBinaryTree::CompleteBinaryTree() {
    root = nullptr;
}

CompleteBinaryTree::~CompleteBinaryTree() {
    clear(root);
}

void CompleteBinaryTree::clear(TreeNode* node) {
    if (!node) return;
    clear(node->left);
    clear(node->right);
    delete node;
}

// Вставка в Complete Binary Tree
void CompleteBinaryTree::tInsert(int value) {
    TreeNode* node = new TreeNode(value);
    if (!root) {
        root = node;
        return;
    }

    queue<TreeNode*> q;
    q.push(root);

    while (!q.empty()) {
        TreeNode* cur = q.front(); q.pop();

        if (!cur->left) {
            cur->left = node;
            return;
        } else q.push(cur->left);

        if (!cur->right) {
            cur->right = node;
            return;
        } else q.push(cur->right);
    }
}

// Поиск элемента
bool CompleteBinaryTree::tSearch(int value) const {
    if (!root) return false;

    queue<TreeNode*> q;
    q.push(root);

    while (!q.empty()) {
        TreeNode* cur = q.front(); q.pop();
        if (cur->data == value) return true;
        if (cur->left) q.push(cur->left);
        if (cur->right) q.push(cur->right);
    }
    return false;
}

// Проверка Complete Binary Tree
bool CompleteBinaryTree::isComplete() const {
    if (!root) return true;

    queue<TreeNode*> q;
    q.push(root);
    bool flag = false;

    while (!q.empty()) {
        TreeNode* cur = q.front(); q.pop();

        if (cur->left) {
            if (flag) return false;
            q.push(cur->left);
        } else {
            flag = true;
        }

        if (cur->right) {
            if (flag) return false;
            q.push(cur->right);
        } else {
            flag = true;
        }
    }
    return true;
}

// Печать дерева
void CompleteBinaryTree::printTNode(TreeNode* node, int indent) const {
    if (!node) return;
    if (node->right) printTNode(node->right, indent + 4);
    if (indent) cout << string(indent, ' ');
    cout << node->data << endl;
    if (node->left) printTNode(node->left, indent + 4);
}

void CompleteBinaryTree::printT() const {
    if (!root) {
        //cout << "(empty)" << endl;
        return;
    }
    printTNode(root, 0);
}

// Сохранение в файл
void CompleteBinaryTree::saveT(const string& filename) const {
    if (!root) return;
    ofstream out(filename);
    if (!out.is_open()) return;

    queue<TreeNode*> q;
    q.push(root);

    while (!q.empty()) {
        TreeNode* cur = q.front(); q.pop();
        out << cur->data << endl;
        if (cur->left) q.push(cur->left);
        if (cur->right) q.push(cur->right);
    }
    out.close();
}

// Загрузка из файла
void CompleteBinaryTree::loadT(const string& filename) {
    ifstream in(filename);
    if (!in.is_open()) return;

    clear(root);
    root = nullptr;

    int value;
    while (in >> value) {
        tInsert(value);
    }
    in.close();
}