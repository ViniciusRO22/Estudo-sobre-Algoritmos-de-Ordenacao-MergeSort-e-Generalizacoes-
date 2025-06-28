#include "PilhaD.h"


void inicializarPilhaD(PilhaDinamica *p) {
    p->topo = NULL;
    p->tamanho = 0;
}

void push(PilhaDinamica *p, float valor) {
    No *novo = (No*)malloc(sizeof(No));
    novo->rating = valor;
    novo->prox = p->topo;
    p->topo = novo;
    p->tamanho++;
}

void liberarPilha(PilhaDinamica *p) {
    No *atual = p->topo;
    while (atual) {
        No *tmp = atual;
        atual = atual->prox;
        free(tmp);
    }
}
float* copiarParaArrayPD(PilhaDinamica *p) {
    float *v = (float*)malloc(p->tamanho * sizeof(float));
    No *atual = p->topo;
    for (int i = 0; i < p->tamanho; i++) {
        v[i] = atual->rating;
        atual = atual->prox;
    }
    return v;
}


void lerRatingsParaPilha(PilhaDinamica *p, const char *arquivo, int limite) {
    FILE *fp = fopen("data/Input/ratings.csv", "r");
    if (!fp) { perror("data/Input/ratings.csv"); exit(EXIT_FAILURE); }

    char linha[256];
    fgets(linha, sizeof(linha), fp);               

    int uid, mid; float rating; long ts;
    int count = 0;
    while (count < limite && fgets(linha, sizeof(linha), fp)) {
        if (sscanf(linha, "%d,%d,%f,%ld", &uid, &mid, &rating, &ts) == 4) {
            push(p, rating);
            count++;
        }
    }
    fclose(fp);
}



