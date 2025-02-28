#include <stdio.h>
#include <stdlib.h>
#include "csr.h"

int main()
{
    int nnz = 9;
    int m = 4;
    int n = 4;
    float *values = (float *)malloc(nnz * sizeof(float));
    int *col_idx = (int *)malloc(nnz * sizeof(int));
    int *row_ptr = (int *)malloc((m + 1) * sizeof(int));

    for (int i = 0; i < nnz; i++)
        values[i] = i + 1;

    int col_idx_static[] = {0, 1, 2, 3, 0, 1, 2, 3, 2};
    for (int i = 0; i < nnz; i++)
        col_idx[i] = col_idx_static[i];

    int row_ptr_static[] = {0, 4, 6, 8, 9};
    for (int i = 0; i <= m; i++)
        row_ptr[i] = row_ptr_static[i];

    csr *C = malloc(sizeof(csr));
    C->nnz = nnz;
    C->m = m;
    C->n = n;
    C->values = values;
    C->col_index = col_idx;
    C->row_ptr = row_ptr;

    float *v = (float *)malloc(m * sizeof(float));
    for (int i = 0; i < m; i++)
        v[i] = i;

    float *x = (float *)malloc(m * sizeof(float));

    spmv_csr(C, v, x);

    for (int k = 0; k < m; k++)
    {
        printf("%.1f ", x[k]);
    }

    free(C->values);
    free(C->col_index);
    free(C->row_ptr);
    free(C);
    free(v);
    free(x);

    return 0;
}