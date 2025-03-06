#include "mbr.h"
#include <stdio.h>

// void spmv_mbr(mbr *a, float *v, float *x)
// {
//     int block_rows = a->blk_rows;
//     int block_columns = a->blk_columns;

//     for (int by = 0; by < block_rows; by++)
//     {
//         for (int bx = 0; bx < block_columns; bx++)
//         {
//             int blk = by * block_columns + bx;
//             printf("Block %d\n", blk);
//         }
//     }
// };

void spmv_mbr(mbr *a, float *v, float *x)
{
    int block_rows = a->blk_rows;
    int block_columns = a->blk_columns;
    int r = a->r;
    int c = a->c;

    for (int by = 0; by < a->blk_rows; by++)
    {
        int block_x_start = a->row_ptr[by];
        int block_x_end = a->row_ptr[by + 1];

        for (int blk_id = block_x_start; blk_id < block_x_end; blk_id++)
        {
            float xi = 0;

            int bx = a->col_index[blk_id];
            int bmap = a->bitmap[blk_id];

            int bit_idx = 0;
            int i;

            /***** TODO: this part is wrong ******/
            while (bmap != 0)
            {
                printf("Block %d - Bitmap is %d - Looking at bit %d\n", blk_id, bmap, bit_idx);
                if ((bmap & 1) == 1)
                {
                    i = bit_idx % r + by * r;
                    int j = bit_idx % c + bx * c;

                    printf("Doing values[%d] * v[%d]\n", i, j);
                    printf("\n");
                    xi += a->values[i] * v[j];
                }

                x[i] = xi;

                bmap = bmap >> 1;

                if (bmap == 0) {
                    bit_idx = 0;
                } else {
                    bit_idx++;
                }
            }
            /***** TODO: this part is wrong ******/
        }
    }
};