#include "DoublyList.h"

DoublyList::DoublyList() {
    head = nullptr;
    tail = nullptr;
}

DoublyList::~DoublyList(){
    while(head){
        NodeDoublyList* cur = head;
        head = head -> next;
        delete cur;
    }
}

void DoublyList::AddHeadDL(string value) {
    NodeDoublyList* newNode = new NodeDoublyList{value, nullptr, head};
    if (head != nullptr) //если первый не пустой
        head -> prev = newNode; //перед головой новая нода
    else
        tail = newNode; //иначе новая нода и голова и хвост
    head = newNode; //обновляем head
}

void DoublyList::AddTailDL(string value) {
    NodeDoublyList* newNode = new NodeDoublyList{value, tail, nullptr};
    if (tail != nullptr) //если последний не пустой
        tail -> next = newNode; //после хвоста - новая нода
    else
        head = newNode; 
    tail = newNode; // обновляем tail
}

DoublyList::NodeDoublyList* DoublyList::FindDL(string value) {
    NodeDoublyList* cur = head;
    while (cur != nullptr) {
        if (cur -> data == value) return cur;
        cur = cur -> next;
    }
    return nullptr;
}

void DoublyList::AddAfterDL(const string& target, const string& value) {
    if (!head) {
        cout << "Список пуст" << endl;
        return;
    }     
    NodeDoublyList* ptr = FindDL(target); //ищем узел
    if (ptr == nullptr) return;

    NodeDoublyList* newNode = new NodeDoublyList{value, ptr, ptr -> next};
    if (ptr -> next != nullptr)
        ptr -> next -> prev = newNode;//если есть, обновляем его prev
    else tail = newNode;
    ptr -> next = newNode;
}

void DoublyList::AddBeforeDL(const string& target, const string& value) {
    if (!head) {
        cout << "Список пуст" << endl;
        return;
    }
    NodeDoublyList* ptr = FindDL(target);
    if (ptr -> prev == nullptr){
        AddHeadDL(value);
        return;
    }
    //создаем ноду указывающую на предыдущую(prev) и текущую(next)
    NodeDoublyList* newNode = new NodeDoublyList{value, ptr -> prev, ptr};
    ptr -> prev -> next = newNode;
    ptr -> prev = newNode;
}


void DoublyList::DeleteHeadDL() {
    if (head == nullptr) return;
    NodeDoublyList* temp = head;
    head = head -> next; //сдвигаем head
    if (head != nullptr)
        head -> prev = nullptr;
    else
        tail = nullptr;
    delete temp;
}

void DoublyList::DeleteTailDL() {
    if (tail == nullptr) return;
    NodeDoublyList* temp = tail;
    tail = tail -> prev; //сдвигаем tail
    if (tail != nullptr)
        tail -> next = nullptr;
    else
        head = nullptr;
    delete temp;
}


void DoublyList::DeleteAfterDL(const string& target) {
    if (head == nullptr){
        cout << "Список пуст" << endl;
    }
    NodeDoublyList* ptr = FindDL(target); //находим узел
    if (ptr == nullptr) return;
    if (ptr -> next == nullptr) return;

    NodeDoublyList* temp = ptr -> next;
    ptr -> next = temp -> next; //переназначаем ptr->next
    if (temp -> next != nullptr)
        temp -> next -> prev = ptr;
    else tail = ptr; //обновляем хвост
    delete temp;
}

void DoublyList::DeleteBeforeDL(const string& target) {
    if (head == nullptr){
        cout << "Список пуст" << endl;
    }
    NodeDoublyList* ptr = FindDL(target);//находим узел
    if (ptr == nullptr) return;
    if (ptr -> prev == nullptr) return;

    NodeDoublyList* temp = ptr -> prev;
    ptr -> prev = temp -> prev;
    if (temp -> prev != nullptr)
        temp -> prev -> next = ptr; 
    else head = ptr; //обновляем голову
    delete temp;
}

void DoublyList::DeleteByValueDL(string value) {
    NodeDoublyList* node = FindDL(value);//находим узел
    if (node == nullptr) return;

    if (node == head) {
        DeleteHeadDL();
        return;
    }
    if (node == tail) {
        DeleteTailDL();
        return;
    }
    node -> prev -> next = node -> next; //переназначаем соседей
    node -> next -> prev = node -> prev;
    delete node;
}

void DoublyList::printForwardDL() {
    if (head == nullptr){
        cout << "Список пуст" << endl;
        return;
    }
    NodeDoublyList* cur = head;
    while (cur != nullptr) {
        cout << cur -> data << " ";
        cur = cur -> next;
    }
    cout << endl;
}

void DoublyList::printBackwardDL() {
    NodeDoublyList* cur = head;

    while (cur != nullptr) {
        cout << cur -> data << " ";
        cur = cur -> prev;
    }
    cout << endl;
}


void DoublyList::saveDL(const string& filename) { //сохранение в файл
    ofstream out(filename);
    NodeDoublyList* curr = head;
    while(curr != nullptr) { 
        out << curr -> data << endl; 
        curr = curr -> next; }
    out.close();
}

void DoublyList::loadDL(const string& filename) {//загрузка из файла
    ifstream in(filename);
    if(!in.is_open()) return;
    string value;
    head = tail = nullptr;
    while(getline(in,value)) 
        AddTailDL(value);
    in.close();
}