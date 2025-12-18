#define CATCH_CONFIG_MAIN
#include "catch.hpp"
#include "array.h"
#include "binaryTree.h"
#include "DoublyList.h"
#include "ForwardList.h"
#include "queue.h"
#include "stack.h"
#include "hashTable.h"
#include "openHashTable.h"

TEST_CASE("ForwardList empty list behavior") {
    ForwardList fl;

    REQUIRE_FALSE(fl.contains("A"));
    REQUIRE(fl.toVector().empty());

    fl.DeleteHeadFL();
    fl.DeleteTailFL();
    fl.DeleteAfterFL("X");
    fl.DeleteBeforeFL("X");
    fl.DeleteValueFL("X");

    fl.printFL();
}
TEST_CASE("AddAfterFL cases") {
    ForwardList fl;

    fl.AddAfterFL("X", "A"); // пустой список

    fl.AddTailFL("A");
    fl.AddTailFL("C");

    fl.AddAfterFL("A", "B");   // A B C
    fl.AddAfterFL("X", "Y");   // target не найден

    REQUIRE(fl.toVector() ==
            std::vector<std::string>{"A","B","C"});
}
TEST_CASE("AddBeforeFL cases") {
    ForwardList fl;

    fl.AddBeforeFL("A", "X"); // пустой

    fl.AddTailFL("A");
    fl.AddBeforeFL("A", "X"); // перед головой

    fl.AddTailFL("C");
    fl.AddBeforeFL("C", "B"); // середина

    REQUIRE(fl.toVector() ==
            std::vector<std::string>{"X","A","B","C"});
}
TEST_CASE("Delete head and tail") {
    ForwardList fl;

    fl.AddTailFL("A");
    fl.DeleteHeadFL();
    REQUIRE(fl.toVector().empty());

    fl.AddTailFL("A");
    fl.AddTailFL("B");
    fl.AddTailFL("C");

    fl.DeleteTailFL(); // удаляем C
    REQUIRE(fl.toVector() ==
            std::vector<std::string>{"A","B"});
}
TEST_CASE("DeleteAfterFL cases") {
    ForwardList fl;

    fl.DeleteAfterFL("A"); // пустой

    fl.AddTailFL("A");
    fl.DeleteAfterFL("A"); // next == nullptr

    fl.AddTailFL("B");
    fl.AddTailFL("C");

    fl.DeleteAfterFL("B"); // удалить C

    REQUIRE(fl.toVector() ==
            std::vector<std::string>{"A","B"});
}
TEST_CASE("DeleteBeforeFL cases") {
    ForwardList fl;

    fl.DeleteBeforeFL("A"); // пустой

    fl.AddTailFL("A");
    fl.DeleteBeforeFL("A"); // head == target

    fl.AddTailFL("B");
    fl.AddTailFL("C");

    fl.DeleteBeforeFL("B"); // удаляем A
    REQUIRE(fl.toVector() ==
            std::vector<std::string>{"B","C"});

    fl.DeleteBeforeFL("C"); // удаляем B
    REQUIRE(fl.toVector() ==
            std::vector<std::string>{"C"});
}
TEST_CASE("DeleteValueFL cases") {
    ForwardList fl;

    fl.DeleteValueFL("A"); // пустой

    fl.AddTailFL("A");
    fl.AddTailFL("B");
    fl.AddTailFL("C");

    fl.DeleteValueFL("A"); // удалить голову
    fl.DeleteValueFL("B"); // удалить середину
    fl.DeleteValueFL("X"); // не найден

    REQUIRE(fl.toVector() ==
            std::vector<std::string>{"C"});
}
TEST_CASE("printReverseFL") {
    ForwardList fl;

    fl.printReverseFL(nullptr); // ptr == nullptr

    fl.AddTailFL("A");
    fl.AddTailFL("B");
    fl.AddTailFL("C");

    fl.printReverseFL(fl.FindFL("A"));
}
TEST_CASE("Save and load ForwardList") {
    ForwardList fl;
    fl.AddTailFL("one");
    fl.AddTailFL("two");

    fl.saveFL("fl_test.txt");

    ForwardList fl2;
    fl2.loadFL("fl_test.txt");

    REQUIRE(fl2.toVector() ==
            std::vector<std::string>{"one","two"});

    std::remove("fl_test.txt");
}

TEST_CASE("DoublyList empty list behavior") {
    DoublyList dl;

    REQUIRE(dl.FindDL("X") == nullptr);

    dl.AddAfterDL("A", "B");
    dl.AddBeforeDL("A", "B");

    dl.DeleteHeadDL();
    dl.DeleteTailDL();
    dl.DeleteAfterDL("A");
    dl.DeleteBeforeDL("A");
    dl.DeleteByValueDL("A");

    dl.printForwardDL();
    dl.printBackwardDL();

    dl.saveDL("empty.txt");
    dl.loadDL("no_such_file.txt");

    std::remove("empty.txt");
}
TEST_CASE("AddHeadDL and AddTailDL DoublyList") {
    DoublyList dl;

    dl.AddHeadDL("B");
    dl.AddHeadDL("A");
    dl.AddTailDL("C");

    REQUIRE(dl.FindDL("A") != nullptr);
    REQUIRE(dl.FindDL("B") != nullptr);
    REQUIRE(dl.FindDL("C") != nullptr);
}
TEST_CASE("AddAfterDL cases DoublyList") {
    DoublyList dl;

    dl.AddAfterDL("X", "Y"); // пустой

    dl.AddTailDL("A");
    dl.AddAfterDL("X", "Y"); // target не найден

    dl.AddAfterDL("A", "B"); // в конец
    dl.AddAfterDL("A", "X"); // в середину

    REQUIRE(dl.FindDL("B") != nullptr);
    REQUIRE(dl.FindDL("X") != nullptr);
}
TEST_CASE("AddBeforeDL cases DoublyList") {
    DoublyList dl;

    dl.AddBeforeDL("A", "X"); // пустой

    dl.AddTailDL("A");
    dl.AddBeforeDL("A", "X"); // перед головой

    dl.AddTailDL("C");
    dl.AddBeforeDL("C", "B"); // середина

    REQUIRE(dl.FindDL("X") != nullptr);
    REQUIRE(dl.FindDL("B") != nullptr);
}
TEST_CASE("Delete head and tail DoublyList") {
    DoublyList dl;

    dl.DeleteHeadDL();
    dl.DeleteTailDL();

    dl.AddTailDL("A");
    dl.DeleteHeadDL();
    REQUIRE(dl.FindDL("A") == nullptr);

    dl.AddTailDL("A");
    dl.AddTailDL("B");
    dl.AddTailDL("C");

    dl.DeleteTailDL();
    REQUIRE(dl.FindDL("C") == nullptr);
}
TEST_CASE("DeleteAfterDL cases DoublyList") {
    DoublyList dl;

    dl.DeleteAfterDL("A"); // пустой

    dl.AddTailDL("A");
    dl.DeleteAfterDL("A"); // next == nullptr

    dl.AddTailDL("B");
    dl.AddTailDL("C");

    dl.DeleteAfterDL("B"); // удалить C
    REQUIRE(dl.FindDL("C") == nullptr);
}
TEST_CASE("DeleteBeforeDL cases") {
    DoublyList dl;

    dl.DeleteBeforeDL("A"); // пустой

    dl.AddTailDL("A");
    dl.AddTailDL("B");
    dl.DeleteBeforeDL("A"); // prev == nullptr

    dl.AddTailDL("C");

    dl.DeleteBeforeDL("B"); // удалить A
    REQUIRE(dl.FindDL("A") == nullptr);

    dl.DeleteBeforeDL("C"); // удалить B
    REQUIRE(dl.FindDL("B") == nullptr);
}
TEST_CASE("DeleteByValueDL cases DoublyList") {
    DoublyList dl;

    dl.DeleteByValueDL("X");

    dl.AddTailDL("A");
    dl.AddTailDL("B");
    dl.AddTailDL("C");

    dl.DeleteByValueDL("A"); // head
    dl.DeleteByValueDL("C"); // tail
    dl.DeleteByValueDL("B"); // middle
    dl.DeleteByValueDL("X"); // not found

    REQUIRE(dl.FindDL("A") == nullptr);
    REQUIRE(dl.FindDL("B") == nullptr);
    REQUIRE(dl.FindDL("C") == nullptr);
}
TEST_CASE("Print forward and backward DoublyList") {
    DoublyList dl;

    std::stringstream ss;
    auto* old = std::cout.rdbuf(ss.rdbuf());

    dl.printForwardDL();
    dl.printBackwardDL();

    dl.AddTailDL("A");
    dl.AddTailDL("B");

    dl.printForwardDL();
    dl.printBackwardDL();

    std::cout.rdbuf(old);

    REQUIRE(ss.str().find("A") != std::string::npos);
    REQUIRE(ss.str().find("B") != std::string::npos);
}
TEST_CASE("Save and load DoublyList") {
    DoublyList dl;

    dl.AddTailDL("one");
    dl.AddTailDL("two");

    dl.saveDL("dl_test.txt");

    DoublyList dl2;
    dl2.loadDL("dl_test.txt");

    REQUIRE(dl2.FindDL("one") != nullptr);
    REQUIRE(dl2.FindDL("two") != nullptr);

    std::remove("dl_test.txt");
}

TEST_CASE("Array constructor and initial state") {
    Array arr;

    REQUIRE(arr.lengthM() == 0);
    REQUIRE(arr.getM(0) == "");
    REQUIRE(arr.getM(-1) == "");
}
TEST_CASE("pushBackM and resize") {
    Array arr;

    arr.pushBackM("A");
    arr.pushBackM("B");
    arr.pushBackM("C"); // resize

    REQUIRE(arr.lengthM() == 3);
    REQUIRE(arr.getM(0) == "A");
    REQUIRE(arr.getM(1) == "B");
    REQUIRE(arr.getM(2) == "C");
}
TEST_CASE("insertM cases") {
    Array arr;

    arr.insertM(1, "X"); // index > size
    REQUIRE(arr.lengthM() == 0);

    arr.pushBackM("A");
    arr.pushBackM("C");

    arr.insertM(1, "B"); // середина
    REQUIRE(arr.getM(1) == "B");

    arr.insertM(0, "START"); // начало
    REQUIRE(arr.getM(0) == "START");

    arr.insertM(arr.lengthM(), "END"); // конец
    REQUIRE(arr.getM(arr.lengthM() - 1) == "END");
}
TEST_CASE("deleteM cases") {
    Array arr;

    arr.deleteM(0); // пустой

    arr.pushBackM("A");
    arr.pushBackM("B");
    arr.pushBackM("C");

    arr.deleteM(-1); // неверный индекс
    arr.deleteM(10); // неверный индекс

    arr.deleteM(1); // удалить середину
    REQUIRE(arr.lengthM() == 2);
    REQUIRE(arr.getM(1) == "C");

    arr.deleteM(0); // удалить первый
    REQUIRE(arr.getM(0) == "C");
}
TEST_CASE("getM and replaceM") {
    Array arr;

    arr.replaceM(0, "X"); // вне диапазона

    arr.pushBackM("A");
    arr.pushBackM("B");

    REQUIRE(arr.getM(1) == "B");

    arr.replaceM(1, "BB");
    REQUIRE(arr.getM(1) == "BB");

    REQUIRE(arr.getM(5) == "");
}
TEST_CASE("printM output") {
    Array arr;

    std::stringstream ss;
    auto* old = std::cout.rdbuf(ss.rdbuf());

    arr.printM(); // пустой

    arr.pushBackM("A");
    arr.pushBackM("B");

    arr.printM(); // непустой

    std::cout.rdbuf(old);

    REQUIRE(ss.str().find("Массив пуст") != std::string::npos);
    REQUIRE(ss.str().find("A") != std::string::npos);
    REQUIRE(ss.str().find("B") != std::string::npos);
}
TEST_CASE("saveM and loadM") {
    Array arr;

    arr.pushBackM("one");
    arr.pushBackM("two");

    arr.saveM("array_test.txt");

    Array arr2;
    arr2.loadM("array_test.txt");

    REQUIRE(arr2.lengthM() == 2);
    REQUIRE(arr2.getM(0) == "one");
    REQUIRE(arr2.getM(1) == "two");

    Array arr3;
    arr3.loadM("no_such_file.txt"); // файл не существует
    REQUIRE(arr3.lengthM() == 0);

    std::remove("array_test.txt");
}
//-------------------------------------------------

TEST_CASE("Queue initial state") {
    Queue q;

    REQUIRE(q.isEmptyQ() == true);
    REQUIRE(q.popQ() == "");
}
TEST_CASE("Queue push and pop single element") {
    Queue q;

    q.pushQ("A");

    REQUIRE(q.isEmptyQ() == false);
    REQUIRE(q.popQ() == "A");
    REQUIRE(q.isEmptyQ() == true);
}

TEST_CASE("Queue push and pop multiple elements") {
    Queue q;

    q.pushQ("A");
    q.pushQ("B");
    q.pushQ("C");

    REQUIRE(q.popQ() == "A");
    REQUIRE(q.popQ() == "B");
    REQUIRE(q.popQ() == "C");
    REQUIRE(q.popQ() == ""); // очередь пуста
}
TEST_CASE("Queue isEmptyQ states") {
    Queue q;

    REQUIRE(q.isEmptyQ());

    q.pushQ("X");
    REQUIRE_FALSE(q.isEmptyQ());

    q.popQ();
    REQUIRE(q.isEmptyQ());
}
TEST_CASE("Queue printQ output") {
    Queue q;
    std::stringstream ss;
    auto* oldBuf = std::cout.rdbuf(ss.rdbuf());

    q.printQ(); // пустая

    q.pushQ("A");
    q.pushQ("B");
    q.printQ(); // непустая

    std::cout.rdbuf(oldBuf);

    REQUIRE(ss.str().find("Очередь пуста") != std::string::npos);
    REQUIRE(ss.str().find("A") != std::string::npos);
    REQUIRE(ss.str().find("B") != std::string::npos);
}
TEST_CASE("Queue saveQ and loadQ") {
    Queue q;

    q.pushQ("one");
    q.pushQ("two");
    q.pushQ("three");

    q.saveQ("queue_test.txt");

    Queue q2;
    q2.loadQ("queue_test.txt");

    REQUIRE(q2.popQ() == "one");
    REQUIRE(q2.popQ() == "two");
    REQUIRE(q2.popQ() == "three");
    REQUIRE(q2.popQ() == "");

    std::remove("queue_test.txt");
}
TEST_CASE("Queue loadQ from non-existent file") {
    Queue q;

    q.loadQ("no_such_file.txt");
    REQUIRE(q.isEmptyQ());
}
//---------------------------------------
TEST_CASE("Stack initial state") {
    Stack s;

    REQUIRE(s.isEmptyS() == true);
    REQUIRE(s.popS() == "");
    REQUIRE(s.top() == "");
}
TEST_CASE("Stack push, top and pop single element") {
    Stack s;

    s.pushS("A");

    REQUIRE_FALSE(s.isEmptyS());
    REQUIRE(s.top() == "A");
    REQUIRE(s.popS() == "A");
    REQUIRE(s.isEmptyS());
}
TEST_CASE("Stack push and pop multiple elements") {
    Stack s;

    s.pushS("A");
    s.pushS("B");
    s.pushS("C");

    REQUIRE(s.popS() == "C");
    REQUIRE(s.popS() == "B");
    REQUIRE(s.popS() == "A");
    REQUIRE(s.popS() == "");
}
TEST_CASE("Stack printS output") {
    Stack s;
    std::stringstream ss;
    auto* oldBuf = std::cout.rdbuf(ss.rdbuf());

    s.printS(); // пустой стек

    s.pushS("X");
    s.pushS("Y");
    s.printS(); // непустой стек

    std::cout.rdbuf(oldBuf);

    REQUIRE(ss.str().find("Стек (верх -> низ)") != std::string::npos);
    REQUIRE(ss.str().find("Y") != std::string::npos);
    REQUIRE(ss.str().find("X") != std::string::npos);
}
TEST_CASE("Stack clearS") {
    Stack s;

    s.pushS("1");
    s.pushS("2");
    s.pushS("3");

    s.clearS();

    REQUIRE(s.isEmptyS());
    REQUIRE(s.popS() == "");
}
TEST_CASE("Stack saveS and loadS") {
    Stack s;

    s.pushS("one");
    s.pushS("two");
    s.pushS("three");

    s.saveS("stack_test.txt");

    Stack s2;
    s2.loadS("stack_test.txt");

    REQUIRE(s2.popS() == "three");
    REQUIRE(s2.popS() == "two");
    REQUIRE(s2.popS() == "one");
    REQUIRE(s2.popS() == "");

    std::remove("stack_test.txt");
}
TEST_CASE("Stack loadS from non-existent file") {
    Stack s;

    s.loadS("no_file_here.txt");
    REQUIRE(s.isEmptyS());
}
//------------------------------------
TEST_CASE("ChainHashTable initial state") {
    ChainHashTable ht;

    REQUIRE_FALSE(ht.contains("key"));
    REQUIRE(ht.get("key") == "");
}
TEST_CASE("ChainHashTable insert single element") {
    ChainHashTable ht;

    REQUIRE(ht.insert("a", "1") == true);
    REQUIRE(ht.contains("a") == true);
    REQUIRE(ht.get("a") == "1");
}
TEST_CASE("ChainHashTable insert duplicate key") {
    ChainHashTable ht;

    REQUIRE(ht.insert("a", "1") == true);
    REQUIRE(ht.insert("a", "2") == false);
    REQUIRE(ht.get("a") == "1");
}


TEST_CASE("ChainHashTable remove head of chain") {
    ChainHashTable ht;

    ht.insert("a", "1");
    ht.insert("b", "2");

    REQUIRE(ht.contains("a"));
    ht.remove("a");

    REQUIRE_FALSE(ht.contains("a"));
    REQUIRE(ht.get("a") == "");
}
TEST_CASE("ChainHashTable remove middle or tail of chain") {
    ChainHashTable ht;

    ht.insert("a", "1");
    ht.insert("b", "2");
    ht.insert("c", "3");

    REQUIRE(ht.contains("b"));
    ht.remove("b");

    REQUIRE_FALSE(ht.contains("b"));
    REQUIRE(ht.contains("a"));
    REQUIRE(ht.contains("c"));
}
TEST_CASE("ChainHashTable remove non-existent key") {
    ChainHashTable ht;

    ht.insert("a", "1");
    ht.remove("x"); // не существует

    REQUIRE(ht.contains("a"));
}
TEST_CASE("ChainHashTable get missing key") {
    ChainHashTable ht;

    ht.insert("a", "1");

    REQUIRE(ht.get("x") == "");
}

TEST_CASE("HashTableOpen initial state") {
    HashTableOpen ht;

    REQUIRE_FALSE(ht.contains("key"));
    REQUIRE(ht.get("key") == "");
}
TEST_CASE("HashTableOpen insert single element") {
    HashTableOpen ht;

    REQUIRE(ht.insert("value1", "key1"));
    REQUIRE(ht.contains("key1"));
    REQUIRE(ht.get("key1") == "value1");
}
TEST_CASE("HashTableOpen insert empty key") {
    HashTableOpen ht;

    REQUIRE_FALSE(ht.insert("value", ""));
}
TEST_CASE("HashTableOpen duplicate key") {
    HashTableOpen ht;

    REQUIRE(ht.insert("value1", "key"));
    REQUIRE_FALSE(ht.insert("value2", "key"));
    REQUIRE(ht.get("key") == "value1");
}
TEST_CASE("HashTableOpen collision handling") {
    HashTableOpen ht;

    // Заставляем работать probing
    ht.insert("v1", "a");
    ht.insert("v2", "b");
    ht.insert("v3", "c");

    REQUIRE(ht.contains("a"));
    REQUIRE(ht.contains("b"));
    REQUIRE(ht.contains("c"));

    REQUIRE(ht.get("a") == "v1");
    REQUIRE(ht.get("b") == "v2");
    REQUIRE(ht.get("c") == "v3");
}
TEST_CASE("HashTableOpen get stops at unused cell") {
    HashTableOpen ht;

    ht.insert("value", "key");

    REQUIRE(ht.get("unknown") == "");
}
TEST_CASE("HashTableOpen contains stops at unused cell") {
    HashTableOpen ht;

    ht.insert("value", "key");

    REQUIRE_FALSE(ht.contains("unknown"));
}
TEST_CASE("HashTableOpen remove existing key") {
    HashTableOpen ht;

    ht.insert("value", "key");

    REQUIRE(ht.contains("key"));
    REQUIRE(ht.remove("key"));
    REQUIRE_FALSE(ht.contains("key"));
    REQUIRE(ht.get("key") == "");
}
TEST_CASE("HashTableOpen remove missing key") {
    HashTableOpen ht;

    ht.insert("value", "key");

    REQUIRE_FALSE(ht.remove("unknown"));
}
TEST_CASE("HashTableOpen full table insert fails") {
    HashTableOpen ht;

    for (int i = 0; i < OPEN_TABLE_SIZE; ++i) {
        ht.insert("v" + std::to_string(i), "k" + std::to_string(i));
    }

    REQUIRE_FALSE(ht.insert("extra", "extra"));
}
TEST_CASE("HashTableOpen debugIndex") {
    HashTableOpen ht;
    int idx = ht.debugIndex("test");
    REQUIRE(idx >= 0);
    REQUIRE(idx < OPEN_TABLE_SIZE);
}
TEST_CASE("HashTableOpen printTable empty") {
    HashTableOpen ht;

    std::ostringstream out;
    auto* oldBuf = std::cout.rdbuf(out.rdbuf());

    ht.printTable();

    std::cout.rdbuf(oldBuf);

    std::string s = out.str();

    REQUIRE(s.find("Хэш-таблица") != std::string::npos);
    REQUIRE(s.find("-") != std::string::npos);
}
TEST_CASE("HashTableOpen printTable with elements") {
    HashTableOpen ht;

    ht.insert("value1", "key1");
    ht.insert("value2", "key2");

    std::ostringstream out;
    auto* oldBuf = std::cout.rdbuf(out.rdbuf());

    ht.printTable();

    std::cout.rdbuf(oldBuf);

    std::string s = out.str();

    REQUIRE(s.find("'key1' -> 'value1'") != std::string::npos);
    REQUIRE(s.find("'key2' -> 'value2'") != std::string::npos);
}
//-------------------------------------------------
TEST_CASE("BinaryTree empty tree") {
    CompleteBinaryTree tree;

    REQUIRE(tree.tSearch(10) == false);
    REQUIRE(tree.isComplete() == true);

    std::ostringstream out;
    auto* old = std::cout.rdbuf(out.rdbuf());

    tree.printT();

    std::cout.rdbuf(old);
}
TEST_CASE("BinaryTree insert and search") {
    CompleteBinaryTree tree;

    tree.tInsert(1);
    tree.tInsert(2);
    tree.tInsert(3);
    tree.tInsert(4);

    REQUIRE(tree.tSearch(1));
    REQUIRE(tree.tSearch(2));
    REQUIRE(tree.tSearch(3));
    REQUIRE(tree.tSearch(4));
    REQUIRE_FALSE(tree.tSearch(100));
}
TEST_CASE("BinaryTree isComplete true") {
    CompleteBinaryTree tree;

    for (int i = 1; i <= 7; ++i)
        tree.tInsert(i);

    REQUIRE(tree.isComplete() == true);
}
TEST_CASE("BinaryTree printT output") {
    CompleteBinaryTree tree;

    tree.tInsert(1);
    tree.tInsert(2);
    tree.tInsert(3);

    std::ostringstream out;
    auto* old = std::cout.rdbuf(out.rdbuf());

    tree.printT();

    std::cout.rdbuf(old);

    std::string s = out.str();
    REQUIRE(s.find("1") != std::string::npos);
    REQUIRE(s.find("2") != std::string::npos);
    REQUIRE(s.find("3") != std::string::npos);
}
TEST_CASE("BinaryTree save and load") {
    CompleteBinaryTree tree;

    tree.tInsert(10);
    tree.tInsert(20);
    tree.tInsert(30);

    tree.saveT("tree.txt");

    CompleteBinaryTree loaded;
    loaded.loadT("tree.txt");

    REQUIRE(loaded.tSearch(10));
    REQUIRE(loaded.tSearch(20));
    REQUIRE(loaded.tSearch(30));
}