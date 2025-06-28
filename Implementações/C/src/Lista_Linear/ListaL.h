#ifndef LISTAL_H
#define LISTAL_H
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <time.h>

#define MAX_TAMANHO 1000000

typedef struct {
    float dados[MAX_TAMANHO];
    int tamanho;
} ListaLinear;

void carregarRatings(const char* ratingscsv, ListaLinear* lista, int n);

#endif