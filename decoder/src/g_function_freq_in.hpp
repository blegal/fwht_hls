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
template <int gf_size> void g_function_freq_in(
		symbols_t* __restrict dst,   // the data to be computed for the left side of the graph
		symbols_t* __restrict src_a, // the upper value set from the right side of the graph
		symbols_t* __restrict src_b, // the lower value set from the right side of the graph
		const uint16_t*  __restrict src_c,    // the computed symbols coming from the left side of the graph
		const int n_symbols)
{
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
		const symbols_t tmp_d = normalize(tmp_c);
		dst[s] =  tmp_d;
	}

}
//
//
//
//
//
template <int gf_size, int n_symbols> inline __attribute__((always_inline)) void g_function_freq_in(
		symbols_t* __restrict dst,   // the data to be computed for the left side of the graph
		symbols_t* __restrict src_a, // the upper value set from the right side of the graph
		symbols_t* __restrict src_b, // the lower value set from the right side of the graph
		const uint16_t*  __restrict src_c  // the computed symbols coming from the left side of the graph
		)
{

	for (int s = 0; s < n_symbols; s++)
	{
#pragma HLS PIPELINE off

		const symbols_t ia = src_a[s];
		const symbols_t ib = src_b[s];

		symbols_t oa, ob;
		fwht_norm_64_io(ia.value, oa.value);
		fwht_norm_64_io(ib.value, ob.value);

		const symbols_t tmp_c = multiply_symbol(oa, ob);
		const symbols_t tmp_d = normalize(tmp_c);
		dst[s] =  tmp_d;
	}

}
//
//
//
//
//
template <int gf_size> inline __attribute__((always_inline)) void g_function_freq_in_after_rate_0(
		symbols_t* __restrict dst,   // the data to be computed for the left side of the graph
		symbols_t* __restrict src_a, // the upper value set from the right side of the graph
		symbols_t* __restrict src_b, // the lower value set from the right side of the graph
		const int n_symbols)
{
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
		const symbols_t tmp_d = normalize(tmp_c);
		dst[s] = tmp_d;
	}
}
//
//
//
//
//
