#include "stack.h"

Stack::Stack(){
    head = nullptr;
}

Stack::~Stack(){
    while(head){
        StackNode* cur = head;
        head = head -> next;
        delete cur;
    }
}

bool Stack::isEmptyS() {
    return head == nullptr;
}

void Stack::pushS(string value) { //добавляем на вершину
    StackNode* newNode = new StackNode{value, nullptr};
    newNode -> next = head; // новый элемент указывает на старый верхний
    head = newNode;       // теперь он становится вершиной
}

string Stack::popS() {//удаляем верхний элемент
    if (isEmptyS()) {
        //cout << "Стек пуст" << endl;
        return "";
    }
    StackNode* temp = head; 
    string value = temp -> data;
    head = head -> next; // передвигаем вершину вниз(на следующий элемент)
    delete temp;
    return value; //возвращаем значение удаленного узла
}

string Stack::top() {
    if (isEmptyS()) {
        return "";
    }
    return head -> data;
}

void Stack::printS() {
    if (isEmptyS()){
        //cout << "Стек пуст." << endl;
        return;
    }
    StackNode* current = head;
    cout << "Стек (верх -> низ): ";
    while (current != nullptr) { //проходим от вершины вниз
        cout << current -> data << " "; 
        current = current -> next;
    }
    cout << endl;
}

void Stack::clearS(){
    while(!isEmptyS()) 
        popS();
    //cout << "Стек очищен";
}
void Stack::loadS(const string& filename) { //читает элементы во временный стек
    ifstream fin(filename);
    if (!fin) return;
    string value;
    Stack tempStack;
    while (fin >> value) tempStack.pushS(value); // читаем и инвертируем
    clearS();
    fin.close();
    // Перенос в основной стек в правильном порядке
    while (!tempStack.isEmptyS()){
        pushS(tempStack.popS());
    }
}

void Stack::saveS(const string& filename) { //сохраняет сверху вниз
    ofstream fout(filename);
    StackNode* curr = head;
    while (curr) {
        fout << curr -> data << "\n";
        curr = curr -> next;
    }
    fout.close();
}