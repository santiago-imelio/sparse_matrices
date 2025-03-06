#include <stdio.h>
#include <stdlib.h>
#include "mbr.h"

int main()
{
    int m = 6;
    int n = 6;
    int blk_rows = 3;
    int blk_columns = 3;
    int nnz_blocks = 7;
    int r = 2;
    int c = 2;

    float *values = (float *)malloc((nnz_blocks * r * c) * sizeof(float));
    int *col_idx = (int *)malloc(nnz_blocks * sizeof(int));
    int *row_ptr = (int *)malloc((nnz_blocks + 1) * sizeof(int));
    int *bmap = (int *)malloc(nnz_blocks * sizeof(int));

    float values_static[] = {5,1,0,1,7,0,0,2,0,0,3,0,0,2,0,0,4,0,1,3,0,6,0,0,3,0,0,0};
    for (int i = 0; i < (nnz_blocks * r * c); i++)
        values[i] = values_static[i];

    int col_idx_static[] = {0,1,2,0,1,0,2};
    for (int i = 0; i < nnz_blocks; i++)
        col_idx[i] = col_idx_static[i];

    int row_ptr_static[] = {0,3,5,7};
    for (int i = 0; i <= nnz_blocks; i++)
        row_ptr[i] = row_ptr_static[i];

    int bmap_static[] = {11,9,4,2,13,2,1};
    for (int i = 0; i < nnz_blocks; i++)
        bmap[i] = bmap_static[i];

    mbr *C = malloc(sizeof(mbr));
    C->blk_rows = blk_rows;
    C->blk_columns = blk_columns;
    C->nnz_blocks = nnz_blocks;
    C->r = r;
    C->c = c;
    C->values = values;
    C->col_index = col_idx;
    C->row_ptr = row_ptr;
    C->bitmap = bmap;

    float *v = (float *)malloc(m * sizeof(float));
    for (int i = 0; i < m; i++)
        v[i] = i;

    float *x = (float *)malloc(m * sizeof(float));

    spmv_mbr(C, v, x);

    for (int k = 0; k < m; k++)
    {
        printf("%.1f ", x[k]);
    }

    free(C->values);
    free(C->col_index);
    free(C->row_ptr);
    free(C->bitmap);
    free(C);
    free(v);
    free(x);
}