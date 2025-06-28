#include "ListaD.h"

void inserirFinal(NoLD **inicio, NoLD **fim, float rating) {
    NoLD *novo = (NoLD*)malloc(sizeof(NoLD));
    novo->rating = rating;
    novo->prox = NULL;

    if (*inicio == NULL) {
        *inicio = novo;
        *fim = novo;
    } else {
        (*fim)->prox = novo;
        *fim = novo;
    }
}


void liberarLista(NoLD *inicio) {
    while (inicio) {
        NoLD *tmp = inicio;
        inicio = inicio->prox;
        free(tmp);
    }
}


void dividirLista(NoLD *origem, NoLD **frente, NoLD **tras) {
    NoLD *lento = origem;
    NoLD *rapido = origem->prox;

    while (rapido) {
        rapido = rapido->prox;
        if (rapido) {
            lento = lento->prox;
            rapido = rapido->prox;
        }
    }

    *frente = origem;
    *tras = lento->prox;
    lento->prox = NULL;
}




void lerRatingsParaLista(NoLD **lista, const char *arquivo, int limite) {
    FILE *fp = fopen("data/Input/ratings.csv", "r");
    if (!fp) {
        perror("Erro ao abrir ratings.csv");
        exit(EXIT_FAILURE);
    }

    char linha[256];
    fgets(linha, sizeof(linha), fp); 

    int uid, mid;
    float rating;
    long ts;

    NoLD *fim = NULL;
    int count = 0;
    while (count < limite && fgets(linha, sizeof(linha), fp)) {
        if (sscanf(linha, "%d,%d,%f,%ld", &uid, &mid, &rating, &ts) == 4) {
            inserirFinal(lista, &fim, rating);
            count++;
        }
    }

    fclose(fp);
}



