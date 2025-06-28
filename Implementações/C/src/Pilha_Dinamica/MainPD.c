#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "PilhaD.h"       
#include "MergePD.h"       

typedef struct {
    int size;
    char structure[16];      
    char representation[16];
    double duration_s;       
    size_t mem_bytes;        
} ResultadoCSV;

size_t memoriaPD_durante_execução = 0;

void executarPilhaDinamica() {
    const char *arquivoCSV = "data/Input/ratings.csv";
    int tamanhos[] = {100, 1000, 10000, 100000, 1000000};
    int numTamanhos = sizeof(tamanhos) / sizeof(int);
    ResultadoCSV resultado;

    for (int i = 0; i < numTamanhos; i++) {
        double somaTempos = 0.0;
        size_t somaMemoria = 0;

        for (int j = 0; j < 10; j++) {
            PilhaDinamica pilha;
            inicializarPilhaD(&pilha);
            lerRatingsParaPilha(&pilha, arquivoCSV, tamanhos[i]);
            memoriaPD_durante_execução = 0;
            float *arr = copiarParaArrayPD(&pilha);

            clock_t inicio = clock();
            mergeSortPD(arr, 0, pilha.tamanho - 1);
            clock_t fim = clock();

            somaTempos += (double)(fim - inicio) / CLOCKS_PER_SEC;
            somaMemoria += memoriaPD_durante_execução;
            if (j == 9) {
                char nome[32];
                sprintf(nome, "data/Output/output_%d.txt", tamanhos[i]);
                salvarArray(nome, arr, pilha.tamanho);
            }

            free(arr);
            liberarPilha(&pilha);
        }

        resultado.size = tamanhos[i];
        strcpy(resultado.structure, "pilha");
        strcpy(resultado.representation, "dinamica");
        resultado.duration_s = somaTempos / 10.0;
        resultado.mem_bytes = somaMemoria / 10.0;

        printf("%d,%s,%s,%.6f,%zu\n",
               resultado.size,
               resultado.structure,
               resultado.representation,
               resultado.duration_s,
               resultado.mem_bytes);
    }
}
