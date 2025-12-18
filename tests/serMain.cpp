#include "catch.hpp"
#include "array.h"
#include "binaryTree.h"
#include "DoublyList.h"
#include "ForwardList.h"
#include "queue.h"
#include "stack.h"
#include "hashTable.h"
#include "openHashTable.h"

int main() {
    Array a;
    a.pushBackM("one");
    a.pushBackM("two");
    a.saveBin("array.bin");

    Array a2;
    a2.loadBin("array.bin");
    a2.printM();

    ForwardList fl;
    fl.AddTailFL("A");
    fl.AddTailFL("B");
    fl.saveBin("fl.bin");

    ForwardList fl2;
    fl2.loadBin("fl.bin");
    fl2.printFL();

    Stack s;
    s.pushS("X");
    s.pushS("Y");
    s.saveBin("stack.bin");

    Stack s2;
    s2.loadBin("stack.bin");
    s2.printS();

    Queue q;
    q.pushQ("1");
    q.pushQ("2");
    q.saveBin("queue.bin");

    Queue q2;
    q2.loadBin("queue.bin");
    q2.printQ();

    CompleteBinaryTree t;
    t.tInsert(1);
    t.tInsert(2);
    t.tInsert(3);
    t.saveBin("tree.bin");

    CompleteBinaryTree t2;
    t2.loadBin("tree.bin");
    t2.printT();

    return 0;
}