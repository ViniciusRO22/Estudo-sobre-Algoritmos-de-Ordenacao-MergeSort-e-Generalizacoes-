#include "MergeLD.h"

int profundidade_atual = 0;
int profundidade_maxima = 0;


NoLD* mergeLD(NoLD *esq, NoLD *dir) {
    NoLD dummy;
    NoLD *atual = &dummy;
    dummy.prox = NULL;

    while (esq && dir) {
        if (esq->rating <= dir->rating) {
            atual->prox = esq;
            esq = esq->prox;
        } else {
            atual->prox = dir;
            dir = dir->prox;
        }
        atual = atual->prox;
    }

    atual->prox = (esq) ? esq : dir;
    return dummy.prox;
}

void mergeSortLista(NoLD **inicio) {
    if (*inicio == NULL || (*inicio)->prox == NULL)
        return;

profundidade_atual++;
   if( profundidade_atual > profundidade_maxima)
        profundidade_maxima = profundidade_atual;


    NoLD *frente, *tras;
    dividirLista(*inicio, &frente, &tras);

    mergeSortLista(&frente);
    mergeSortLista(&tras);

    *inicio = mergeLD(frente, tras);

    profundidade_atual--;
}

void salvarLista(const char *nome, NoLD *lista) {
    FILE *fp = fopen(nome, "w");
    if (!fp) {
        perror("Erro ao salvar arquivo de saída");
        exit(EXIT_FAILURE);
    }

    while (lista) {
        fprintf(fp, "%.1f\n", lista->rating);
        lista = lista->prox;
    }

    fclose(fp);
}