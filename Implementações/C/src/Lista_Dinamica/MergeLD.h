#ifndef MERGELD_H
#define MERGELD_H
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <stddef.h>
#include "ListaD.h"

NoLD* mergeLD(NoLD *esq, NoLD *dir);
void mergeSortLista(NoLD **inicio);
void salvarLista(const char *nome, NoLD *lista);

extern int profundidade_atual;
extern int profundidade_maxima;
#endif