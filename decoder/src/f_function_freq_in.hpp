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
		const symbols_t ia = src_a[s];
		const symbols_t ib = src_b[s];

		symbols_t oa, ob;
		fwht_norm_64_io(ia.value, oa.value);
		fwht_norm_64_io(ib.value, ob.value);

		const symbols_t tmp_c = multiply_symbol(oa, ob);
		dst[s] = tmp_c;

//		for (int i = 0; i < gf_size; i++)
//        {
//            // TODO : attention au facteur 10x qui est magique !!!
//            dst[s].value[i] = src_a[s].value[i] * src_b[s].value[i];
//        }
//        dst[s].is_freq = true;
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
		const symbols_t ia = src_a[s];
		const symbols_t ib = src_b[s];
		symbols_t oa, ob;
		fwht_norm_64_io(ia.value, oa.value);
		fwht_norm_64_io(ib.value, ob.value);

		const symbols_t tmp_c = multiply_symbol(oa, ob);
		dst[s] = tmp_c;

//		for (int i = 0; i < gf_size; i++)
//        {
//            // TODO : attention au facteur 10x qui est magique !!!
//            dst[s].value[i] = src_a[s].value[i] * src_b[s].value[i];
//        }
//        dst[s].is_freq = true;
    }
}
//
//
//
//
//
