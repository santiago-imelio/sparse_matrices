#include "bcsr.h"

void spmv_bcsr(bcsr *a, float *v, float *x)
{
    int m = a->m;

    for (int i = 0; i < m; i++)
    {
        int row_start_idx = a->row_ptr[i];
        int row_end_idx = a->row_ptr[i + 1];

        float xi = 0;

        for (int k = row_start_idx; k < row_end_idx; k++)
        {
            int start_col_idx = a->col_index[k];
            int block_start_idx = a->nz_ptr[k];
            int block_end_idx = a->nz_ptr[k + 1];

            int t = 0;

            for (int l = block_start_idx; l < block_end_idx; l++)
            {
                xi += v[start_col_idx + t] * a->values[l];
                t++;
            }
        }

        x[i] = xi;
    }
}