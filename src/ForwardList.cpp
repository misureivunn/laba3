
#include "ForwardList.h"


ForwardList::ForwardList(){
    head = nullptr;
}

ForwardList::~ForwardList(){
    clear();
}

void ForwardList::clear(){
    while(head != nullptr){
        NodeSinglyList* cur = head;
        head = head -> next;
        delete cur;
    }
}

bool ForwardList::contains(const std::string& value) const {
    NodeSinglyList* cur = head;
    while (cur != nullptr) {
        if (cur->data == value) return true;
        cur = cur->next;
    }
    return false;
}

std::vector<std::string> ForwardList::toVector() const {
    std::vector<std::string> out;
    NodeSinglyList* cur = head;
    while (cur) {
        out.push_back(cur->data);
        cur = cur->next;
    }
    return out;
}

void ForwardList::AddHeadFL(const string& data){//в начало
        NodeSinglyList* newHead = new NodeSinglyList {data, nullptr};//новый узел
        newHead -> next = head; //направляем на голову
        head = newHead; //новая голова
}

void ForwardList::AddTailFL(const string& data){//в конец
    NodeSinglyList* newNode = new NodeSinglyList{data, nullptr};
    if (head == nullptr) { //если список пуст
        head = newNode;
        return;
    }
    NodeSinglyList* curr = head; //проходим по списку
    while (curr -> next != nullptr){
        curr = curr -> next;
    }
    curr -> next = newNode; //добавляем новый узел в конец
}

void ForwardList::AddNodeFL(NodeSinglyList* ptr, const string& data){//создает ноду after
    NodeSinglyList* newNode = new NodeSinglyList {data, nullptr};
    newNode -> next = ptr -> next;
    ptr -> next = newNode; 
}

void ForwardList::AddAfterFL(const string& target, const string& data){//после элемента
    if (!head) {
        cout << "Список пуст" << endl;
        return;
    } 
    NodeSinglyList* ptr = FindFL(target); //находим узел
    if (ptr) AddNodeFL(ptr, data); //добавляем после узла
}

void ForwardList::AddBeforeFL(const string& target, const string& data){//перед элементом
    if (!head) {
        cout << "Список пуст" << endl;
        return;
    } 
    if (head -> data == target){
        AddHeadFL(data); //вставляем в начало
        return;
    }

    NodeSinglyList* curr = head; //перебираем элементы до элемента перед target 
    while (curr != nullptr && curr -> next != nullptr && curr -> next -> data != target){
        curr = curr -> next;
    }
    AddNodeFL(curr, data); 
}


void ForwardList::DeleteHeadFL(){
    if (head == nullptr) 
        return;
    NodeSinglyList* ptr = head; //запоминаем первый элемент
    head = head -> next; //переназначаем head
    delete ptr; //удаляем первый элемент
}

void ForwardList::DeleteTailFL(){
    if (head == nullptr) return;
    if (head -> next == nullptr){ //если один элемент то удаляем голову
        delete head;
        head = nullptr;
        return;
    }
    NodeSinglyList* curr = head;
    while (curr -> next -> next != nullptr){ //идем до предпоследнего узла
        curr = curr -> next;
    }
    delete curr -> next; //удаляем последний
    curr -> next = nullptr;
}

void ForwardList::DeleteAfterFL(const string& target){
    if (head == nullptr) return;
    NodeSinglyList* ptr = FindFL(target);//ищем узел

    if (ptr == nullptr || ptr -> next == nullptr) return;
    NodeSinglyList* deleteNode = ptr -> next;
    ptr -> next = deleteNode -> next;
    delete deleteNode;
}

void ForwardList::DeleteBeforeFL(const string& target){
    if (head == nullptr || head -> next == nullptr || head -> data == target) return;
    NodeSinglyList* prev = nullptr;
    NodeSinglyList* curr = head;
    while (curr -> next -> data != target && curr -> next != nullptr){ //ищем элемент перед target
        prev = curr;
        curr = curr -> next;
    }
    if (curr -> next == nullptr) return;

    if (prev == nullptr)
        DeleteHeadFL();
    else {
        prev -> next = curr -> next; //меняем указатель предыдущего узла
        delete curr; //удаляем текущий
    }
}

void ForwardList::DeleteValueFL(const string& value){
    if (head == nullptr) return;
    if (head -> data == value) {//если по значению голова
        DeleteHeadFL(); //удаляем голову
        return;
    }

    NodeSinglyList* curr = head; //ищем предыдущий элемент
    while (curr -> next != nullptr && curr -> next -> data != value){
        curr = curr -> next;
    }
    if(curr -> next == nullptr) return;

    NodeSinglyList* deleteNode = curr -> next; 
    curr -> next = deleteNode -> next; //меняем указатель предыдущего узла
    delete deleteNode;
}

ForwardList::NodeSinglyList* ForwardList::FindFL(const string& value){
    NodeSinglyList* cur = head;
    while (cur != nullptr) {//перебор списка
        if (cur -> data == value) return cur; 
        cur = cur -> next;
    }
    return nullptr;
}

void ForwardList::printFL(){//вывод от ноды
    NodeSinglyList* cur = head;
    while(cur){
        cout << cur -> data << " ";
        cur = cur -> next;
    }
    cout << endl;
}

void ForwardList::printByValueFL(const string& value){//вывод от значения
    NodeSinglyList* ptr = FindFL(value);
    printFL();
}

void ForwardList::printReverseFL(NodeSinglyList* ptr){//обратный вывод
    if (ptr == nullptr) {
        cout << endl;
        return;
    }
    printReverseFL(ptr -> next);
    cout << ptr -> data << " ";
}

void ForwardList::saveFL(const string& filename) {
    ofstream out(filename);
    NodeSinglyList* curr = head; //записывает элементы в файл
    while(curr != nullptr) { 
        out << curr -> data << endl; 
        curr = curr -> next; }
    out.close();
}

void ForwardList::loadFL(const string& filename) {
    ifstream in(filename);
    if(!in.is_open()) return;
    clear();
    string value;
    while(getline(in,value)) 
        AddTailFL(value);
    in.close();
}