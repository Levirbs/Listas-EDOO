#include <iostream>
#include <string>
#include <vector>

using namespace std;

string buildNumberImpl(int n);
int countPlusOpsImpl(int n);

string Stackulator(vector<int> desiredStack);

int main() {
    int n;
    cin >> n;
    
    vector<int> desiredStack(n);
    for (int i = 0; i < n; i++) {
        cin >> desiredStack[i];
    }
    
    string result = Stackulator(desiredStack);
    cout << result;
    
    return 0;
}

// Funcao para gerar instrucoes para um numero unico
string buildNumberImpl(int n) {
    if (n == 1) return "1";
    if (n % 2 == 0) {
        return buildNumberImpl(n / 2) + "d+";
    }
    return buildNumberImpl((n - 1) / 2) + "d+1+";
}

// Funcao para contar operacoes de mais nas intrucoes para construir n
int countPlusOpsImpl(int n) {
    if (n == 1) return 0;
    if (n % 2 == 0) return 1 + countPlusOpsImpl(n / 2);
    return 2 + countPlusOpsImpl((n - 1) / 2); // d+1+ tem 2 operacoes de mais (+)
}

string Stackulator(vector<int> desiredStack) {
    int n = desiredStack.size();
    if (n == 0) return "";
    
    // Caso Especial: todos elementos sao 1
    bool allOnes = true;
    for (int num : desiredStack) {
        if (num != 1) {
            allOnes = false;
            break;
        }
    }
    
    if (allOnes) {
        // Para n 1, podemos adicionar 1 uma vez e duplicar n-1 vezes
        string result = "1";
        for (int i = 1; i < n; i++) {
            result += "d";
        }
        return result;
    }
    
    // Calcula o valor ajustado do topo para a base da pilha
    vector<int> adjustedValues(n);
    vector<int> plusOperations(n, 0);
    
    // Comeca com o elemento do topo (ultimo do vetor)
    adjustedValues[0] = desiredStack[n-1];
    plusOperations[0] = countPlusOpsImpl(adjustedValues[0]);
    
    // Processa os elementos restantes o topo para a base
    for (int i = 1; i < n; i++) {
        int idx = n - 1 - i; // Indice na pilha original
        
        // Soma todos as operacoes de mais que vao aparecer acima deste elemento
        int adjustment = 0;
        for (int j = 0; j < i; j++) {
            adjustment += plusOperations[j];
        }
        
        // Ajusta o valor para compensar futuros decrementos por causa da operacao de soma
        adjustedValues[i] = desiredStack[idx] + adjustment;
        plusOperations[i] = countPlusOpsImpl(adjustedValues[i]);
    }
    
    // Constroi as instrucoes da base para o topo
    string result = "";
    for (int i = n - 1; i >= 0; i--) {
        result += buildNumberImpl(adjustedValues[i]);
    }
    
    return result;
}