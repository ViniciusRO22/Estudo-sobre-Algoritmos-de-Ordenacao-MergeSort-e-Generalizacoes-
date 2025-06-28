#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "FilaD.h"
#include "MergeFD.h"


typedef struct {
    int size;
    char structure[10];      
    char representation[10]; 
    double duration_s;
    size_t mem_bytes;
} ResultadoCSV;


void executarFilaDinamica() {
    const char* arquivoCSV = "data/Input/ratings.csv";
    int entradas[] = {100, 1000, 10000, 100000, 1000000};
    int n = sizeof(entradas) / sizeof(entradas[0]);
    ResultadoCSV resultado;
    size_t memoria_usada = 0;

    for (int i = 0; i < n; i++) {
        FilaDinamica fila;
        iniciarFila(&fila);

        lerRatingsParaFila(&fila, arquivoCSV, entradas[i]);
        float *array = copiarParaArray(&fila);

        memoriaFilaD_durante_execução = 0;

        clock_t inicio = clock();
        mergeSortFD(array, 0, fila.tamanho - 1);
        clock_t fim = clock();

        memoria_usada += memoriaFilaD_durante_execução / 10;

        resultado.size = entradas[i];
        strcpy(resultado.structure, "fila");
        strcpy(resultado.representation, "dinamica");
        resultado.duration_s = ((double)(fim - inicio)) / CLOCKS_PER_SEC;
        resultado.mem_bytes = memoria_usada;

        
        printf("%d,%s,%s,%.6f,%zu\n",
               resultado.size,
               resultado.structure,
               resultado.representation,
               resultado.duration_s,
               resultado.mem_bytes);

        free(array);
        liberarFila(&fila);
    }
}
