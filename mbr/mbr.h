/**
 * Mapped Blocked Row.
 */
typedef struct mbr
{
    int m;
    int n;
    int blk_rows;
    int blk_columns;
    int nnz_blocks;
    int r;
    int c;
    float *values; // length r * c * nnz_blocks
    int *col_index;
    int *row_ptr;
    int *bitmap;
} mbr;

void spmv_mbr(mbr *a, float *v, float *x);