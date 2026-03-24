#include <iostream>

using namespace std;

template <typename E> 
class Queue {
    public:
        Queue() {}
        virtual ~Queue() {}
        
        virtual void enqueue(const E&) = 0;
        virtual E dequeue() = 0;
        virtual int length() const = 0;
};

template <typename E> 
class AQueue: public Queue<E> {
    private:
        int maxSize;
        int front;
        int rear;
        E *listArray;
    public:
        AQueue(int size = 5) {
            maxSize = size + 1;
            rear = 0; 
            front = 1;
            listArray = new E[maxSize];
        }

        ~AQueue() {
            delete[] listArray;
        }
        
        void enqueue(const E& it) {
            if (((rear + 2) % maxSize) != front) {
                rear = (rear + 1) % maxSize;
                listArray[rear] = it;
            } else {
                cerr << "Queue is full" << endl;
            }
        }

        E dequeue() {
            if (length() != 0) {
                E it = listArray[front];
                front = (front + 1) % maxSize;
                return it;
            } else {
                cerr << "Queue is empty" << endl;
                return -1;
            }
        }

        virtual int length() const {
            return ((rear + maxSize) - front + 1) % maxSize;
        }
};


int main() {
    int nTestCase;
    cin >> nTestCase;

    if (nTestCase < 1 || nTestCase > 1000) {
        return 1;
    }

    for (int t = 0; t < nTestCase; t++) {
        int nStudent;
        cin >> nStudent;

        if (nStudent < 1 || nStudent > 1000) {
            return 1;
        }

        AQueue<int> enterQueue(nStudent); // Fila de tempos de chegada
        AQueue<int> leaveQueue(nStudent); // Fila de tempos limite

        for (int i = 0; i < nStudent; i++) {
            int enterSecond, leaveSecond;
            cin >> enterSecond >> leaveSecond;

            if (enterSecond < 1 || enterSecond > 5000 || leaveSecond < 1 || leaveSecond > 5000) {
                return 1;
            }

            enterQueue.enqueue(enterSecond);
            leaveQueue.enqueue(leaveSecond);
        }

        int currentTime = 1; // O tempo atual
        AQueue<int> resultQueue(nStudent); // Fila para armazenar os resultados

        while (enterQueue.length() > 0) {
            int enter = enterQueue.dequeue();
            int leave = leaveQueue.dequeue();

            if (currentTime < enter) {
                currentTime = enter; // Avança para o próximo estudante
            }

            if (currentTime <= leave) {
                resultQueue.enqueue(currentTime); // O estudante recebe o chá
                currentTime++; // Avança o tempo
            } else {
                resultQueue.enqueue(0); // O estudante não recebe chá
            }
        }

        while (resultQueue.length() > 0) {
            cout << resultQueue.dequeue() << " ";
        }
        cout << endl;
    }

    return 0;
}