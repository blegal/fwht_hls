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
template <int gf_size> void f_function_freq_in(
          symbols_t* __restrict dst,
    const symbols_t* __restrict src_a,
    const symbols_t* __restrict src_b,
    const int n_symbols
){
#pragma HLS INLINE
    for (int s = 0; s < n_symbols; s++)
    {
#pragma HLS PIPELINE off
		const symbols_t oa = src_a[s];
		const symbols_t ob = src_b[s];

		const symbols_t tmp_c = multiply_symbol(oa, ob);
		dst[s] = tmp_c;

    }
}
//
//
//
//
//
template <int gf_size, int n_symbols> inline __attribute__((always_inline)) void f_function_freq_in(
          symbols_t* __restrict dst,
    const symbols_t* __restrict src_a,
    const symbols_t* __restrict src_b
){
#pragma HLS INLINE
    for (int s = 0; s < n_symbols; s++)
    {
#pragma HLS PIPELINE off
		const symbols_t oa = src_a[s];
		const symbols_t ob = src_b[s];
		const symbols_t tmp_c = multiply_symbol(oa, ob);
		dst[s] = tmp_c;
    }
}
//
//
//
//
//
