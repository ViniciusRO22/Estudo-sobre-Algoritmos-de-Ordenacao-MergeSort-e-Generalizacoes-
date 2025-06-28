#ifndef FILAL_H
#define FILAL_H
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define MAX_TAM 1000000

typedef struct {
    float dados[MAX_TAM];
    int frente;
    int tras;
} FilaLinear;

void inicializarFila(FilaLinear* fila) ;
int enqueue(FilaLinear* fila, float valor);
void carregarRatingsFL(const char* arquivoCSV, FilaLinear* fila, int n);

#endif