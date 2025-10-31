//
// Created by legal on 03/07/2025.
//
#pragma once
//
//
//
///////////////////////////////////////////////////////////////////////////////////////////////////////////
//
//
//

symbols_t normalize(const symbols_t tab)
{
#pragma HLS ARRAY_PARTITION dim=1 type=complete variable=tab.value
	const int gf_size = 64;
#pragma HLS INLINE off
    float sum = 1e-32f;
    for (int i = 0; i < gf_size; i += 1) {
        sum += tab.value[i];
    }
    symbols_t result;
    const float factor = 1.f / sum;
    for (int i = 0; i < gf_size; i++) {
        result.value[i] = tab.value[i] * factor;
    }
    return result;
}

//
//
//
///////////////////////////////////////////////////////////////////////////////////////////////////////////
//
//
//
/*
template<int gf_size>
struct symbols_s {
    float value[gf_size];
};
*/

template <int size>
float make_sum(const float [size]);

template <>
float make_sum<1>(const float tab[1]) {
	return tab[0];
}

template <int size>
float make_sum(const float tab[size]) {
#pragma HLS inline
	static_assert((size >> 1) << 1 == size, "Error: size must be even.");
	return make_sum<size / 2>(tab) + make_sum<size / 2>(tab + size / 2);
}

symbols_s<64> normalize_n64(const symbols_s<64> tab_i)
{
#pragma HLS INLINE off
    //float sum1 = 1e-32f;
    //float sum2 = 1e-32f;

    const float sum = make_sum<64>(tab_i.value);
    //for (int i = 0; i < 32; i += 1)
   //{
//#pragma HLS PIPELINE
  //      sum1 += tab_i.value[i     ];
    //    sum2 += tab_i.value[i + 32];
    //}
    //float sum = sum1 + sum2;

    symbols_s<64> tab_o;
    const float factor = 1.f / sum;
    for (int i = 0; i < 64; i++) {
#pragma HLS UNROLL factor=64
    	tab_o.value[i] = tab_i.value[i] * factor;
    }
    return tab_o;
}
//
//
//
///////////////////////////////////////////////////////////////////////////////////////////////////////////
//
//
//
