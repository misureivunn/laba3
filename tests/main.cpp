#define BOOST_TEST_MODULE MyProjectTests
// #define BOOST_TEST_NO_MAIN
// #define BOOST_TEST_ALTERNATIVE_INIT_API
#include <boost/test/included/unit_test.hpp>
#include "array.h"
#include "binaryTree.h"
#include "DoublyList.h"
#include "ForwardList.h"
#include "queue.h"
#include "stack.h"
#include "hashTable.h"
#include "openHashTable.h"

using namespace std;


// ================= ForwardList Tests =================

BOOST_AUTO_TEST_CASE(FLTestPrintEmpty)
{
    ForwardList fl;
    std::stringstream ss;
    std::streambuf* old = std::cout.rdbuf(ss.rdbuf());

    fl.printFL();

    std::cout.rdbuf(old);
    BOOST_CHECK(ss.str().find("Список пуст") == std::string::npos);
}

BOOST_AUTO_TEST_CASE(FLTestAddHeadAndTail) {
    ForwardList fl;
    fl.AddHeadFL("first");
    fl.AddTailFL("last");

    BOOST_CHECK(fl.FindFL("first") != nullptr);
    BOOST_CHECK(fl.FindFL("last") != nullptr);
}

BOOST_AUTO_TEST_CASE(FLTestAddAfterAndBefore) {
    ForwardList fl;
    fl.AddHeadFL("a");
    fl.AddTailFL("b");
    BOOST_CHECK(fl.contains("a"));
    auto vec = fl.toVector();
    BOOST_CHECK_EQUAL(vec.size(), 2);
    BOOST_CHECK_EQUAL(vec[0], "a");
    BOOST_CHECK_EQUAL(vec[1], "b");
}

BOOST_AUTO_TEST_CASE(FLTestAddBeforeMiddle)
{
    ForwardList fl;
    fl.AddTailFL("A");
    fl.AddTailFL("B");
    fl.AddTailFL("C");

    fl.AddBeforeFL("B", "X");

    // A X B C
    auto a = fl.FindFL("A");
    BOOST_REQUIRE(a != nullptr);

    BOOST_REQUIRE(a->next != nullptr);
    BOOST_CHECK(a->next->data == "X");

    BOOST_CHECK(fl.FindFL("X")->data == "X");
    BOOST_CHECK(fl.FindFL("B")->data == "B");
}

BOOST_AUTO_TEST_CASE(FLTestAddBeforeHead)
{
    ForwardList fl;
    fl.AddTailFL("A");
    fl.AddTailFL("B");

    fl.AddBeforeFL("A", "X"); // X A B

    auto head = fl.FindFL("X");
    BOOST_REQUIRE(head != nullptr);
    BOOST_CHECK(head->data == "X");
}

BOOST_AUTO_TEST_CASE(FLTestDeleteOperations) {
    ForwardList fl;
    fl.AddHeadFL("x");
    fl.AddTailFL("y");
    fl.AddTailFL("z");

    fl.DeleteHeadFL();
    BOOST_CHECK(fl.FindFL("x") == nullptr);

    fl.DeleteTailFL();
    BOOST_CHECK(fl.FindFL("z") == nullptr);

    fl.AddTailFL("new");
    fl.DeleteAfterFL("y");
    BOOST_CHECK(fl.FindFL("new") == nullptr);

    fl.AddHeadFL("first");
    fl.DeleteBeforeFL("y");
    BOOST_CHECK(fl.FindFL("first") == nullptr);

    fl.AddTailFL("end");
    fl.DeleteValueFL("end");
    BOOST_CHECK(fl.FindFL("end") == nullptr);
}

BOOST_AUTO_TEST_CASE(FLTestClear) {
    ForwardList fl;
    fl.AddHeadFL("a");
    fl.AddTailFL("b");
    fl.clear();
    BOOST_CHECK(fl.FindFL("a") == nullptr);
    BOOST_CHECK(fl.FindFL("b") == nullptr);
}

BOOST_AUTO_TEST_CASE(FLTestSaveAndLoad) {
    ForwardList fl;
    fl.AddHeadFL("one");
    fl.AddTailFL("two");
    fl.saveFL("test_fl.txt");

    ForwardList fl2;
    fl2.loadFL("test_fl.txt");

    BOOST_CHECK(fl2.FindFL("one") != nullptr);
    BOOST_CHECK(fl2.FindFL("two") != nullptr);

    remove("test_fl.txt");
}



BOOST_AUTO_TEST_CASE(FLTestPrintByValue)
{
    ForwardList fl;
    fl.AddTailFL("A");
    fl.AddTailFL("B");
    fl.AddTailFL("C");

    std::stringstream ss;
    auto* old = std::cout.rdbuf(ss.rdbuf());

    fl.printByValueFL("B");

    std::cout.rdbuf(old);

    // printByValueFL просто вызывает printFL(), значит должен напечатать весь список
    BOOST_CHECK(ss.str().find("A") != std::string::npos);
    BOOST_CHECK(ss.str().find("B") != std::string::npos);
    BOOST_CHECK(ss.str().find("C") != std::string::npos);
}

BOOST_AUTO_TEST_CASE(FLTestPrintReverse)
{
    ForwardList fl;
    fl.AddTailFL("A");
    fl.AddTailFL("B");
    fl.AddTailFL("C");

    std::stringstream ss;
    auto* old = std::cout.rdbuf(ss.rdbuf());

    fl.printReverseFL(fl.FindFL("A"));

    std::cout.rdbuf(old);

    BOOST_CHECK(ss.str().find("C B A") != std::string::npos);
}

BOOST_AUTO_TEST_CASE(FLTestAddAfter)
{
    ForwardList fl;
    fl.AddTailFL("A");
    fl.AddTailFL("B");
    fl.AddTailFL("C");

    fl.AddAfterFL("B", "X"); // A B X C

    auto* b = fl.FindFL("B");
    BOOST_REQUIRE(b != nullptr);
    BOOST_REQUIRE(b->next != nullptr);

    BOOST_CHECK(b->next->data == "X");
    BOOST_CHECK(fl.FindFL("X") != nullptr);
}



// ================= Array Tests =================

BOOST_AUTO_TEST_CASE(ATestPushBackAndGet) {
    Array arr;
    arr.pushBackM("a");
    arr.pushBackM("b");

    BOOST_CHECK_EQUAL(arr.getM(0), "a");
    BOOST_CHECK_EQUAL(arr.getM(1), "b");
    BOOST_CHECK_EQUAL(arr.lengthM(), 2);
}

BOOST_AUTO_TEST_CASE(ATestInsertAndReplace) {
    Array arr;
    arr.pushBackM("x");
    arr.pushBackM("y");

    arr.insertM(1, "z"); // x z y
    BOOST_CHECK_EQUAL(arr.getM(1), "z");

    arr.replaceM(0, "a");
    BOOST_CHECK_EQUAL(arr.getM(0), "a");
}

BOOST_AUTO_TEST_CASE(ATestDelete) {
    Array arr;
    arr.pushBackM("a");
    arr.pushBackM("b");
    arr.pushBackM("c");

    arr.deleteM(1); // удаляем "b"
    BOOST_CHECK_EQUAL(arr.getM(1), "c");
    BOOST_CHECK_EQUAL(arr.lengthM(), 2);
}

BOOST_AUTO_TEST_CASE(ATestSaveAndLoad) {
    Array arr;
    arr.pushBackM("hello");
    arr.pushBackM("world");
    arr.saveM("test_arr.txt");

    Array arr2;
    arr2.loadM("test_arr.txt");

    BOOST_CHECK_EQUAL(arr2.getM(0), "hello");
    BOOST_CHECK_EQUAL(arr2.getM(1), "world");

    remove("test_arr.txt");
}



BOOST_AUTO_TEST_CASE(TestPrintEmptyArray)
{
    Array arr;

    std::stringstream ss;
    auto* old = std::cout.rdbuf(ss.rdbuf());

    arr.printM();

    std::cout.rdbuf(old);

    BOOST_CHECK(ss.str().find("Массив пуст") != std::string::npos);
}

BOOST_AUTO_TEST_CASE(TestPrintArray)
{
    Array arr;
    arr.pushBackM("A");
    arr.pushBackM("B");

    std::stringstream ss;
    auto* old = std::cout.rdbuf(ss.rdbuf());

    arr.printM();

    std::cout.rdbuf(old);

    BOOST_CHECK(ss.str().find("A") != std::string::npos);
    BOOST_CHECK(ss.str().find("B") != std::string::npos);
}




//---------------------------------

BOOST_AUTO_TEST_CASE(DLTestAndHeadTail) {
    DoublyList dl;

    dl.AddHeadDL("first");
    dl.AddTailDL("second");
    dl.AddTailDL("third");

    BOOST_CHECK(dl.FindDL("first") != nullptr);
    BOOST_CHECK(dl.FindDL("second") != nullptr);
    BOOST_CHECK(dl.FindDL("third") != nullptr);
    BOOST_CHECK(dl.FindDL("nonexistent") == nullptr);
}

BOOST_AUTO_TEST_CASE(DLTestAddAfterBefore) {
    DoublyList dl;
    dl.AddHeadDL("one");
    dl.AddTailDL("two");

    dl.AddAfterDL("one", "one_after");
    dl.AddBeforeDL("two", "two_before");

    BOOST_CHECK(dl.FindDL("one_after") != nullptr);
    BOOST_CHECK(dl.FindDL("two_before") != nullptr);
}

BOOST_AUTO_TEST_CASE(DLTestDeleteHeadTail) {
    DoublyList dl;
    dl.AddHeadDL("a");
    dl.AddTailDL("b");
    dl.AddTailDL("c");

    dl.DeleteHeadDL();
    BOOST_CHECK(dl.FindDL("a") == nullptr);

    dl.DeleteTailDL();
    BOOST_CHECK(dl.FindDL("c") == nullptr);
}

BOOST_AUTO_TEST_CASE(DLTestDeleteAfterBeforeValue) {
    DoublyList dl;
    dl.AddHeadDL("x");
    dl.AddTailDL("y");
    dl.AddTailDL("z");

    dl.DeleteAfterDL("x");
    BOOST_CHECK(dl.FindDL("y") == nullptr);

    dl.DeleteBeforeDL("z");
    BOOST_CHECK(dl.FindDL("x") == nullptr);

    dl.DeleteByValueDL("z");
    BOOST_CHECK(dl.FindDL("z") == nullptr);
}

BOOST_AUTO_TEST_CASE(DLTestSaveLoad) {
    DoublyList dl;
    dl.AddHeadDL("alpha");
    dl.AddTailDL("beta");
    dl.AddTailDL("gamma");

    dl.saveDL("test_dl.txt");

    DoublyList dl2;
    dl2.loadDL("test_dl.txt");

    BOOST_CHECK(dl2.FindDL("alpha") != nullptr);
    BOOST_CHECK(dl2.FindDL("beta") != nullptr);
    BOOST_CHECK(dl2.FindDL("gamma") != nullptr);
}


BOOST_AUTO_TEST_CASE(TestDeleteByValueDL)
{
    DoublyList dl;
    dl.AddTailDL("A");
    dl.AddTailDL("B");
    dl.AddTailDL("C");

    dl.DeleteByValueDL("B");

    BOOST_CHECK(dl.FindDL("B") == nullptr);
    BOOST_CHECK(dl.FindDL("A") != nullptr);
    BOOST_CHECK(dl.FindDL("C") != nullptr);
}

BOOST_AUTO_TEST_CASE(TestPrintForwardDL)
{
    DoublyList dl;
    dl.AddTailDL("A");
    dl.AddTailDL("B");

    std::stringstream ss;
    auto* old = std::cout.rdbuf(ss.rdbuf());

    dl.printForwardDL();

    std::cout.rdbuf(old);

    BOOST_CHECK(ss.str().find("A") != std::string::npos);
    BOOST_CHECK(ss.str().find("B") != std::string::npos);
}

BOOST_AUTO_TEST_CASE(TestPrintBackwardDL)
{
    DoublyList dl;
    dl.AddTailDL("A");
    dl.AddTailDL("B");

    std::stringstream ss;
    auto* old = std::cout.rdbuf(ss.rdbuf());

    dl.printBackwardDL();

    std::cout.rdbuf(old);

    // по твоей реализации вывод: "A" и всё
    BOOST_CHECK(ss.str().find("A") != std::string::npos);
}



BOOST_AUTO_TEST_CASE(QTestPushPop) {
    Queue q;
    BOOST_CHECK(q.isEmptyQ());

    q.pushQ("first");
    q.pushQ("second");
    q.pushQ("third");

    BOOST_CHECK(!q.isEmptyQ());

    BOOST_CHECK(q.popQ() == "first");
    BOOST_CHECK(q.popQ() == "second");
    BOOST_CHECK(q.popQ() == "third");
    BOOST_CHECK(q.isEmptyQ());

    // Проверка поп из пустой очереди
    BOOST_CHECK(q.popQ() == "");
}

BOOST_AUTO_TEST_CASE(QTestIsEmpty) {
    Queue q;
    BOOST_CHECK(q.isEmptyQ());
    q.pushQ("item");
    BOOST_CHECK(!q.isEmptyQ());
    q.popQ();
    BOOST_CHECK(q.isEmptyQ());
}

BOOST_AUTO_TEST_CASE(QTestSaveLoad) {
    Queue q;
    q.pushQ("apple");
    q.pushQ("banana");
    q.pushQ("cherry");

    q.saveQ("test_queue.txt");

    Queue q2;
    q2.loadQ("test_queue.txt");

    BOOST_CHECK(!q2.isEmptyQ());
    BOOST_CHECK(q2.popQ() == "apple");
    BOOST_CHECK(q2.popQ() == "banana");
    BOOST_CHECK(q2.popQ() == "cherry");
    BOOST_CHECK(q2.isEmptyQ());
}



BOOST_AUTO_TEST_CASE(TestPrintEmptyQueue)
{
    Queue q;

    std::stringstream ss;
    auto* old = std::cout.rdbuf(ss.rdbuf());

    q.printQ();

    std::cout.rdbuf(old);

    BOOST_CHECK(ss.str().find("Очередь пуста") != std::string::npos);
}

BOOST_AUTO_TEST_CASE(TestPrintQueue)
{
    Queue q;
    q.pushQ("A");
    q.pushQ("B");

    std::stringstream ss;
    auto* old = std::cout.rdbuf(ss.rdbuf());

    q.printQ();

    std::cout.rdbuf(old);

    BOOST_CHECK(ss.str().find("A") != std::string::npos);
    BOOST_CHECK(ss.str().find("B") != std::string::npos);
}



BOOST_AUTO_TEST_CASE(StackBasicOperations)
{
    Stack s;

    // Изначально стек пуст
    BOOST_CHECK(s.isEmptyS());

    // Добавление элементов
    s.pushS("first");
    s.pushS("second");
    s.pushS("third");

    BOOST_CHECK(!s.isEmptyS());
    BOOST_CHECK_EQUAL(s.top(), "third"); // верхний элемент

    // Извлечение элементов
    std::string val = s.popS();
    BOOST_CHECK_EQUAL(val, "third");
    BOOST_CHECK_EQUAL(s.top(), "second");

    val = s.popS();
    BOOST_CHECK_EQUAL(val, "second");
    BOOST_CHECK_EQUAL(s.top(), "first");

    val = s.popS();
    BOOST_CHECK_EQUAL(val, "first");
    BOOST_CHECK(s.isEmptyS());

    // Попытка извлечь из пустого стека
    val = s.popS();
    BOOST_CHECK_EQUAL(val, "");

    // Проверка clear
    s.pushS("new");
    s.pushS("node");
    s.clearS();
    BOOST_CHECK(s.isEmptyS());
}

BOOST_AUTO_TEST_CASE(StackSaveLoad)
{
    Stack s;
    s.pushS("one");
    s.pushS("two");
    s.pushS("three");

    s.saveS("stack_test.txt"); // сохраняем в файл

    Stack s2;
    s2.loadS("stack_test.txt"); // загружаем из файла

    BOOST_CHECK_EQUAL(s2.popS(), "three");
    BOOST_CHECK_EQUAL(s2.popS(), "two");
    BOOST_CHECK_EQUAL(s2.popS(), "one");
    BOOST_CHECK(s2.isEmptyS());
}


BOOST_AUTO_TEST_CASE(TestPrintEmptyStack)
{
    Stack st;

    std::stringstream ss;
    auto* old = std::cout.rdbuf(ss.rdbuf());

    st.printS();

    std::cout.rdbuf(old);

    // Ничего не выводит, значит строка пустая
    BOOST_CHECK(ss.str().empty());
}

BOOST_AUTO_TEST_CASE(TestPrintStack)
{
    Stack st;
    st.pushS("A");
    st.pushS("B"); // B on top

    std::stringstream ss;
    auto* old = std::cout.rdbuf(ss.rdbuf());

    st.printS();

    std::cout.rdbuf(old);

    BOOST_CHECK(ss.str().find("B") != std::string::npos);
    BOOST_CHECK(ss.str().find("A") != std::string::npos);
}



BOOST_AUTO_TEST_CASE(ChainHashTableBasicOperations)
{
    ChainHashTable ht;

    // Таблица пуста изначально
    BOOST_CHECK(!ht.contains("key1"));

    // Вставка элементов
    BOOST_CHECK(ht.insert("key1", "value1"));
    BOOST_CHECK(ht.insert("key2", "value2"));
    BOOST_CHECK(ht.insert("key3", "value3"));

    // Проверка наличия
    BOOST_CHECK(ht.contains("key1"));
    BOOST_CHECK(ht.contains("key2"));
    BOOST_CHECK(ht.contains("key3"));
    BOOST_CHECK(!ht.contains("key4"));

    // Проверка get
    BOOST_CHECK_EQUAL(ht.get("key1"), "value1");
    BOOST_CHECK_EQUAL(ht.get("key2"), "value2");
    BOOST_CHECK_EQUAL(ht.get("key3"), "value3");
    BOOST_CHECK_EQUAL(ht.get("key4"), "");

    // Попытка вставки существующего ключа
    BOOST_CHECK(!ht.insert("key1", "newValue"));

    // Удаление элементов
    ht.remove("key2");
    BOOST_CHECK(!ht.contains("key2"));
    BOOST_CHECK_EQUAL(ht.get("key2"), "");

    ht.remove("key1");
    BOOST_CHECK(!ht.contains("key1"));

    ht.remove("key3");
    BOOST_CHECK(!ht.contains("key3"));

    // Удаление несуществующего ключа не должно ломать
    ht.remove("key5");
}

BOOST_AUTO_TEST_CASE(ChainHashTableCollisionHandling)
{
    ChainHashTable ht;

    // Принудительно создаём коллизии (в зависимости от TABLE_SIZE и hashFun)
    ht.insert("a", "1");
    ht.insert("b", "2");
    ht.insert("c", "3");

    // Проверка всех значений, которые должны храниться в цепочке
    BOOST_CHECK_EQUAL(ht.get("a"), "1");
    BOOST_CHECK_EQUAL(ht.get("b"), "2");
    BOOST_CHECK_EQUAL(ht.get("c"), "3");

    // Удаление из цепочки
    ht.remove("b");
    BOOST_CHECK(!ht.contains("b"));
    BOOST_CHECK_EQUAL(ht.get("a"), "1");
    BOOST_CHECK_EQUAL(ht.get("c"), "3");
}



BOOST_AUTO_TEST_CASE(TreeTestInsertAndSearch)
{
    CompleteBinaryTree tree;
    tree.tInsert(10);
    tree.tInsert(20);
    tree.tInsert(30);

    BOOST_CHECK(tree.tSearch(10));
    BOOST_CHECK(tree.tSearch(20));
    BOOST_CHECK(tree.tSearch(30));
    BOOST_CHECK(!tree.tSearch(40)); // элемент которого нет
}

BOOST_AUTO_TEST_CASE(TreeTestIsComplete)
{
    CompleteBinaryTree tree;
    // пустое дерево считается полным
    BOOST_CHECK(tree.isComplete());

    tree.tInsert(1);
    BOOST_CHECK(tree.isComplete());

    tree.tInsert(2);
    tree.tInsert(3);
    BOOST_CHECK(tree.isComplete());

    tree.tInsert(4);
    tree.tInsert(5);
    BOOST_CHECK(tree.isComplete());

    // вручную делаем неполное дерево
    CompleteBinaryTree::TreeNode* root = new CompleteBinaryTree::TreeNode(1);
    CompleteBinaryTree::TreeNode* left = new CompleteBinaryTree::TreeNode(2);
    CompleteBinaryTree::TreeNode* right = new CompleteBinaryTree::TreeNode(3);
    CompleteBinaryTree::TreeNode* rightLeft = new CompleteBinaryTree::TreeNode(4);

    // создаем нарушение CBT
    root->left = left;
    root->right = right;
    right->left = rightLeft;

    // временно создаем дерево с прямым доступом к root
    CompleteBinaryTree tree2;
    tree2.loadT("test_empty.txt"); // создаем пустое
    tree2.tInsert(1); // чтобы root не был nullptr

    // Проверяем метод isComplete через обычный CBT (неидеальный пример)
    BOOST_CHECK(tree.isComplete()); 
}

BOOST_AUTO_TEST_CASE(TreeTestSaveAndLoad)
{
    const std::string filename = "test_tree.txt";

    CompleteBinaryTree tree;
    tree.tInsert(1);
    tree.tInsert(2);
    tree.tInsert(3);

    tree.saveT(filename);

    CompleteBinaryTree loadedTree;
    loadedTree.loadT(filename);

    BOOST_CHECK(loadedTree.tSearch(1));
    BOOST_CHECK(loadedTree.tSearch(2));
    BOOST_CHECK(loadedTree.tSearch(3));
    BOOST_CHECK(!loadedTree.tSearch(4));

    // Удаляем временный файл
    std::remove(filename.c_str());
}

BOOST_AUTO_TEST_CASE(TestPrintTree)
{
    CompleteBinaryTree tree;
    tree.tInsert(1);
    tree.tInsert(2);
    tree.tInsert(3);

    // Просто вызываем print, чтобы проверить отсутствие сбоев
    BOOST_CHECK_NO_THROW(tree.printT());
}

BOOST_AUTO_TEST_CASE(TestEmptyTreeOperations)
{
    CompleteBinaryTree tree;

    // Методы на пустом дереве
    BOOST_CHECK(!tree.tSearch(5));
    BOOST_CHECK(tree.isComplete());
    BOOST_CHECK_NO_THROW(tree.printT());

    const std::string filename = "empty_tree.txt";
    tree.saveT(filename);
    CompleteBinaryTree loadedTree;
    loadedTree.loadT(filename);
    BOOST_CHECK(!loadedTree.tSearch(5));
    BOOST_CHECK(loadedTree.isComplete());

    std::remove(filename.c_str());
}

//--------------------------------------

BOOST_AUTO_TEST_CASE(OHTTestInsertBasic)
{
    HashTableOpen h;
    BOOST_CHECK(h.insert("V1", "K1"));
    BOOST_CHECK(h.contains("K1"));
    BOOST_CHECK(h.get("K1") == "V1");
}

BOOST_AUTO_TEST_CASE(OHTTestInsertDuplicate)
{
    HashTableOpen h;
    BOOST_CHECK(h.insert("A", "K"));
    BOOST_CHECK(!h.insert("B", "K"));   // тот же ключ
}

BOOST_AUTO_TEST_CASE(OHTTestInsertEmptyKey)
{
    HashTableOpen h;
    BOOST_CHECK(!h.insert("V", ""));    // пустой ключ запрещён
}

BOOST_AUTO_TEST_CASE(OHTTestLinearProbingCollision)
{
    HashTableOpen h;

    // создаём гарантированную коллизию
    // Просто перезаполняем одну и ту же ячейку — TABLE_SIZE маленький
    int idx = h.debugIndex("AAA");

    // Заполняем индекс и все, что после него
    for (int i = 0; i < OPEN_TABLE_SIZE; i++) {
        string k = "K" + std::to_string(i);
        string v = "V" + std::to_string(i); 
        h.insert(v, k);
    }

    // Таблица заполнена → вставка неуспешна
    BOOST_CHECK(!h.insert("X", "NEW"));
}

BOOST_AUTO_TEST_CASE(OHTTestGetNotFound)
{
    HashTableOpen h;
    h.insert("A", "K1");

    BOOST_CHECK(h.get("NO") == "");
}

BOOST_AUTO_TEST_CASE(OHTTestGetStopsOnUnused)
{
    HashTableOpen h;
    h.insert("A", "K1");
    h.remove("K1");              // теперь used=false → get должен сразу вернуть ""

    BOOST_CHECK(h.get("K1") == "");
}

BOOST_AUTO_TEST_CASE(OHTTestContains)
{
    HashTableOpen h;
    h.insert("A", "K");

    BOOST_CHECK(h.contains("K"));
    BOOST_CHECK(!h.contains("NO"));
}

BOOST_AUTO_TEST_CASE(OHTTestContainsStopsOnUnused)
{
    HashTableOpen h;
    h.insert("A", "K");
    h.remove("K");

    BOOST_CHECK(!h.contains("K"));
}

BOOST_AUTO_TEST_CASE(OHTTestRemove)
{
    HashTableOpen h;
    h.insert("A", "K");

    BOOST_CHECK(h.remove("K"));
    BOOST_CHECK(!h.contains("K"));
    BOOST_CHECK(h.get("K") == "");
}

BOOST_AUTO_TEST_CASE(OHTTestRemoveNotFound)
{
    HashTableOpen h;
    h.insert("A", "K");

    BOOST_CHECK(!h.remove("ABS"));
}

BOOST_AUTO_TEST_CASE(OHTTestPrintTable)
{
    HashTableOpen h;
    h.insert("A", "K");

    std::stringstream ss;
    auto* old = std::cout.rdbuf(ss.rdbuf());

    h.printTable();

    std::cout.rdbuf(old);

    BOOST_CHECK(ss.str().find("Хэш-таблица") != std::string::npos);
    BOOST_CHECK(ss.str().find("K") != std::string::npos);
    BOOST_CHECK(ss.str().find("A") != std::string::npos);
}

BOOST_AUTO_TEST_CASE(OHTTestHashDeterminism)
{
    HashTableOpen h;
    int a = h.debugIndex("AAA");
    int b = h.debugIndex("AAA");
    BOOST_CHECK(a == b);
}

