#pragma once
//
//
//
//
//
#include "archi.hpp"
//
//
//
//
//
template <int gf_size> void middle_node_pruned_rate_0(
    uint16_t* __restrict decoded,  // Decoded symbols are the final output of the decoder (done on the left)
    uint16_t* __restrict symbols,  // Symbols are the ones going from leafs to root (done on the left)
    int        size      // Size is the number of symbols (should be a power of 2)
) {
#pragma HLS INLINE
    for (int i = 0; i < size; i++) {
        symbols[i] = 0;
        decoded[i] = 0;
    }
}
