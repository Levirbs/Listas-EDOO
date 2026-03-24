#include <iostream>
#include <string>
#include <vector>
using namespace std;

const int table_size = 101; 

class HashTable {
private:
    vector<string> table; 
    vector<bool> isEmpty;
    int current_size = 0;

    int Hash(const string& key) {
        int hashValue = 0;
        for (int i = 0; i < key.length(); ++i) {
            hashValue += key[i] * (i + 1);
        }
        hashValue = (hashValue * 19) % table_size;
        return hashValue;
    }

    int findPosition(const string& key) {
        int hashIndex = Hash(key); 

        for (int i = 0; i <= 19; ++i) {
            int index = (hashIndex + i * i + 23 * i) % table_size;
            if (table[index] == key && !isEmpty[index]) {
                return index;
            }
            if (table[index].empty()) {
                break;
            }
        }

        return -1;
    }

public:
    HashTable() : table(table_size, ""), isEmpty(table_size, false) {}

    void Insert(const string& key) {
        if (findPosition(key) != -1) { return; };

        int hashIndex = Hash(key); 

        for (int i = 0; i <= 19; ++i) {
            int index = (hashIndex + i * i + 23 * i) % table_size;

            if (table[index].empty() || isEmpty[index]) {
                table[index] = key;
                isEmpty[index] = false;
                current_size++;
                return;
            }
        }
    }

    void Delete(const string& key) {
        int index = findPosition(key);
        if (index != -1) {
            isEmpty[index] = true; 

            current_size--;
        }
    }

    int currentSize() const {
        return current_size;
    }

    void Display() const {
        for (int i = 0; i < table_size; ++i) {
            if (!table[i].empty() && !isEmpty[i]) {
                cout << i << ":" << table[i] << endl;
            }
        }
    }
};

int main() {
    int t, n;
    string input, operation, key;

    cin >> t; 

    for (int i = 0; i < t; ++i) {
        cin >> n; 

        HashTable hash; 

        for (int k = 0; k < n; ++k) {
            cin >> input;
            size_t pos = input.find(':');
            operation = input.substr(0, pos);
            key = input.substr(pos + 1);
            
            if (operation == "ADD") {
                hash.Insert(key);
            } else if (operation == "DEL") {
                hash.Delete(key);
            }
        }

        cout << hash.currentSize() << endl;
        hash.Display();
    }

    return 0;
}