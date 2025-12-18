#include "queue.h"
Queue::Queue(){
    front = nullptr;
    rear = nullptr;
}

Queue::~Queue(){
    while (front){
        QueueNode* cur = front;
        front = front -> next;
        delete cur;
    }

}

void Queue::pushQ(string value) { //добавляется в конец
    QueueNode* newNode = new QueueNode{value, nullptr}; //создаем новый узел
    if (rear == nullptr) { //если очередь пустая 
        front = rear = newNode; 
        return;
    }
    rear -> next = newNode; //добавляем в конец узел
    rear = newNode; //сдвигаем rear
}

string Queue::popQ() { //удаляется первый элемент
    if (front == nullptr) {
        return "";
    }
    QueueNode* temp = front;//
    string value = temp -> data;
    front = front -> next; //сдвигаем front
    if (front == nullptr)  // если очередь опустела
        rear = nullptr;
    delete temp;
    return value; //выводим удаленный элемент
}

bool Queue::isEmptyQ() {
    return front == nullptr;
}

// Вывод очереди
void Queue::printQ() {
    if (isEmptyQ()) {
        cout << "Очередь пуста" << endl;
        return;
    }
    QueueNode* current = front;
    cout << "Очередь (слева направо): ";
    while (current != nullptr) { //проходим от front до rear
        cout << current -> data << " ";
        current = current -> next;
    }
    cout << endl;
}

// Загрузка очереди из файла
void Queue::loadQ(const string& filename) {
    ifstream fin(filename);
    if (!fin) return;
    string value;
    while (fin >> value) pushQ(value);
    fin.close();
}

// Сохранение очереди в файл
void Queue::saveQ(const string& filename) {
    ofstream fout(filename);
    QueueNode* current = front;
    while (current != nullptr) {
        fout << current -> data << "\n";
        current = current -> next;
    }
    fout.close();
}