#include <stdio.h>
#include <stdlib.h>
#include "bcsr.h"

int main()
{
    int nnz = 12;
    int m = 5;
    int n = 5;
    int n_blocks = 7;

    float *values = (float *)malloc(nnz * sizeof(float));
    int *col_idx = (int *)malloc(n_blocks * sizeof(int));
    int *row_ptr = (int *)malloc((m + 1) * sizeof(int));
    int *nz_ptr = (int *)malloc((n_blocks + 1) * sizeof(int));

    float values_static[] = {5, 1, 7, 1, 2, 3, 2, 4, 1, 3, 6, 3};
    for (int i = 0; i < nnz; i++)
        values[i] = values_static[i];

    int col_idx_static[] = {1, 2, 4, 2, 3, 2, 5}; // one-indexed
    for (int i = 0; i < n_blocks; i++)
        col_idx[i] = col_idx_static[i] - 1;

    int row_ptr_static[] = {1, 2, 4, 5, 6, 8}; // one-indexed
    for (int i = 0; i <= m; i++)
        row_ptr[i] = row_ptr_static[i] - 1;

    int nz_ptr_static[] = {1, 4, 5, 7, 9, 11, 12, 13}; // one-indexed
    for (int i = 0; i <= n_blocks; i++)
        nz_ptr[i] = nz_ptr_static[i] - 1;

    bcsr *C = malloc(sizeof(bcsr));
    C->nnz = nnz;
    C->m = m;
    C->n = n;
    C->values = values;
    C->col_index = col_idx;
    C->row_ptr = row_ptr;
    C->nz_ptr = nz_ptr;

    float *v = (float *)malloc(m * sizeof(float));
    for (int i = 0; i < m; i++)
        v[i] = i;

    float *x = (float *)malloc(m * sizeof(float));

    spmv_bcsr(C, v, x);

    // for (int k = 0; k < m; k++)
    // {
    //     printf("%.1f ", x[k]);
    // }

    free(C->values);
    free(C->col_index);
    free(C->row_ptr);
    free(C->nz_ptr);
    free(C);
    free(v);
    free(x);
}