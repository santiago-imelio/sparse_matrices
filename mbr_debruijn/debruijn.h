// de Bruijn sequence
#define DEBRUIJN32 0b00000111011111001011010100110001

/**
 * de Bruijn hash function.
 * Given n-bit single-1 bitstring, produces an log(n)-bit binary
 * number, where n is the length of the de Bruijn sequence used.
 *
 */
int debruijn_hash(int x) { return (x * (int)DEBRUIJN32) >> 27; }

/**
 * Precomputed de Bruijn lookup table.
 * `debruijn_lookup[b]` represents the position in the
 * de Bruijn sequence where the binary number `b` starts.
 */
static const int debruijn_lookup[32] = {
    0, 1, 28, 2, 29, 14, 24, 3, 30, 22, 20, 15, 25, 17, 4, 8,
    31, 27, 13, 23, 21, 19, 16, 7, 26, 12, 18, 6, 11, 5, 10, 9
};