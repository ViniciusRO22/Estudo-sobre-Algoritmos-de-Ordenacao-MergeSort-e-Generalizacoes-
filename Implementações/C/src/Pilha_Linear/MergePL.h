#ifndef MERGELL_H
#define MERGELL_H
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <stddef.h>
#include "PilhaL.h"

extern size_t memoriaPL_durante_execução;

void mergePL(float arr[], int esquerda, int meio, int direita);
void mergeSortPL(float arr[], int esquerda, int direita);
void salvarEmArquivoPL(PilhaLinear* pilha, int n);
#endif