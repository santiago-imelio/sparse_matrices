/**
 * Blocked Compressed Sparse Row.
 */
typedef struct bcsr
{
    int m;
    int n;
    int nnz;
    int n_blocks;
    float *values;
    int *col_index;
    int *row_ptr;
    int *nz_ptr;
} bcsr;

void spmv_bcsr(bcsr *a, float *v, float *x);