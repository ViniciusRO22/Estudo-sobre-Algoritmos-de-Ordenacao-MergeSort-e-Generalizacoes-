#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <malloc.h>
#include <sys/resource.h>
#include "PilhaL.h"       
#include "MergePL.h"       

typedef struct {
    int size;
    char structure[16];     
    char representation[16]; 
    double duration_s;       
    size_t mem_bytes;        
} ResultadoCSV;
  
void executarPilhaLinear() {
    const char* arquivoCSV = "data/Input/ratings.csv";
    int tamanhos[] = {100, 1000, 10000, 100000, 1000000};
    int qtdTamanhos = sizeof(tamanhos) / sizeof(int);
    ResultadoCSV resultado;

    for (int i = 0; i < qtdTamanhos; i++) {
         double somaTempos = 0.0;
           PilhaLinear pilha;

           size_t memoria_usada = 0;

        for (int j = 0; j < 10; j++) {
            carregarRatingsPL(arquivoCSV, &pilha, tamanhos[i]);

            memoriaPL_durante_execução = 0;

            clock_t inicio = clock();
            mergeSortPL(pilha.dados, 0, pilha.topo - 1);
            clock_t fim = clock();

            somaTempos += (double)(fim - inicio) / CLOCKS_PER_SEC;
            memoria_usada += memoriaPL_durante_execução;
            
            if (j == 9) {
                char nome[32];
                sprintf(nome, "data/Output/output_%d.txt", tamanhos[i]);
                
            }
        }

        resultado.size = tamanhos[i];
        strcpy(resultado.structure, "pilha");
        strcpy(resultado.representation, "linear");
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
