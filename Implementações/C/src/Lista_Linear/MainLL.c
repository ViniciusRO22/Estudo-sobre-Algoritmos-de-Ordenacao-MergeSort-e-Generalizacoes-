#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "MergeLL.h"
#include "ListaL.h"


typedef struct {
    int size;
    char structure[10];      
    char representation[10]; 
    double duration_s;
    size_t mem_bytes;
} ResultadoCSV;



void executarListaLinear() {
    const char* arquivoCSV = "data/Input/ratings.csv";
    int tamanhos[] = {100, 1000, 10000, 100000, 1000000};
    int numTamanhos = sizeof(tamanhos) / sizeof(int);
    ResultadoCSV resultado;

    for (int i = 0; i < numTamanhos; i++) {
        ListaLinear lista;
        double somaTempos = 0.0;
        size_t  memoria_usada = 0;

        for (int j = 0; j < 10; j++) {
            carregarRatings(arquivoCSV, &lista, tamanhos[i]);

            memoriaLL_durante_execução = 0;

            clock_t inicio = clock();
            mergeSortLL(lista.dados, 0, lista.tamanho - 1);
            clock_t fim = clock();

            somaTempos += (double)(fim - inicio) / CLOCKS_PER_SEC;
            memoria_usada += memoriaLL_durante_execução;
            if (j == 9) {
                salvarEmArquivo(lista.dados, lista.tamanho, tamanhos[i]);
            }
        }

        resultado.size = tamanhos[i];
        strcpy(resultado.structure, "lista");
        strcpy(resultado.representation, "linear");
        resultado.duration_s = somaTempos / 10.0;
        resultado.mem_bytes = memoria_usada / 10;

        printf("%d,%s,%s,%.6f,%zu\n",
               resultado.size,
               resultado.structure,
               resultado.representation,
               resultado.duration_s,
               resultado.mem_bytes);
    }

    char nome[32];
    sprintf(nome, "data/Output/output_%d.txt", tamanhos[numTamanhos - 1]);
 
}
   
