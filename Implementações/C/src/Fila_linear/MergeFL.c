#include "MergeFL.h"

size_t memoriaFilaL_durante_execução = 0;

void mergeFL(float arr[], int l, int m, int r) {
    int n1 = m - l + 1, n2 = r - m;

    memoriaFilaL_durante_execução += sizeof(float) * (n1 + n2);

    float* L = malloc(n1 * sizeof(float));
    float* R = malloc(n2 * sizeof(float));

    for (int i = 0; i < n1; i++)
        L[i] = arr[l + i];
    for (int j = 0; j < n2; j++)
        R[j] = arr[m + 1 + j];

    int i = 0, j = 0, k = l;
    while (i < n1 && j < n2) {
        arr[k++] = (L[i] <= R[j]) ? L[i++] : R[j++];
    }

    while (i < n1) arr[k++] = L[i++];
    while (j < n2) arr[k++] = R[j++];

    free(L);
    free(R);
}

void mergeSortFL(float arr[], int l, int r) {
    if (l < r) {
        int m = l + (r - l) / 2;
        mergeSortFL(arr, l, m);
        mergeSortFL(arr, m + 1, r);
        mergeFL(arr, l, m, r);
    }
}

// Salvar dados ordenados
void salvarOrdenadoEmArquivo(FilaLinear* fila, const char* nomeArquivo) {
    FILE* f = fopen(nomeArquivo, "w");
    if (!f) {
        perror("Erro ao salvar o arquivo de saída");
        return;
    }

    for (int i = fila->frente; i <= fila->tras; i++) {
        fprintf(f, "%.1f\n", fila->dados[i]);
    }

    fclose(f);
}
