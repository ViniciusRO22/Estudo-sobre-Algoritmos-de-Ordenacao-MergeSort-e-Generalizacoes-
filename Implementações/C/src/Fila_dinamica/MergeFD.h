#ifndef MERGEFD_H
#define MERGEFD_H
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <stddef.h>
#include "FilaD.h"

extern size_t memoriaFilaD_durante_execução;

void mergeFD(float arr[], int esq, int meio, int dir) ;
void mergeSortFD(float arr[], int esq, int dir) ;
void salvarArrayEmArquivo(const char *arquivo, float *array, int tamanho);
#endif