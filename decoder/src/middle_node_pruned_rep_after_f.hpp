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
extern void local_remove_xors(uint16_t * values, int size);

template <int gf_size> void middle_node_pruned_rep_after_f(
    symbols_t* __restrict inputs,  // Inputs are the symbols from the channel (from the right)
    uint16_t*  __restrict decoded, // Decoded symbols are the final output of the decoder (done on the left)
    uint16_t*  __restrict symbols, // Symbols are the ones going from leafs to root (done on the left)
    int                   size     // Size is the number of symbols (should be a power of 2)
) {
#pragma HLS INLINE
        for(int i = 0; i < size; i++) {
#pragma HLS PIPELINE off
    		const symbols_t ia = inputs[i];
    		symbols_t oa;
    		fwht_norm_64_io(ia.value, oa.value);
            inputs[i] = normalize( oa );
        }

		const symbols_t ia = inputs[0];
        const symbols_t	ib = inputs[1];

        symbols_t temp = multiply_symbol(ia, ib);
        for(int i = 2; i < size; i++){
#pragma HLS PIPELINE off
    		const symbols_t tt = inputs[i];
    		temp = multiply_symbol(temp, tt);
        }

        const int value = argmax( temp.value );

        for(int i = 0; i < size; i++)
        {
            symbols[i] = value;
            decoded[i] = 0; // should be corrected (it is systematic solution actually)
        }
        decoded[size-1] = value; // should be corrected (it is systematic solution actually)
}

