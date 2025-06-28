#ifndef PILHAL_H
#define PILHAL_H


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define MAX_TAMANHO 1000000

typedef struct {
    float dados[MAX_TAMANHO];
    int topo;
} PilhaLinear;

void inicializarPilhaL(PilhaLinear* pilha);
int pushPL(PilhaLinear* pilha, float valor);
float pop(PilhaLinear* pilha);
void carregarRatingsPL(const char* ratingscsv, PilhaLinear* pilha, int n);
#endif