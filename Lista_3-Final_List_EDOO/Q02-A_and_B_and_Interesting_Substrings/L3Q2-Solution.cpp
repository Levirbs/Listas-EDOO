#include <iostream>
#include <vector>
using namespace std;

class Node {
    private:
        long long key;
        int value;
        Node* next;
    
    public:
        Node(long long k, int v) : key(k), value(v), next(nullptr) {}

        long long getKey() { return this->key; }

        int getValue() { return this->value; }

        void setValue(int newValue) { this->value = newValue; }

        Node* getNext() {return this->next; }

        void setNext(Node* newNode) { next = newNode; }
};

class LinkedHashTable {
    private:
        static const int size = 10007;
        Node* tabela[size];

        // Funcao hash para calcular o indice baseado na chave
        int hash(long long key) const {
            return ((key % size) + size) % size;
        }

    public:
        LinkedHashTable() { for (int i = 0; i < size; i++) tabela[i] = nullptr; }

        ~LinkedHashTable() {
            for (int i = 0; i < size; i++) {
                Node* atual = tabela[i];

                // Libera a memoria de todos os nos na tabela
                while (atual != nullptr) {
                    Node* temp = atual;
                    atual = atual->getNext();
                    delete temp;
                }
            }
        }
        
        // Retorna o valor associado a chave ou 0 se nao existir
        int get(long long key) const {
            int i = hash(key);
            Node* atual = tabela[i];

            while (atual != nullptr) {
                if (atual->getKey() == key) {
                    return atual->getValue();
                }
                atual = atual->getNext();
            }
            return 0;
        }

        // Incrementa o valor associado a chave ou cria um novo no com valor 1
        void addOne(long long key) {
            int i = hash(key);
            Node* atual = tabela[i];
            
            if (atual == nullptr) {
                tabela[i] = new Node(key, 1);
                return;
            }
            
            while (atual != nullptr) {
                if (atual->getKey() == key) {
                    atual->setValue(atual->getValue() + 1);
                    return;
                }
                
                if (atual->getNext() == nullptr) break;
                atual = atual->getNext();
            }
            
            Node* newNode = new Node(key, 1);
            atual->setNext(newNode);
        };
};

int main() {
    vector<int> charPositions[26];
    string text;
    int charValues[26];

    // Le os valores associados a cada letra do alfabeto
    int alphabet = 0;
    while (alphabet < 26) {
        cin >> charValues[alphabet++];
    }

    // Processa o texto de entrada
    cin >> text;
    int textLength = text.size();
    
    // Inicializa o vetor de somas prefixadas
    vector<long long> sums(textLength + 1, 0);
    sums[0] = 0;
    
    // Mapeia as somas prefixadas e registra as posicoes de cada caractere
    {
        int idx = 0;
        while (idx < textLength) {
            char currChar = text[idx];
            int letterIndex = currChar - 'a';
            
            // Calcula a soma prefixada atual
            sums[idx + 1] = sums[idx] + charValues[letterIndex];
            
            // Registra a posicao atual para o caractere
            charPositions[letterIndex].push_back(idx + 1);
            
            idx++;
        }
    }

    // Conta as substrings interessantes
    long long totalCount = 0;
    
    // Processa cada letra do alfabeto
    for (int charIdx = 0; charIdx < 26; charIdx++) {
        if (charPositions[charIdx].empty()) continue;
        
        LinkedHashTable freq;
        long long substrCount = 0;
        
        auto it = charPositions[charIdx].begin();
        while (it != charPositions[charIdx].end()) {
            int pos = *it;
            
            // Obtem o número de correspondencias anteriores
            long long prevMatches = freq.get(sums[pos - 1]);
            substrCount += prevMatches;
            
            // Atualiza a tabela hash com a soma atual
            freq.addOne(sums[pos]);
            
            ++it;
        }
        
        totalCount += substrCount;
    }

    // Imprime o total de substrings interessantes
    cout << totalCount << endl;
    return 0;
}