#include "mbr.h"
#include <stdio.h>

void spmv_mbr(mbr *a, float *v, float *x)
{
    for (int i = 0; i < a->m; i++)
        x[i] = 0;

    int block_rows = a->blk_rows;
    int block_columns = a->blk_columns;
    int r = a->r;
    int c = a->c;

    int values_idx = 0;

    for (int by = 0; by < a->blk_rows; by++)
    {
        int block_x_start = a->row_ptr[by];
        int block_x_end = a->row_ptr[by + 1];

        for (int blk_id = block_x_start; blk_id < block_x_end; blk_id++)
        {
            int bx = a->col_index[blk_id];
            int bmap = a->bitmap[blk_id];

            int bit_idx = 0;

            while (bmap != 0)
            {
                if ((bmap & 1) == 1)
                {
                    int row_in_block = bit_idx / c; // Row within the block
                    int col_in_block = bit_idx % c; // Column within the block

                    int i = by * r + row_in_block; // Row in matrix
                    int j = bx * c + col_in_block; // Column in matrix

                    x[i] += a->values[values_idx] * v[j];
                    values_idx++;
                }

                bmap >>= 1;
                bmap == 0 ? bit_idx = 0 : bit_idx++;
            }
        }
    }
};