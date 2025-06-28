#include "MergeFD.h"

size_t memoriaFilaD_durante_execução = 0;


void mergeFD(float arr[], int esq, int meio, int dir) {
    int n1 = meio - esq + 1, n2 = dir - meio;

    memoriaFilaD_durante_execução += sizeof(float) * (n1 + n2);

    float *L = (float *) malloc(n1 * sizeof(float));
    float *R = (float *) malloc(n2 * sizeof(float));

    for (int i = 0; i < n1; i++)
        L[i] = arr[esq + i];
    for (int j = 0; j < n2; j++)
        R[j] = arr[meio + 1 + j];

    int i = 0, j = 0, k = esq;
    while (i < n1 && j < n2) {
        if (L[i] <= R[j])
            arr[k++] = L[i++];
        else
            arr[k++] = R[j++];
    }

    while (i < n1)
        arr[k++] = L[i++];
    while (j < n2)
        arr[k++] = R[j++];

    free(L);
    free(R);
}

void mergeSortFD(float arr[], int esq, int dir) {
    if (esq < dir) {
        int meio = esq + (dir - esq) / 2;
        mergeSortFD(arr, esq, meio);
        mergeSortFD(arr, meio + 1, dir);
        mergeFD(arr, esq, meio, dir);
    }
}

void salvarArrayEmArquivo(const char *arquivo, float *array, int tamanho) {
    FILE *fp = fopen(arquivo, "w");
    if (!fp) {
        perror("Erro ao abrir output.txt");
        return;
    }

    for (int i = 0; i < tamanho; i++) {
        fprintf(fp, "%.1f\n", array[i]);
    }

    fclose(fp);
}
