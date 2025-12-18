 #include "openHashTable.h"

HashTableOpen::HashTableOpen() {
    for (int i = 0; i < OPEN_TABLE_SIZE; i++) {
        table[i].key = "";
        table[i].value = "";
        table[i].used = false;
    }
}

bool HashTableOpen::insert(const string& value, const string& key) {
    if (key.empty()) return false;
    int h = hashFun(key);
    for (int i = 0; i < OPEN_TABLE_SIZE; i++) {
        int idx = (h + i) % OPEN_TABLE_SIZE;
        if (!table[idx].used) {
            table[idx].key = key;
            table[idx].value = value;
            table[idx].used = true;
            return true;
        }
        if (table[idx].key == key)
            return false;
    }
    return false;
}

string HashTableOpen::get(const string& key) const {
    int h = hashFun(key);
    for (int i = 0; i < OPEN_TABLE_SIZE; i++) {
        int idx = (h + i) % OPEN_TABLE_SIZE;
        if (!table[idx].used) return "";
        if (table[idx].key == key) return table[idx].value;
    }
    return "";
}

bool HashTableOpen::contains(const string& key) const {
    int h = hashFun(key);
    for (int i = 0; i < OPEN_TABLE_SIZE; i++) {
        int idx = (h + i) % OPEN_TABLE_SIZE;
        if (!table[idx].used) return false;
        if (table[idx].key == key) return true;
    }
    return false;
}

bool HashTableOpen::remove(const string& key) {
    int h = hashFun(key);
    for (int i = 0; i < OPEN_TABLE_SIZE; i++) {
        int idx = (h + i) % OPEN_TABLE_SIZE;
        if (!table[idx].used) return false;
        if (table[idx].key == key) {
            table[idx].used = false;
            table[idx].key = "";
            table[idx].value = "";
            return true;
        }
    }
    return false;
}

void HashTableOpen::printTable() const {
    cout << "Хэш-таблица (ключ -> значение):\n";
    for (int i = 0; i < OPEN_TABLE_SIZE; i++) {
        cout << i << ": ";
        if (table[i].used)
            cout << "'" << table[i].key << "' -> '" << table[i].value << "'";
        else
            cout << "-";
        cout << endl;
    }
}

// вспомогательное: индекс для тестов
int HashTableOpen::debugIndex(const string& key) const {
    return hashFun(key);
}