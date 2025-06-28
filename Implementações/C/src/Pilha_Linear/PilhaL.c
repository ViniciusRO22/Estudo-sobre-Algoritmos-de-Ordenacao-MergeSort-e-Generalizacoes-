#include "PilhaL.h"


void inicializarPilhaL(PilhaLinear* pilha) {
    pilha->topo = -1;
}


int pushPL(PilhaLinear* pilha, float valor) {
    if (pilha->topo >= MAX_TAMANHO - 1) {
        return 0; 
    }
    pilha->dados[++pilha->topo] = valor;
    return 1;
}


float pop(PilhaLinear* pilha) {
    if (pilha->topo < 0) {
        return -1; 
    }
    return pilha->dados[pilha->topo--];
}


void carregarRatingsPL(const char* ratingscsv, PilhaLinear* pilha, int n) {
    FILE* f = fopen(ratingscsv, "r");
    if (!f) {
        perror("Erro ao abrir o arquivo");
        exit(1);
    }

    char linha[1024];
    fgets(linha, 1024, f); 
    inicializarPilhaL(pilha);

    while (fgets(linha, 1024, f) && pilha->topo < n - 1) {
        char* token = strtok(linha, ","); 
        token = strtok(NULL, ",");        
        token = strtok(NULL, ",");        // rating
        if (token) {
            pushPL(pilha, atof(token));
        }
    }

    fclose(f);
}


