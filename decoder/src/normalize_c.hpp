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

symbols_t normalize(const symbols_t src)
{

#pragma HLS ARRAY_PARTITION dim=1 factor=4 type=cyclic variable=src.value
#pragma HLS INLINE off

#pragma HLS ALLOCATION operation instances=fadd limit=4
#pragma HLS ALLOCATION operation instances=fmul limit=4

    float loc[16];
    loc[ 0]  = (src.value[ 0] + src.value[ 1]) + (src.value[ 2] + src.value[ 3]);
    loc[ 1]  = (src.value[ 4] + src.value[ 5]) + (src.value[ 6] + src.value[ 7]);
    loc[ 2]  = (src.value[ 8] + src.value[ 9]) + (src.value[10] + src.value[11]);
    loc[ 3]  = (src.value[12] + src.value[13]) + (src.value[14] + src.value[15]);
    loc[ 4]  = (src.value[16] + src.value[17]) + (src.value[18] + src.value[19]);
    loc[ 5]  = (src.value[20] + src.value[21]) + (src.value[22] + src.value[23]);
    loc[ 6]  = (src.value[24] + src.value[25]) + (src.value[26] + src.value[27]);
    loc[ 7]  = (src.value[28] + src.value[29]) + (src.value[30] + src.value[31]);
    loc[ 8]  = (src.value[32] + src.value[33]) + (src.value[34] + src.value[35]);
    loc[ 9]  = (src.value[36] + src.value[37]) + (src.value[38] + src.value[39]);
    loc[10]  = (src.value[40] + src.value[41]) + (src.value[42] + src.value[43]);
    loc[11]  = (src.value[44] + src.value[45]) + (src.value[46] + src.value[47]);
    loc[12]  = (src.value[48] + src.value[49]) + (src.value[50] + src.value[51]);
    loc[13]  = (src.value[52] + src.value[53]) + (src.value[54] + src.value[55]);
    loc[14]  = (src.value[56] + src.value[57]) + (src.value[58] + src.value[59]);
    loc[15]  = (src.value[60] + src.value[61]) + (src.value[62] + src.value[63]);

    float p0 = (loc[ 0] + loc[ 1]) + (loc[ 2] + loc[ 3]);
    float p1 = (loc[ 4] + loc[ 5]) + (loc[ 6] + loc[ 7]);
    float p2 = (loc[ 8] + loc[ 9]) + (loc[10] + loc[11]);
    float p3 = (loc[12] + loc[13]) + (loc[14] + loc[15]);

    const float sum    = (p0 + p1) + (p2 + p3);
    const float factor = 1.f / sum;

    symbols_t dst;
#pragma HLS ARRAY_PARTITION dim=1 factor=4 type=cyclic variable=dst.value
    for (int i = 0; i < 64; i++) {
#pragma HLS PIPELINE
#pragma HLS UNROLL factor=4
        dst.value[i] = src.value[i] * factor;
    }
    return dst;
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

symbols_s<64> normalize_n64(const symbols_s<64> src)
{
#pragma HLS ARRAY_PARTITION dim=1 factor=4 type=cyclic variable=src.value
#pragma HLS INLINE off

#pragma HLS ALLOCATION operation instances=fadd limit=4
#pragma HLS ALLOCATION operation instances=fmul limit=4

    float loc[16];
    loc[ 0]  = (src.value[ 0] + src.value[ 1]) + (src.value[ 2] + src.value[ 3]);
    loc[ 1]  = (src.value[ 4] + src.value[ 5]) + (src.value[ 6] + src.value[ 7]);
    loc[ 2]  = (src.value[ 8] + src.value[ 9]) + (src.value[10] + src.value[11]);
    loc[ 3]  = (src.value[12] + src.value[13]) + (src.value[14] + src.value[15]);
    loc[ 4]  = (src.value[16] + src.value[17]) + (src.value[18] + src.value[19]);
    loc[ 5]  = (src.value[20] + src.value[21]) + (src.value[22] + src.value[23]);
    loc[ 6]  = (src.value[24] + src.value[25]) + (src.value[26] + src.value[27]);
    loc[ 7]  = (src.value[28] + src.value[29]) + (src.value[30] + src.value[31]);
    loc[ 8]  = (src.value[32] + src.value[33]) + (src.value[34] + src.value[35]);
    loc[ 9]  = (src.value[36] + src.value[37]) + (src.value[38] + src.value[39]);
    loc[10]  = (src.value[40] + src.value[41]) + (src.value[42] + src.value[43]);
    loc[11]  = (src.value[44] + src.value[45]) + (src.value[46] + src.value[47]);
    loc[12]  = (src.value[48] + src.value[49]) + (src.value[50] + src.value[51]);
    loc[13]  = (src.value[52] + src.value[53]) + (src.value[54] + src.value[55]);
    loc[14]  = (src.value[56] + src.value[57]) + (src.value[58] + src.value[59]);
    loc[15]  = (src.value[60] + src.value[61]) + (src.value[62] + src.value[63]);

    float p0 = (loc[ 0] + loc[ 1]) + (loc[ 2] + loc[ 3]);
    float p1 = (loc[ 4] + loc[ 5]) + (loc[ 6] + loc[ 7]);
    float p2 = (loc[ 8] + loc[ 9]) + (loc[10] + loc[11]);
    float p3 = (loc[12] + loc[13]) + (loc[14] + loc[15]);

    const float sum    = (p0 + p1) + (p2 + p3);
    const float factor = 1.f / sum;

    symbols_s<64> dst;
#pragma HLS ARRAY_PARTITION dim=1 factor=4 type=cyclic variable=dst.value
    for (int i = 0; i < 64; i++) {
#pragma HLS PIPELINE
#pragma HLS UNROLL factor=4
        dst.value[i] = src.value[i] * factor;
    }
    return dst;
}
//
//
//
///////////////////////////////////////////////////////////////////////////////////////////////////////////
//
//
//
