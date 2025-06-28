#include "include/includes.hpp"
#include "include/merge.hpp"
#include "include/benchmark.hpp"
#include "include/arquivo.hpp"
#include "include/estruturas.hpp"
#include <algorithm>

// Função auxiliar para inverter pilha usando pilha auxiliar
template<typename PilhaType>
void invertePilha(PilhaType& pilha) {
    PilhaType pilhaAux;
    
    // Passa todos elementos para pilha auxiliar
    while (!pilha.isEmpty()) {
        pilhaAux.push(pilha.pop());
    }
    
    // Volta todos elementos para pilha original (agora em ordem correta)
    while (!pilhaAux.isEmpty()) {
        pilha.push(pilhaAux.pop());
    }
}

int main() {
    vector<int> sizes = {100, 1000, 10000, 100000};
    vector<Result> results;
    const int nExec = 5;
    const string data = "data/Input/ratings.csv";
    const string filePath = data;

    for (int size : sizes) {
        cout << "\n=== " << size << " entradas ===\n";
        vector<int> base = readCSV(filePath, size);

        // Função auxiliar para executar e medir
        auto benchmarkSort = [&](const string& structure, const string& representation, auto sortFunc) {
            double sumDur = 0;
            size_t sumMem = 0;
            
            for (int i = 0; i < nExec; i++) {
                auto [dur, mem] = benchmarkFunction([&]() {
                    sortFunc(); // Executa o algoritmo
                });
                
                sumDur += dur;
                sumMem += mem;
            }
            
            results.push_back({
                size, 
                structure, 
                representation, 
                sumDur / nExec, 
                sumMem / nExec
            });
            
            cout << structure << " " << representation << ": " 
                 << sumDur / nExec << " s, " 
                 << sumMem / nExec << " bytes\n";
        };

        // --- Lista Linear ---
        benchmarkSort("lista", "linear", [&]() {
            ListaLinear lista(size + 100);
            
            // Preenche a lista
            for (int val : base) {
                lista.insert(val);
            }
            
            // Converte para vetor, ordena e volta para lista
            vector<int> temp = lista.toVector();
            mergeSort(temp, 0, temp.size() - 1);
            lista.fromVector(temp);
        });

        // --- Lista Dinâmica ---
        benchmarkSort("lista", "dinamica", [&]() {
            ListaDinamica lista;
            
            // Preenche a lista
            for (int val : base) {
                lista.insert(val);
            }
            
            // Converte para vetor, ordena e volta para lista
            vector<int> temp = lista.toVector();
            mergeSort(temp, 0, temp.size() - 1);
            lista.fromVector(temp);
        });

        // --- Pilha Linear ---
        benchmarkSort("pilha", "linear", [&]() {
            PilhaLinear pilha(size + 100);
            
            // Preenche a pilha
            for (int val : base) {
                pilha.push(val);
            }
            
            // Converte para vetor, ordena
            vector<int> temp = pilha.toVector();
            mergeSort(temp, 0, temp.size() - 1);
            
            // Reconstrói a pilha ordenada
            pilha.fromVector(temp);
            
            // Inverte a pilha para manter ordem correta
            invertePilha(pilha);
        });

        // --- Pilha Dinâmica ---
        benchmarkSort("pilha", "dinamica", [&]() {
            PilhaDinamica pilha;
            
            // Preenche a pilha
            for (int val : base) {
                pilha.push(val);
            }
            
            // Converte para vetor, ordena
            vector<int> temp = pilha.toVector();
            mergeSort(temp, 0, temp.size() - 1);
            
            // Reconstrói a pilha ordenada
            pilha.fromVector(temp);
            
            // Inverte a pilha para manter ordem correta
            invertePilha(pilha);
        });

        // --- Fila Linear ---
        benchmarkSort("fila", "linear", [&]() {
            FilaLinear fila(size + 100);
            
            // Preenche a fila
            for (int val : base) {
                fila.enqueue(val);
            }
            
            // Converte para vetor, ordena e volta para fila
            vector<int> temp = fila.toVector();
            mergeSort(temp, 0, temp.size() - 1);
            fila.fromVector(temp);
        });

        // --- Fila Dinâmica ---
        benchmarkSort("fila", "dinamica", [&]() {
            FilaDinamica fila;
            
            // Preenche a fila
            for (int val : base) {
                fila.enqueue(val);
            }
            
            // Converte para vetor, ordena e volta para fila
            vector<int> temp = fila.toVector();
            mergeSort(temp, 0, temp.size() - 1);
            fila.fromVector(temp);
        });
    }

    saveCSV("data/Output/results.csv", results);
    cout << "\nResultados salvos em results.csv\n";

    return 0;
}