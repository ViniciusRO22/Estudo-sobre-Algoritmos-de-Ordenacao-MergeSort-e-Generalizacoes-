#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <math.h>
#include "Lista_Linear/MergeLL.h"
#include "Lista_Dinamica/MergeLD.h"
#include "Pilha_Linear/MergePL.h"
#include "Fila_dinamica/MergeFD.h"
#include "Fila_linear/MergeFL.h"
#include "Pilha_Dinamica/MergePD.h"
#include "Lista_Linear/ListaL.h"
#include "Lista_Dinamica/ListaD.h"
#include "Pilha_Linear/PilhaL.h"
#include "Pilha_Dinamica/PilhaD.h"
#include "Fila_linear/FilaL.h"
#include "Fila_dinamica/FilaD.h"



    void executarListaLinear();
    void executarListaDinamica();
    void executarPilhaLinear();
    void executarPilhaDinamica();
    void executarFilaLinear();
    void executarFilaDinamica();

int main() {
    freopen("data/Output/resultados_benchmark.csv", "w", stdout);
    printf("size,structure,representation,duration_s,mem_bytes\n");

    executarListaLinear();
    executarListaDinamica();
    executarPilhaLinear();
    executarPilhaDinamica();
    executarFilaLinear();
    executarFilaDinamica();


    
    fclose(stdout);
    return 0;
}
