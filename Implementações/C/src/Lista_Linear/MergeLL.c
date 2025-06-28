#include "MergeLL.h"

size_t memoriaLL_durante_execução = 0;

void mergeLL(float arr[], int esquerda, int meio, int direita) {
    int n1 = meio - esquerda + 1, n2 = direita - meio;

    memoriaLL_durante_execução += sizeof(float) * (n1 + n2);

    float* L = (float*)malloc(n1 * sizeof(float));
    float* R = (float*)malloc(n2 * sizeof(float));

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


void mergeSortLL(float arr[], int esquerda, int direita) {
    if (esquerda < direita) {
        int meio = esquerda + (direita - esquerda) / 2;
        mergeSortLL(arr, esquerda, meio);
        mergeSortLL(arr, meio + 1, direita);
        mergeLL(arr, esquerda, meio, direita);
    }
}


void salvarEmArquivo(const float* arr, int tamanho, int n) {
    char nomeArquivo[64];
    sprintf(nomeArquivo, "data/Output/output_%d.txt", n);

    FILE* f = fopen(nomeArquivo, "w");
    if (!f) {
        perror("Erro ao salvar arquivo");
        return;
    }

    for (int i = 0; i < tamanho; i++) {
        fprintf(f, "%.1f\n", arr[i]);
    }

    fclose(f);
}