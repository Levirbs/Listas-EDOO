#include <string>
#include <iostream>

using namespace std;

// Abstract base class for a list
template <typename E>
class List {
    public:
        List() {}
        virtual ~List() {}

        virtual void clear() = 0;
        virtual void insert(const E& item) = 0;
        virtual void moveToStart() = 0;
        virtual void moveToEnd() = 0;
        virtual void next() = 0;
        virtual int length() const = 0;
        virtual const E& getValue() const = 0;
};

// Node class for a singly linked list
template <typename E>
class SimpleLink {
public:
    E data;
    SimpleLink<E>* next;

    SimpleLink(const E& data, SimpleLink<E>* next)
    : data(data), next(next) {}

    SimpleLink() : next(nullptr) {}
    ~SimpleLink() {}
};

// Singly linked list implementation of the List interface
template <typename E>
class ListL : public List<E> {
private:
    SimpleLink<E>* head;
    SimpleLink<E>* tail;
    SimpleLink<E>* curr;
    int cnt;

    void init() {
        curr = tail = head = new SimpleLink<E>;
        cnt = 0;
    }   
    
    void removeall() {
        while (head != nullptr) {
            curr = head;
            head = head->next;
            delete curr;
        }
    }

public:
    ListL(int size = 5) {
        init();
    }
    ~ListL() {
        removeall();
    }

    void clear() override {
        removeall();
        init();
    }

    void insert(const E& it) override {
        curr->next = new SimpleLink<E>(it, curr->next);
        if (tail == curr) tail = curr->next;
        cnt++;
    }

    void moveToStart() override {
        curr = head;
    }

    void moveToEnd() override {
        curr = tail;
    }

    void next() override {
        if (curr != tail) curr = curr->next;
    }

    int length() const override {
        return cnt;
    }

    const E& getValue() const override {
    if (curr->next == nullptr) {
        cout << "No value" << endl;
        throw runtime_error("No value");
    }
    return curr->next->data;
    }
};

int main() {
    string line;
    ListL<char> out_list;
    while (getline(cin, line)) {
        int size = line.size();
        if (size > 0 && size <= 100000) {
            for (char ch : line) {
                if (ch == '[') {
                    out_list.moveToStart();
                } else if (ch == ']') {
                    out_list.moveToEnd();
                } else {
                    out_list.insert(ch);
                    out_list.next();
                }
            }
            
            // Iterate over the list and print each character
            out_list.moveToStart();
            for (int i = 0; i < out_list.length(); i++) {
                cout << out_list.getValue();
                out_list.next();
            }
            cout << endl;

            // Clear the list for the next input line
            out_list.clear();
        }
    }

    return 0;
}