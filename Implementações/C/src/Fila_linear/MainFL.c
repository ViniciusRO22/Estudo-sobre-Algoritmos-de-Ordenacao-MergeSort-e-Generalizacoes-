#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "FilaL.h"
#include "MergeFL.h"


void executarFilaLinear() {
    const char* arquivoCSV = "data/Input/ratings.csv";
    int tamanhos[] = {100, 1000, 10000, 100000, 1000000};
    int numTamanhos = sizeof(tamanhos) / sizeof(tamanhos[0]);

    for (int i = 0; i < numTamanhos; i++) {
        int n = tamanhos[i];
        double tempoTotal = 0.0;
        size_t memoria = 0;
        
        for (int j = 0; j < 10; j++) {
            FilaLinear fila;
            carregarRatingsFL(arquivoCSV, &fila, n);

            memoriaFilaL_durante_execução = 0;

            clock_t inicio = clock();
            mergeSortFL(fila.dados, 0, fila.tras);
            clock_t fim = clock();

            double tempo = (double)(fim - inicio) / CLOCKS_PER_SEC;
            tempoTotal += tempo;
            memoria += memoriaFilaL_durante_execução / 10;
           
            char nomeSaida[64];
             snprintf(nomeSaida, sizeof(nomeSaida), "data/Output/ouput_%d.txt", n);
        
        }

        double media = tempoTotal / 10.0;
        
        printf("%d,fila,linear,%.6f,%zu\n", n, media, memoria);
    }

}



