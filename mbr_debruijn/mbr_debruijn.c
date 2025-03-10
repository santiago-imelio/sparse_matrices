#include "mbr_debruijn.h"
#include <stdio.h>

// De Bruijn sequence
#define DEBRUIJN32 0x077CB531U

// Lookup table for bit position
static const int debruijn_bit_index[32] = {
    0, 1, 28, 2, 29, 14, 24, 3, 30, 22, 20, 15, 25, 17, 4, 8,
    31, 27, 13, 23, 21, 19, 16, 7, 26, 12, 18, 6, 11, 5, 10, 9
};

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

            while (bmap != 0)
            {
                // Find the position of the least significant set bit
                int y = bmap & (-bmap);
                int z = (int) DEBRUIJN32 * y;
                int bit_idx = debruijn_bit_index[z >> 27];

                bmap &= bmap - 1; // Clear the least significant set bit

                int row_in_block = bit_idx / c;
                int col_in_block = bit_idx % c;

                int i = by * r + row_in_block;
                int j = bx * c + col_in_block;

                x[i] += a->values[values_idx] * v[j];
                values_idx++;
            }
        }
    }
};