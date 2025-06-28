#include "FilaL.h"

void inicializarFila(FilaLinear* fila) {
    fila->frente = 0;
    fila->tras = -1;
}

int enqueue(FilaLinear* fila, float valor) {
    if (fila->tras >= MAX_TAM - 1) return 0;
    fila->dados[++fila->tras] = valor;
    return 1;
}

void carregarRatingsFL(const char* arquivoCSV, FilaLinear* fila, int n) {
    FILE* f = fopen("data/Input/ratings.csv", "r");
    if (!f) {
        perror("Erro ao abrir o arquivo");
        exit(1);
    }

    char linha[1024];
    fgets(linha, sizeof(linha), f); 
    inicializarFila(fila);

    while (fgets(linha, sizeof(linha), f) && (fila->tras + 1) < n) {
        char* token = strtok(linha, ","); 
        token = strtok(NULL, ",");        
        token = strtok(NULL, ",");        // rating
        if (token) {
            float rating = atof(token);
            enqueue(fila, rating);
        }
    }

    fclose(f);
}

// Funções de ordenação



