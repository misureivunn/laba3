#include "array.h"
#include "binaryTree.h"
#include "DoublyList.h"
#include "ForwardList.h"
#include "queue.h"
#include "stack.h"
#include "hashTable.h"
#include "openHashTable.h"
#include <gtest/gtest.h>

using namespace std;
TEST(ForwardListTest, AddHeadTailContains) {
    ForwardList fl;

    fl.AddHeadFL("B");
    fl.AddHeadFL("A");
    fl.AddTailFL("C");

    EXPECT_TRUE(fl.contains("A"));
    EXPECT_TRUE(fl.contains("B"));
    EXPECT_TRUE(fl.contains("C"));
    EXPECT_FALSE(fl.contains("X"));
}


TEST(ForwardListTest, AddBeforeAfter) {
    ForwardList fl;
    fl.AddTailFL("A");
    fl.AddTailFL("C");

    fl.AddBeforeFL("C", "B"); // A B C
    fl.AddAfterFL("B", "X");  // A B X C

    auto v = fl.toVector();
    EXPECT_EQ(v, (std::vector<std::string>{"A","B","X","C"}));
}

TEST(ForwardListTest, DeleteOperations) {
    ForwardList fl;
    fl.AddTailFL("A");
    fl.AddTailFL("B");
    fl.AddTailFL("C");

    fl.DeleteHeadFL();        // B C
    fl.DeleteAfterFL("B");   // B
    fl.AddTailFL("D");       // B D
    fl.DeleteBeforeFL("D");  // D
    fl.DeleteValueFL("D");   // empty

    EXPECT_FALSE(fl.contains("B"));
    EXPECT_FALSE(fl.contains("D"));
}

TEST(ForwardListTest, FindAndAddNode) {
    ForwardList fl;
    fl.AddTailFL("A");
    fl.AddTailFL("C");

    auto* a = fl.FindFL("A");
    ASSERT_NE(a, nullptr);

    fl.AddNodeFL(a, "B"); // A B C
    EXPECT_TRUE(fl.contains("B"));
}

TEST(ForwardListTest, PrintFunctions) {
    ForwardList fl;
    fl.AddTailFL("A");
    fl.AddTailFL("B");
    fl.AddTailFL("C");

    std::stringstream ss;
    auto* old = std::cout.rdbuf(ss.rdbuf());

    fl.printFL();
    fl.printReverseFL(fl.FindFL("A"));

    std::cout.rdbuf(old);

    EXPECT_NE(ss.str().find("A"), std::string::npos);
    EXPECT_NE(ss.str().find("C"), std::string::npos);
}


TEST(ForwardListTest, SaveLoad) {
    ForwardList fl;
    fl.AddTailFL("one");
    fl.AddTailFL("two");

    fl.saveFL("fl_test.txt");

    ForwardList fl2;
    fl2.loadFL("fl_test.txt");

    EXPECT_TRUE(fl2.contains("one"));
    EXPECT_TRUE(fl2.contains("two"));

    std::remove("fl_test.txt");
}


TEST(ForwardListTest, EmptyCases) {
    ForwardList fl;

    fl.DeleteHeadFL();
    fl.DeleteTailFL();
    fl.DeleteAfterFL("X");
    fl.DeleteBeforeFL("X");
    fl.DeleteValueFL("X");
    fl.printReverseFL(nullptr);

    EXPECT_FALSE(fl.contains("X"));
}

TEST(ForwardListCoverage, EmptyListBranches) {
    ForwardList fl;

    fl.AddAfterFL("X", "Y");
    fl.AddBeforeFL("X", "Y");
    fl.DeleteAfterFL("X");
    fl.DeleteBeforeFL("X");
    fl.DeleteValueFL("X");

    EXPECT_EQ(fl.FindFL("X"), nullptr);
}

TEST(ForwardListCoverage, AddBeforeEdgeCases) {
    ForwardList fl;

    fl.AddTailFL("A");

    // target = head
    fl.AddBeforeFL("A", "X");
    EXPECT_TRUE(fl.contains("X"));

}

TEST(ForwardListCoverage, FindNullptr) {
    ForwardList fl;
    fl.AddTailFL("A");

    EXPECT_EQ(fl.FindFL("B"), nullptr);
}

TEST(ForwardListCoverage, PrintByValue) {
    ForwardList fl;
    fl.AddTailFL("A");
    fl.AddTailFL("B");

    std::stringstream ss;
    auto* old = std::cout.rdbuf(ss.rdbuf());

    fl.printByValueFL("B");

    std::cout.rdbuf(old);

    EXPECT_NE(ss.str().find("A"), std::string::npos);
    EXPECT_NE(ss.str().find("B"), std::string::npos);
}

TEST(ForwardListCoverage, PrintReverseNullptr) {
    ForwardList fl;

    std::stringstream ss;
    auto* old = std::cout.rdbuf(ss.rdbuf());

    fl.printReverseFL(nullptr);

    std::cout.rdbuf(old);

    EXPECT_EQ(ss.str(), "\n");
}

TEST(ForwardListCoverage, LoadNonexistentFile) {
    ForwardList fl;
    fl.loadFL("definitely_not_exists.txt");

    EXPECT_FALSE(fl.contains("anything"));
}
//----------------------------------

static string captureOutput(function<void()> fn)
{
    stringstream ss;
    auto* old = cout.rdbuf(ss.rdbuf());
    fn();
    cout.rdbuf(old);
    return ss.str();
}

TEST(DoublyList, AddAndFind)
{
    DoublyList dl;
    dl.AddHeadDL("B");
    dl.AddHeadDL("A");
    dl.AddTailDL("C");

    EXPECT_NE(dl.FindDL("A"), nullptr);
    EXPECT_NE(dl.FindDL("B"), nullptr);
    EXPECT_NE(dl.FindDL("C"), nullptr);
    EXPECT_EQ(dl.FindDL("X"), nullptr);
}

TEST(DoublyList, AddAfterAndBefore)
{
    DoublyList dl;
    dl.AddTailDL("A");
    dl.AddTailDL("C");

    dl.AddAfterDL("A", "B");      // A B C
    dl.AddBeforeDL("A", "START"); // START A B C
    dl.AddAfterDL("C", "END");    // START A B C END

    EXPECT_NE(dl.FindDL("START"), nullptr);
    EXPECT_NE(dl.FindDL("B"), nullptr);
    EXPECT_NE(dl.FindDL("END"), nullptr);
}

TEST(DoublyList, AddAfterBeforeEmpty)
{
    DoublyList dl;

    string out = captureOutput([&] {
        dl.AddAfterDL("A", "B");
        dl.AddBeforeDL("A", "B");
    });

    EXPECT_NE(out.find("Список пуст"), string::npos);
}

TEST(DoublyList, DeleteAllVariants)
{
    DoublyList dl;
    dl.AddTailDL("A");
    dl.AddTailDL("B");
    dl.AddTailDL("C");

    dl.DeleteHeadDL();            // remove A
    dl.DeleteTailDL();            // remove C
    dl.DeleteByValueDL("B");      // remove middle

    EXPECT_EQ(dl.FindDL("A"), nullptr);
    EXPECT_EQ(dl.FindDL("B"), nullptr);
    EXPECT_EQ(dl.FindDL("C"), nullptr);
}

TEST(DoublyList, DeleteAfterBefore)
{
    DoublyList dl;
    dl.AddTailDL("A");
    dl.AddTailDL("B");
    dl.AddTailDL("C");

    dl.DeleteAfterDL("A");        // delete B
    dl.AddTailDL("B"); //ACB
    dl.DeleteBeforeDL("B");       // delete A (C)

    EXPECT_NE(dl.FindDL("A"), nullptr);
    EXPECT_NE(dl.FindDL("B"), nullptr);
    EXPECT_EQ(dl.FindDL("C"), nullptr);
}

TEST(DoublyList, DeleteEdgeCases)
{
    DoublyList dl;

    string out = captureOutput([&] {
        dl.DeleteHeadDL();
        dl.DeleteTailDL();
        dl.DeleteAfterDL("X");
        dl.DeleteBeforeDL("X");
        dl.DeleteByValueDL("X");
    });

    EXPECT_NE(out.find("Список пуст"), string::npos);
}

TEST(DoublyList, Print)
{
    DoublyList dl;
    dl.AddTailDL("A");
    dl.AddTailDL("B");

    string fwd = captureOutput([&] { dl.printForwardDL(); });
    string bwd = captureOutput([&] { dl.printBackwardDL(); });

    EXPECT_NE(fwd.find("A"), string::npos);
    EXPECT_NE(bwd.find("A"), string::npos);
}

TEST(DoublyList, PrintEmpty)
{
    DoublyList dl;
    string out = captureOutput([&] { dl.printForwardDL(); });
    EXPECT_NE(out.find("Список пуст"), string::npos);
}


TEST(DoublyList, SaveLoad)
{
    DoublyList dl;
    dl.AddTailDL("X");
    dl.AddTailDL("Y");

    dl.saveDL("dl.txt");

    DoublyList dl2;
    dl2.loadDL("dl.txt");

    EXPECT_NE(dl2.FindDL("X"), nullptr);
    EXPECT_NE(dl2.FindDL("Y"), nullptr);

    remove("dl.txt");
}

TEST(DoublyList, LoadMissingFile)
{
    DoublyList dl;
    dl.loadDL("no_file.txt"); // if(!open) return
}

//-----------------------------------------

static string captureOut(function<void()> fn)
{
    stringstream ss;
    auto* old = cout.rdbuf(ss.rdbuf());
    fn();
    cout.rdbuf(old);
    return ss.str();
}


TEST(ArrayTest, PushBackAndGet)
{
    Array a;
    a.pushBackM("A");
    a.pushBackM("B");
    a.pushBackM("C"); // resize

    EXPECT_EQ(a.lengthM(), 3);
    EXPECT_EQ(a.getM(0), "A");
    EXPECT_EQ(a.getM(2), "C");
    EXPECT_EQ(a.getM(10), "");
}


TEST(ArrayTest, InsertValid)
{
    Array a;
    a.pushBackM("A");
    a.pushBackM("C");

    a.insertM(1, "B"); // A B C

    EXPECT_EQ(a.lengthM(), 3);
    EXPECT_EQ(a.getM(1), "B");
}

TEST(ArrayTest, InsertInvalid)
{
    Array a;
    string out = captureOut([&] {
        a.insertM(-1, "X");
        a.insertM(5, "Y");
    });

    EXPECT_NE(out.find("Ошибка"), string::npos);
}


TEST(ArrayTest, DeleteValid)
{
    Array a;
    a.pushBackM("A");
    a.pushBackM("B");
    a.pushBackM("C");

    a.deleteM(1); // remove B

    EXPECT_EQ(a.lengthM(), 2);
    EXPECT_EQ(a.getM(1), "C");
}

TEST(ArrayTest, DeleteInvalidAndEmpty)
{
    Array a;

    string out = captureOut([&] {
        a.deleteM(0);      // empty
        a.pushBackM("A");
        a.deleteM(5);      // invalid
    });

    EXPECT_NE(out.find("Массив пуст"), string::npos);
    EXPECT_NE(out.find("Ошибка"), string::npos);
}


TEST(ArrayTest, Replace)
{
    Array a;
    a.pushBackM("A");

    a.replaceM(0, "B");
    EXPECT_EQ(a.getM(0), "B");

    a.replaceM(5, "X"); // invalid, no crash
}

/* ===== Print ===== */

TEST(ArrayTest, Print)
{
    Array a;
    a.pushBackM("A");
    a.pushBackM("B");

    string out = captureOut([&] { a.printM(); });

    EXPECT_NE(out.find("A"), string::npos);
    EXPECT_NE(out.find("B"), string::npos);
}

TEST(ArrayTest, PrintEmpty)
{
    Array a;
    string out = captureOut([&] { a.printM(); });

    EXPECT_NE(out.find("Массив пуст"), string::npos);
}

/* ===== Save / Load ===== */

TEST(ArrayTest, SaveLoad)
{
    Array a;
    a.pushBackM("one");
    a.pushBackM("two");

    a.saveM("arr.txt");

    Array b;
    b.loadM("arr.txt");

    EXPECT_EQ(b.lengthM(), 2);
    EXPECT_EQ(b.getM(0), "one");
    EXPECT_EQ(b.getM(1), "two");

    remove("arr.txt");
}

TEST(ArrayTest, LoadMissingFile)
{
    Array a;
    a.loadM("no_file.txt"); // if(!file) return
}

/* ===== Constructor / isEmpty ===== */

TEST(QueueTest, EmptyOnCreate)
{
    Queue q;
    EXPECT_TRUE(q.isEmptyQ());
}

/* ===== push / pop ===== */

TEST(QueueTest, PushPopSingle)
{
    Queue q;
    q.pushQ("A");

    EXPECT_FALSE(q.isEmptyQ());
    EXPECT_EQ(q.popQ(), "A");
    EXPECT_TRUE(q.isEmptyQ());
}

TEST(QueueTest, PushPopMultiple)
{
    Queue q;
    q.pushQ("A");
    q.pushQ("B");
    q.pushQ("C");

    EXPECT_EQ(q.popQ(), "A");
    EXPECT_EQ(q.popQ(), "B");
    EXPECT_EQ(q.popQ(), "C");
    EXPECT_TRUE(q.isEmptyQ());
}

/* ===== pop empty ===== */

TEST(QueueTest, PopEmpty)
{
    Queue q;
    EXPECT_EQ(q.popQ(), "");
}

TEST(QueueTest, PrintEmpty)
{
    Queue q;
    string out = captureOut([&] { q.printQ(); });

    EXPECT_NE(out.find("Очередь пуста"), string::npos);
}

TEST(QueueTest, PrintNonEmpty)
{
    Queue q;
    q.pushQ("A");
    q.pushQ("B");

    string out = captureOut([&] { q.printQ(); });

    EXPECT_NE(out.find("A"), string::npos);
    EXPECT_NE(out.find("B"), string::npos);
}

TEST(QueueTest, SaveLoad)
{
    Queue q;
    q.pushQ("one");
    q.pushQ("two");
    q.pushQ("three");

    q.saveQ("queue.txt");

    Queue q2;
    q2.loadQ("queue.txt");

    EXPECT_EQ(q2.popQ(), "one");
    EXPECT_EQ(q2.popQ(), "two");
    EXPECT_EQ(q2.popQ(), "three");
    EXPECT_TRUE(q2.isEmptyQ());

    remove("queue.txt");
}

TEST(QueueTest, LoadMissingFile)
{
    Queue q;
    q.loadQ("no_such_file.txt"); // if(!fin) return
    EXPECT_TRUE(q.isEmptyQ());
}

TEST(QueueTest, DestructorCleanup)
{
    Queue* q = new Queue;
    q->pushQ("A");
    q->pushQ("B");
    q->pushQ("C");

    EXPECT_NO_THROW(delete q);
}

//----------------------------------------
TEST(StackTest, EmptyOnCreate) {
    Stack s;
    EXPECT_TRUE(s.isEmptyS());
    EXPECT_EQ(s.popS(), "");
    EXPECT_EQ(s.top(), "");
}

TEST(StackTest, PushPopTop) {
    Stack s;
    s.pushS("A");
    s.pushS("B");

    EXPECT_FALSE(s.isEmptyS());
    EXPECT_EQ(s.top(), "B");
    EXPECT_EQ(s.popS(), "B");
    EXPECT_EQ(s.popS(), "A");
    EXPECT_TRUE(s.isEmptyS());
}

// ---------- clear ----------

TEST(StackTest, ClearStack) {
    Stack s;
    s.pushS("1");
    s.pushS("2");
    s.clearS();

    EXPECT_TRUE(s.isEmptyS());
    EXPECT_EQ(s.popS(), "");
}

// ---------- print ----------

TEST(StackTest, PrintNonEmpty) {
    Stack s;
    s.pushS("A");
    s.pushS("B");

    testing::internal::CaptureStdout();
    s.printS();
    std::string out = testing::internal::GetCapturedStdout();

    EXPECT_NE(out.find("B"), std::string::npos);
    EXPECT_NE(out.find("A"), std::string::npos);
}

TEST(StackTest, PrintEmpty) {
    Stack s;
    testing::internal::CaptureStdout();
    s.printS();
    std::string out = testing::internal::GetCapturedStdout();

    EXPECT_TRUE(out.empty()); // у тебя вывод закомментирован
}

// ---------- save / load ----------

TEST(StackTest, SaveAndLoad) {
    Stack s;
    s.pushS("one");
    s.pushS("two");

    const std::string file = "stack_test.txt";
    s.saveS(file);

    Stack s2;
    s2.loadS(file);

    EXPECT_EQ(s2.popS(), "two");
    EXPECT_EQ(s2.popS(), "one");
    EXPECT_TRUE(s2.isEmptyS());

    std::remove(file.c_str());
}

TEST(StackTest, LoadFromMissingFile) {
    Stack s;
    s.loadS("no_such_file.txt");
    EXPECT_TRUE(s.isEmptyS());
}

#include <gtest/gtest.h>
#include <cstdio>
#include "binaryTree.h"

// ---------- базовые состояния ----------

TEST(BinaryTreeTest, EmptyTree) {
    CompleteBinaryTree t;
    EXPECT_FALSE(t.tSearch(10));
    EXPECT_TRUE(t.isComplete());
    EXPECT_NO_THROW(t.printT());
}

// ---------- вставка и поиск ----------

TEST(BinaryTreeTest, InsertAndSearch) {
    CompleteBinaryTree t;
    t.tInsert(1);
    t.tInsert(2);
    t.tInsert(3);
    t.tInsert(4);

    EXPECT_TRUE(t.tSearch(1));
    EXPECT_TRUE(t.tSearch(2));
    EXPECT_TRUE(t.tSearch(3));
    EXPECT_TRUE(t.tSearch(4));
    EXPECT_FALSE(t.tSearch(100));
}

// ---------- проверка complete ----------

TEST(BinaryTreeTest, IsCompleteTrue) {
    CompleteBinaryTree t;
    t.tInsert(1);
    t.tInsert(2);
    t.tInsert(3);
    t.tInsert(4);
    t.tInsert(5);

    EXPECT_TRUE(t.isComplete());
}

// ---------- печать ----------

TEST(BinaryTreeTest, PrintNonEmpty) {
    CompleteBinaryTree t;
    t.tInsert(10);
    t.tInsert(20);

    testing::internal::CaptureStdout();
    t.printT();
    std::string out = testing::internal::GetCapturedStdout();

    EXPECT_NE(out.find("10"), std::string::npos);
    EXPECT_NE(out.find("20"), std::string::npos);
}

// ---------- save / load ----------

TEST(BinaryTreeTest, SaveAndLoad) {
    CompleteBinaryTree t;
    t.tInsert(1);
    t.tInsert(2);
    t.tInsert(3);

    const std::string file = "tree_test.txt";
    t.saveT(file);

    CompleteBinaryTree t2;
    t2.loadT(file);

    EXPECT_TRUE(t2.tSearch(1));
    EXPECT_TRUE(t2.tSearch(2));
    EXPECT_TRUE(t2.tSearch(3));
    EXPECT_FALSE(t2.tSearch(99));

    std::remove(file.c_str());
}

TEST(BinaryTreeTest, SaveEmptyTree) {
    CompleteBinaryTree t;
    t.saveT("empty_tree.txt"); // просто не должно падать
    SUCCEED();
}

TEST(BinaryTreeTest, LoadMissingFile) {
    CompleteBinaryTree t;
    t.loadT("no_such_file.txt");
    EXPECT_TRUE(t.isComplete());
}

//--------------------------------------------

TEST(ChainHashTableTest, EmptyTable) {
    ChainHashTable ht;
    EXPECT_FALSE(ht.contains("a"));
    EXPECT_EQ(ht.get("a"), "");
}

// ---------- вставка и получение ----------

TEST(ChainHashTableTest, InsertAndGet) {
    ChainHashTable ht;

    EXPECT_TRUE(ht.insert("key1", "value1"));
    EXPECT_TRUE(ht.insert("key2", "value2"));

    EXPECT_TRUE(ht.contains("key1"));
    EXPECT_TRUE(ht.contains("key2"));
    EXPECT_EQ(ht.get("key1"), "value1");
    EXPECT_EQ(ht.get("key2"), "value2");
}

// ---------- дубликаты ----------

TEST(ChainHashTableTest, InsertDuplicate) {
    ChainHashTable ht;

    EXPECT_TRUE(ht.insert("dup", "one"));
    EXPECT_FALSE(ht.insert("dup", "two")); // уже есть
    EXPECT_EQ(ht.get("dup"), "one");
}

// ---------- коллизии ----------

TEST(ChainHashTableTest, CollisionHandling) {
    ChainHashTable ht;

    // несколько элементов в одну цепочку
    ht.insert("a", "1");
    ht.insert("b", "2");
    ht.insert("c", "3");

    EXPECT_EQ(ht.get("a"), "1");
    EXPECT_EQ(ht.get("b"), "2");
    EXPECT_EQ(ht.get("c"), "3");
}

// ---------- удаление ----------

TEST(ChainHashTableTest, RemoveElements) {
    ChainHashTable ht;

    ht.insert("x", "10");
    ht.insert("y", "20");
    ht.insert("z", "30");

    ht.remove("y");
    EXPECT_FALSE(ht.contains("y"));
    EXPECT_EQ(ht.get("y"), "");

    ht.remove("x");
    EXPECT_FALSE(ht.contains("x"));

    ht.remove("z");
    EXPECT_FALSE(ht.contains("z"));
}

// ---------- удаление несуществующего ----------

TEST(ChainHashTableTest, RemoveMissingKey) {
    ChainHashTable ht;
    ht.insert("a", "1");

    EXPECT_NO_THROW(ht.remove("no_key"));
    EXPECT_TRUE(ht.contains("a"));
}

TEST(OpenHashTableTest, InsertGetContains) {
    HashTableOpen h;

    EXPECT_TRUE(h.insert("V1", "K1"));
    EXPECT_TRUE(h.contains("K1"));
    EXPECT_EQ(h.get("K1"), "V1");

    EXPECT_FALSE(h.insert("V2", "K1"));   // дубликат
    EXPECT_FALSE(h.insert("V", ""));      // пустой ключ
}

// ---------- линейное пробирование + переполнение ----------

TEST(OpenHashTableTest, CollisionAndOverflow) {
    HashTableOpen h;

    for (int i = 0; i < OPEN_TABLE_SIZE; i++)
        EXPECT_TRUE(h.insert("V" + std::to_string(i), "K" + std::to_string(i)));

    EXPECT_FALSE(h.insert("X", "NEW")); // таблица заполнена
}

// ---------- remove + остановка на unused ----------

TEST(OpenHashTableTest, RemoveAndStopOnUnused) {
    HashTableOpen h;

    h.insert("A", "K");
    EXPECT_TRUE(h.remove("K"));

    EXPECT_FALSE(h.contains("K"));
    EXPECT_EQ(h.get("K"), "");

    EXPECT_FALSE(h.remove("NO")); // удаление отсутствующего
}

// ---------- get / contains на пустой таблице ----------

TEST(OpenHashTableTest, EmptyTable) {
    HashTableOpen h;
    EXPECT_EQ(h.get("X"), "");
    EXPECT_FALSE(h.contains("X"));
}

// ---------- print ----------

TEST(OpenHashTableTest, PrintTable) {
    HashTableOpen h;
    h.insert("A", "K");

    std::stringstream ss;
    auto* old = std::cout.rdbuf(ss.rdbuf());

    h.printTable();

    std::cout.rdbuf(old);

    EXPECT_NE(ss.str().find("Хэш-таблица"), std::string::npos);
    EXPECT_NE(ss.str().find("K"), std::string::npos);
    EXPECT_NE(ss.str().find("A"), std::string::npos);
}

// ---------- debugIndex ----------

TEST(OpenHashTableTest, DebugIndexDeterministic) {
    HashTableOpen h;
    EXPECT_EQ(h.debugIndex("AAA"), h.debugIndex("AAA"));
}