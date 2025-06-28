#include "MergePD.h"


void mergePD(float a[], int l, int m, int r) {
    int n1 = m - l + 1,  n2 = r - m;

    memoriaPD_durante_execução += sizeof(float) * n1 + n2 * sizeof(float);
    
    float *L = (float*)malloc(n1 * sizeof(float));
    float *R = (float*)malloc(n2 * sizeof(float));
    for (int i = 0; i < n1; i++) L[i] = a[l+i];
    for (int j = 0; j < n2; j++) R[j] = a[m+1+j];

    int i=0, j=0, k=l;
    while (i<n1 && j<n2) a[k++] = (L[i]<=R[j]) ? L[i++] : R[j++];
    while (i<n1) a[k++] = L[i++];
    while (j<n2) a[k++] = R[j++];

    free(L); free(R);
}

void mergeSortPD(float a[], int l, int r) {
    if (l < r) {
        int m = l + (r-l)/2;
        mergeSortPD(a, l, m);
        mergeSortPD(a, m+1, r);
        mergePD(a, l, m, r);
    }
}

void salvarArray(const char *nome, float *v, int n) {
    FILE *fp = fopen(nome, "w");
    if (!fp) { perror("output"); exit(EXIT_FAILURE); }
    for (int i = 0; i < n; i++) fprintf(fp, "%.1f\n", v[i]);
    fclose(fp);
}
