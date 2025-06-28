#include "ListaD.h"
#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stddef.h>
#include "MergeLD.h"
#include <math.h>



typedef struct {
    int size;
    char structure[10];
    char representation[10];
    double duration_s;
    size_t mem_bytes;
} ResultadoCSV;



void executarListaDinamica() {
    const char *arquivo = "data/Input/ratings.csv";
    int tamanhos[] = {100, 1000, 10000, 100000, 1000000};
    int qtd = sizeof(tamanhos) / sizeof(tamanhos[0]);
    ResultadoCSV resultado;

    for (int i = 0; i < qtd; i++) {
        double somaTempos = 0.0;
        size_t memoria_usada = 0;

        for (int j = 0; j < 10; j++) {
            NoLD *lista = NULL;

            lerRatingsParaLista(&lista, arquivo, tamanhos[i]);

            profundidade_atual = 0;
             profundidade_maxima = 0;

            clock_t t0 = clock();
            mergeSortLista(&lista);
            clock_t t1 = clock();

            size_t memoria_durante_ordenacao = tamanhos[i] * sizeof(NoLD) + profundidade_maxima * sizeof(NoLD*);
            memoria_usada += memoria_durante_ordenacao;

            somaTempos += (double)(t1 - t0) / CLOCKS_PER_SEC;

            
            if (j == 9) {
                char nome[32];
                sprintf(nome, "data/Output/output_%d.txt", tamanhos[i]);
                salvarLista(nome, lista);
            }

            liberarLista(lista);
        }

        resultado.size = tamanhos[i];
        strcpy(resultado.structure, "lista");
        strcpy(resultado.representation, "dinamica");
        resultado.duration_s = somaTempos / 10.0;
        resultado.mem_bytes = memoria_usada / 10.0;

        
        printf("%d,%s,%s,%.6f,%zu\n",
               resultado.size,
               resultado.structure,
               resultado.representation,
               resultado.duration_s,
               resultado.mem_bytes);
    }
}
