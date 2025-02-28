#include "csr.h"

void *spmv_csr(csr *a, float *v, float *x)
{
    int m = a->m;

    for (int i = 0; i < m; i++)
    {
        int row_start_idx = a->row_ptr[i];
        int row_end_idx = a->row_ptr[i + 1];

        float xi = 0;

        for (int k = row_start_idx; k < row_end_idx; k++)
        {
            int col = a->col_index[k];
            xi += v[col] * a->values[k];
        }

        x[i] = xi;
    }
}