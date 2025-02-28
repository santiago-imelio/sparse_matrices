/**
 * Compressed Sparse Row.
 */
typedef struct csr
{
    int m;
    int n;
    int nnz;
    float *values;
    int *col_index;
    int *row_ptr;
} csr;

void *spmv_csr(csr *a, float *v, float *x);