#ifndef MERGELL_H
#define MERGELL_H
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <stddef.h>
#include "ListaL.h"

extern size_t memoriaLL_durante_execução;

void mergeLL(float arr[], int esquerda, int meio, int direita);
void mergeSortLL(float arr[], int esquerda, int direita);
void salvarEmArquivo(const float* arr, int tamanho, int n);
#endif