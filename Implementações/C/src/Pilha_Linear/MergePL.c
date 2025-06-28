#include "MergePL.h"

size_t memoriaPL_durante_execução = 0;

void mergePL(float arr[], int esquerda, int meio, int direita) {
    int n1 = meio - esquerda + 1;
    int n2 = direita - meio;

    memoriaPL_durante_execução += sizeof(float) * (n1 + n2);

    float* L = malloc(n1 * sizeof(float));
    float* R = malloc(n2 * sizeof(float));

    for (int i = 0; i < n1; i++) L[i] = arr[esquerda + i];
    for (int j = 0; j < n2; j++) R[j] = arr[meio + 1 + j];

    int i = 0, j = 0, k = esquerda;
    while (i < n1 && j < n2) {
        arr[k++] = (L[i] <= R[j]) ? L[i++] : R[j++];
    }

    while (i < n1) arr[k++] = L[i++];
    while (j < n2) arr[k++] = R[j++];

    free(L);
    free(R);
}


void mergeSortPL(float arr[], int esquerda, int direita) {
    if (esquerda < direita) {
        int meio = esquerda + (direita - esquerda) / 2;
        mergeSortPL(arr, esquerda, meio);
        mergeSortPL(arr, meio + 1, direita);
        mergePL(arr, esquerda, meio, direita);
    }
}

void salvarEmArquivoPL(PilhaLinear* pilha, int n) {
    char nomeArquivo[64];
    sprintf(nomeArquivo, "output_%d.txt", n);

    FILE* f = fopen(nomeArquivo, "w");
    if (!f) {
        perror("Erro ao salvar arquivo");
        return;
    }

    for (int i = 0; i <= pilha->topo; i++) {
        fprintf(f, "%.1f\n", pilha->dados[i]);
    }

    fclose(f);
}
