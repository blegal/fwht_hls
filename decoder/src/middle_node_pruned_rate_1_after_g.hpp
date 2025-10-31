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
template <int gf_size> void middle_node_pruned_rate_1_after_g(
    symbols_t * inputs,  // Inputs are the symbols from the channel (from the right)
    uint16_t * decoded,  // Decoded symbols are the final output of the decoder (done on the left)
    uint16_t * symbols,  // Symbols are the ones going from leafs to root (done on the left)
    int        size      // Size is the number of symbols (should be a power of 2)
) {
#pragma HLS INLINE
    for (int i = 0; i < size; i++)
    {
        const int value = argmax/*<gf_size>*/(inputs[i].value);
        symbols[i]      = value;
        decoded[i]      = value;
    }
    // oups local_remove_xors(decoded, size);
}

