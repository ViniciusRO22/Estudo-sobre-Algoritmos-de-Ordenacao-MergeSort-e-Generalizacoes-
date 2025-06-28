#ifndef MERGEPD_H
#define MERGEPD_H
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <stddef.h>
#include "PilhaD.h"

void mergePD(float a[], int l, int m, int r);
void mergeSortPD(float a[], int l, int r);
void salvarArray(const char *nome, float *v, int n);
extern size_t memoriaPD_durante_execução;
#endif