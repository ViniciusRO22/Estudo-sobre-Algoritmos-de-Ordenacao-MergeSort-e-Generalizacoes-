#ifndef FILAD_H
#define FILAD_H


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

typedef struct NoFD {
    float rating;
    struct NoFD *prox;
} NoFD;

typedef struct {
    NoFD *inicio;
    NoFD *fim;
    int tamanho;
} FilaDinamica;

void iniciarFila(FilaDinamica *fila);
void enfileirar(FilaDinamica *fila, float valor);
void liberarFila(FilaDinamica *fila);
float* copiarParaArray(FilaDinamica *fila);
void lerRatingsParaFila(FilaDinamica *fila, const char *arquivo, int limite);
#endif