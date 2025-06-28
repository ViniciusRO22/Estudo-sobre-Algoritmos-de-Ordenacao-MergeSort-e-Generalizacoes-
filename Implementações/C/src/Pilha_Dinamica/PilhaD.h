#ifndef PILHAD_H
#define PILHAD_H
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <time.h>
typedef struct No {
    float rating;
    struct No *prox;
} No;

typedef struct {
    No *topo;      
    int tamanho;   
} PilhaDinamica;

void inicializarPilhaD(PilhaDinamica *p);
void push(PilhaDinamica *p, float valor);
void liberarPilha(PilhaDinamica *p);
float* copiarParaArrayPD(PilhaDinamica *p);
void lerRatingsParaPilha(PilhaDinamica *p, const char *arquivo, int limite);



#endif