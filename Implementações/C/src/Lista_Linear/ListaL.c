#include "ListaL.h"

void carregarRatings(const char* ratingscsv, ListaLinear* lista, int n) {
    FILE* f = fopen("data/Input/ratings.csv", "r");
    if (!f) {
        perror("Erro ao abrir o arquivo");
        exit(1);
    }

    char linha[1024];
    fgets(linha, 1024, f); 
    lista->tamanho = 0;

    while (fgets(linha, 1024, f) && lista->tamanho < n) {
        char* token = strtok(linha, ","); 
        token = strtok(NULL, ",");        
        token = strtok(NULL, ",");        // rating
        if (token) {
            lista->dados[lista->tamanho++] = atof(token);
        }
    }

    fclose(f);
}



