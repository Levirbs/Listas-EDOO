#include <iostream>
 
using namespace std;

// classe base de pilha

template <typename E> 
class Stack {
    public:
        Stack() {}
        virtual ~Stack() {} 

        virtual void push(const E& item) = 0;

        virtual E pop() = 0;
    };

// Pilha baseada em array

class StackA : public Stack<int> {
    private:
        int capacity; 
        int size;
        int *array; 
    public:
        StackA(int intialSize) {
            capacity = intialSize;
            size = 0;
            array = new int[intialSize];
        }

        ~StackA() {
            delete[] array;
        }
        
        void push(const int& element) override {
            if (size == capacity) {
                std::cout << "Stack is full" <<  std::endl;
            }
            array[size++] = element;
        }

        int pop() override {
            if (size == 0) {
                std::cout << "Stack is empty" <<  std::endl;
            }
            return array[--size];
        }
};


const int MAX_SIZE = 100000;
const int MIN_ELEMENT = 1;
const int MAX_ELEMENT = 100;

int equalStacks(StackA* stack1, StackA* stack2, StackA* stack3, int* soma1, int* soma2, int* soma3);
int organizar_e_somar(StackA* destino, int size);
int* maior(int* soma1, int* soma2, int* soma3);

int main() {
    int size1, size2, size3;
    cin >> size1 >> size2 >> size3;

    // Verificacao de entrada
    if (size1 <= 0 || size2 <= 0 || size3 <= 0 || size1 > MAX_SIZE || size2 > MAX_SIZE || size3 > MAX_SIZE) {
        // cerr << "Tamanhos invalidos" << endl;
        return 1;
    }

    StackA* stack1 = new StackA(size1);
    StackA* stack2 = new StackA(size2);
    StackA* stack3 = new StackA(size3);

    int soma1 = organizar_e_somar(stack1, size1);
    int soma2 = organizar_e_somar(stack2, size2);
    int soma3 = organizar_e_somar(stack3, size3);

    int height = equalStacks(stack1, stack2, stack3, &soma1, &soma2, &soma3);

    cout << height << endl;

    // Liberacao de memoria
    delete stack1;
    delete stack2;
    delete stack3;

    return 0;
}

int equalStacks(StackA* stack1, StackA* stack2, StackA* stack3, int* soma1, int* soma2, int* soma3) {
    while (true) {
        if (*soma1 == *soma2 && *soma1 == *soma3) {
            return *soma1;
        } else {
            int* maiorStack = maior(soma1, soma2, soma3);
            if (maiorStack == soma1) {
                *soma1 -= stack1->pop();
            } else if (maiorStack == soma2) {
                *soma2 -= stack2->pop();
            } else {
                *soma3 -= stack3->pop();
            }
        }
    }
}

int organizar_e_somar(StackA* destino, int size) {
    int disc;
    int soma = 0;
    StackA* temp = new StackA(size);
    for (int i = 0; i < size; i++) {
        cin >> disc;
        if (disc < MIN_ELEMENT || disc > MAX_ELEMENT) {
            cerr << "Elemento invalido: " << disc << endl;
            delete temp;
            return -1;
        }
        temp->push(disc);
    }

    for (int i = 0; i < size; i++) {
        int discTemp = temp->pop();
        destino->push(discTemp);
        soma += discTemp;
    }

    delete temp;
    return soma;
}

int* maior(int* soma1, int* soma2, int* soma3) {
    if (*soma1 >= *soma2 && *soma1 >= *soma3) {
        return soma1;
    } else if (*soma2 >= *soma1 && *soma2 >= *soma3) {
        return soma2;
    } else {
        return soma3;
    }
}