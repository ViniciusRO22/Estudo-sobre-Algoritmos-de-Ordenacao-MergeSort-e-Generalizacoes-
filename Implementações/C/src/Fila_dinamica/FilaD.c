#include "FilaD.h"

void iniciarFila(FilaDinamica *fila) {
    fila->inicio = NULL;
    fila->fim = NULL;
    fila->tamanho = 0;
}

void enfileirar(FilaDinamica *fila, float valor) {
    NoFD *novo = (NoFD *) malloc(sizeof(NoFD));
    novo->rating = valor;
    novo->prox = NULL;
    if (fila->fim)
        fila->fim->prox = novo;
    else
        fila->inicio = novo;
    fila->fim = novo;
    fila->tamanho++;
}

void liberarFila(FilaDinamica *fila) {
    NoFD *atual = fila->inicio;
    while (atual) {
        NoFD *temp = atual;
        atual = atual->prox;
        free(temp);
    }
}

float* copiarParaArray(FilaDinamica *fila) {
    float *array = (float *) malloc(fila->tamanho * sizeof(float));
    NoFD *atual = fila->inicio;
    int i = 0;
    while (atual != NULL) {
        array[i++] = atual->rating;
        atual = atual->prox;
    }
    return array;
}

void lerRatingsParaFila(FilaDinamica *fila, const char *arquivo, int limite) {
    FILE *fp = fopen(arquivo, "r");
    if (!fp) {
        perror("Erro ao abrir arquivo");
        return;
    }

    char linha[256];
    fgets(linha, sizeof(linha), fp); 
    int userId, movieId;
    float rating;
    long timestamp;
    int count = 0;

    while (fgets(linha, sizeof(linha), fp) && count < limite) {
        if (sscanf(linha, "%d,%d,%f,%ld", &userId, &movieId, &rating, &timestamp) == 4) {
            enfileirar(fila, rating);
            count++;
        }
    }

    fclose(fp);
}

