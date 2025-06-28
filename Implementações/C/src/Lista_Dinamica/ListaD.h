#ifndef LISTAD_H
#define LISTAD_H


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

typedef struct NoLD {
    float rating;
    struct NoLD *prox;
} NoLD;


void inserirFinal(NoLD **inicio, NoLD **fim, float rating);
void liberarLista(NoLD *inicio);
void dividirLista(NoLD *origem, NoLD **frente, NoLD **tras);
void lerRatingsParaLista(NoLD **lista, const char *arquivo, int limite);

#endif