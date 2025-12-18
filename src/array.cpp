#include "array.h"

Array::Array(){
    capacity = 2;
    data = new string[capacity]; //выделение памяти
    size = 0;
}

Array::~Array(){
    delete[] data;
}

void Array::resize(int newCapacity){
    string* newArr = new string[newCapacity];
    for (int i = 0; i < size; i++){
        newArr[i] = data[i];
    }
    delete[] data;
    data = newArr;
    capacity = newCapacity;
}


void Array::pushBackM(const string& value){
    if (size >= capacity) resize(capacity * 2);
    data[size++] = value;
}

void Array::insertM(int index, const string& value) {
    if (index < 0 || index > size) {
        cout << "Ошибка: индекс вне диапазона" << endl;
        return;
    }

    pushBackM(""); //увеличиваем массив на 1
    for (int i = size-1; i > index; i--) { //смещаем элементы вправо
        data[i] = data[i - 1];
    }
    data[index] = value; //вставляем по индексу
}
 
void Array::deleteM(int index) {
    if (size == 0) {
        cout << "Массив пуст" << endl;
        return;
    }
    if (index < 0 || index >= size) {
        cout << "Ошибка: индекс вне диапазона" << endl;
        return;
    }
    for (int i = index; i < size - 1; i++) { //сдвигаем влево от индекса
        data[i] = data[i + 1];
    }
    size--;
}

string Array::getM(int index) {
    if (index < 0 || index >= size) {
//        cout << "Ошибка: индекс вне диапазона" << endl;
        return "";
    }
    return data[index];
}

void Array::replaceM(int index, string value) {
    if (index < 0 || index >= size) {
//        cout << "Ошибка: индекс вне диапазона" << endl;
        return;
    }
    data[index] = value;
}

void Array::printM(){
    if (size == 0) {
        cout << "Массив пуст" << endl;
        return;
    }
    cout << "Массив: ";
    for (int i = 0; i < size; i++) {
        cout << data[i] << " ";
    }
    cout << endl;
}

int Array::lengthM(){
    return size;
}

void Array::loadM(const string& filename){
    ifstream file(filename); //читает элементы из файла
    if (!file) return;
    string value;
    while (file >> value)
        pushBackM(value);
    file.close();
}

void Array::saveM(const string& filename){
    ofstream file(filename); //записывает элементы в файл
    for (int i = 0; i < size; i++){
        file << data[i] << endl;
    }
    file.close();
}


