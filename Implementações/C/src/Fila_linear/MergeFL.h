#ifndef MERGEFL_H
#define MERGEFL_H   
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <stddef.h>
#include "FilaL.h"

extern size_t memoriaFilaL_durante_execução;

void mergeFL(float arr[], int l, int m, int r) ;
void mergeSortFL(float arr[], int l, int r) ;
void salvarOrdenadoEmArquivo(FilaLinear* fila, const char* nomeArquivo) ;
#endif