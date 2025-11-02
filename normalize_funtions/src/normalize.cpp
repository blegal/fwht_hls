#include <cstdio>
#include <cstdlib>
#include <cmath>
#include <ap_int.h>
#include <cstdint>

#define gf_size      64
#define log2_gf_size 64


typedef struct tuple{
    float   value;
    unsigned char index; // range [0...63]
} tuple;


tuple f_max(const tuple a, const tuple b)
{
#pragma HLS INLINE
    if( a.value > b.value )
    {
        return a;
    }else{
        return b;
    }
}
//
//
//
//////////////////////////////////////////////////////////////////////
//
//
//
void normalize_float32_t(const float src[gf_size], float dst[gf_size])
{
#pragma HLS INLINE off
    float sum = 1e-32f;
    for (int i = 0; i < gf_size; i += 1) {
#pragma HLS PIPELINE
        sum += src[i];
    }

    const float factor = 1.f / sum;
    for (int i = 0; i < gf_size; i++) {
#pragma HLS PIPELINE
        dst[i] = src[i] * factor;
    }
}
//
//
//
//////////////////////////////////////////////////////////////////////
//
//
//
void normalize_float32x2_t(const float src[gf_size], float dst[gf_size])
{
#pragma HLS ARRAY_PARTITION dim=1 factor=2 type=cyclic variable=src
#pragma HLS ARRAY_PARTITION dim=1 factor=2 type=cyclic variable=dst
#pragma HLS INLINE off

    float local[2] = {1e-32f, 1e-32f};
#pragma HLS ARRAY_PARTITION dim=1 type=complete variable=local
    for (int i = 0; i < gf_size; i += 2) {
#pragma HLS PIPELINE
        for (int  k = 0; k < 2; k += 1)
        {
#pragma HLS UNROLL factor=2
            local[k]    += src[i + k];
        }
    }
    const float sum    = local[0] + local[1];
    const float factor = 1.f / sum;

    for (int i = 0; i < gf_size; i++) {
#pragma HLS PIPELINE
#pragma HLS UNROLL factor=2
        dst[i] = src[i] * factor;
    }
}
//
//
//
//////////////////////////////////////////////////////////////////////
//
//
//
void normalize_float32x4_t(const float src[gf_size], float dst[gf_size])
{
#pragma HLS ARRAY_PARTITION dim=1 factor=4 type=cyclic variable=src
#pragma HLS ARRAY_PARTITION dim=1 factor=4 type=cyclic variable=dst
#pragma HLS INLINE off

#pragma HLS ALLOCATION operation instances=fadd limit=4
#pragma HLS ALLOCATION operation instances=fmul limit=4

    float loc[16];
#if 0
    for (int i = 0; i < gf_size + 4; i += 4) {
#pragma HLS PIPELINE
    	loc[i/4] = ((src[i + 0] + src[i + 1])) + ((src[i + 2] + src[i + 3]));
    }
#else
    loc[ 0]  = (src[ 0] + src[ 1]) + (src[ 2] + src[ 3]);
    loc[ 1]  = (src[ 4] + src[ 5]) + (src[ 6] + src[ 7]);
    loc[ 2]  = (src[ 8] + src[ 9]) + (src[10] + src[11]);
    loc[ 3]  = (src[12] + src[13]) + (src[14] + src[15]);
    loc[ 4]  = (src[16] + src[17]) + (src[18] + src[19]);
    loc[ 5]  = (src[20] + src[21]) + (src[22] + src[23]);
    loc[ 6]  = (src[24] + src[25]) + (src[26] + src[27]);
    loc[ 7]  = (src[28] + src[29]) + (src[30] + src[31]);
    loc[ 8]  = (src[32] + src[33]) + (src[34] + src[35]);
    loc[ 9]  = (src[36] + src[37]) + (src[38] + src[39]);
    loc[10]  = (src[40] + src[41]) + (src[42] + src[43]);
    loc[11]  = (src[44] + src[45]) + (src[46] + src[47]);
    loc[12]  = (src[48] + src[49]) + (src[50] + src[51]);
    loc[13]  = (src[52] + src[53]) + (src[54] + src[55]);
    loc[14]  = (src[56] + src[57]) + (src[58] + src[59]);
    loc[15]  = (src[60] + src[61]) + (src[62] + src[63]);
#endif

    float p0 = (loc[ 0] + loc[ 1]) + (loc[ 2] + loc[ 3]);
    float p1 = (loc[ 4] + loc[ 5]) + (loc[ 6] + loc[ 7]);
    float p2 = (loc[ 8] + loc[ 9]) + (loc[10] + loc[11]);
    float p3 = (loc[12] + loc[13]) + (loc[14] + loc[15]);

    const float sum    = (p0 + p1) + (p2 + p3);
    const float factor = 1.f / sum;

    for (int i = 0; i < gf_size; i++) {
#pragma HLS PIPELINE
#pragma HLS UNROLL factor=4
        dst[i] = src[i] * factor;
    }
}
//
//
//
//////////////////////////////////////////////////////////////////////
//
//
//
void normalize_float32x8_t(const float src[gf_size], float dst[gf_size])
{
#pragma HLS ARRAY_PARTITION dim=1 factor=8 type=cyclic variable=src
#pragma HLS ARRAY_PARTITION dim=1 factor=8 type=cyclic variable=dst
#pragma HLS INLINE off

    float loc[8];

#pragma HLS ALLOCATION operation instances=fadd limit=8
#pragma HLS ALLOCATION operation instances=fmul limit=8

#if 0    
    for (int i = 0; i < gf_size; i += 8) {
#pragma HLS PIPELINE
    	loc[i/8] = p((src[i+0] + src[i+1]) + (src[i+2] + src[i+3])) + ((src[i+4] + src[i+5]) + (src[i+6] + src[i+7]));
    }
#else
    loc[0] = ((src[ 0] + src[ 1]) + (src[ 2] + src[ 3])) + ((src[ 4] + src[ 5]) + (src[ 6] + src[ 7]));
    loc[1] = ((src[ 8] + src[ 9]) + (src[10] + src[11])) + ((src[12] + src[13]) + (src[14] + src[15]));
    loc[2] = ((src[16] + src[17]) + (src[18] + src[19])) + ((src[20] + src[21]) + (src[22] + src[23]));
    loc[3] = ((src[24] + src[25]) + (src[26] + src[27])) + ((src[28] + src[29]) + (src[30] + src[31]));
    loc[4] = ((src[32] + src[33]) + (src[34] + src[35])) + ((src[36] + src[37]) + (src[38] + src[39]));
    loc[5] = ((src[40] + src[41]) + (src[42] + src[43])) + ((src[44] + src[45]) + (src[46] + src[47]));
    loc[6] = ((src[48] + src[49]) + (src[50] + src[51])) + ((src[52] + src[53]) + (src[54] + src[55]));
    loc[7] = ((src[56] + src[57]) + (src[58] + src[59])) + ((src[60] + src[61]) + (src[62] + src[63]));
#endif

    const float sum    = ((loc[0] + loc[1]) + (loc[2] + loc[3])) + ((loc[4] + loc[5]) + (loc[6] + loc[7]));
    const float factor = 1.f / sum;

    for (int i = 0; i < gf_size; i++) {
#pragma HLS PIPELINE
#pragma HLS UNROLL factor=8
        dst[i] = src[i] * factor;
    }
}
//
//
//
//////////////////////////////////////////////////////////////////////
//
//
//
void normalize_float32x16_t(const float src[gf_size], float dst[gf_size])
{
#pragma HLS ARRAY_PARTITION dim=1 factor=16 type=cyclic variable=src
#pragma HLS ARRAY_PARTITION dim=1 factor=16 type=cyclic variable=dst
#pragma HLS INLINE off

    float loc[4];

#pragma HLS ALLOCATION operation instances=fadd limit=16
#pragma HLS ALLOCATION operation instances=fmul limit=16

    // Traitement de 16 données par ligne
    loc[0] = ((src[ 0] + src[ 1]) + (src[ 2] + src[ 3])) +
             ((src[ 4] + src[ 5]) + (src[ 6] + src[ 7])) +
             ((src[ 8] + src[ 9]) + (src[10] + src[11])) +
             ((src[12] + src[13]) + (src[14] + src[15]));

    loc[1] = ((src[16] + src[17]) + (src[18] + src[19])) +
             ((src[20] + src[21]) + (src[22] + src[23])) +
             ((src[24] + src[25]) + (src[26] + src[27])) +
             ((src[28] + src[29]) + (src[30] + src[31]));

    loc[2] = ((src[32] + src[33]) + (src[34] + src[35])) +
             ((src[36] + src[37]) + (src[38] + src[39])) +
             ((src[40] + src[41]) + (src[42] + src[43])) +
             ((src[44] + src[45]) + (src[46] + src[47]));

    loc[3] = ((src[48] + src[49]) + (src[50] + src[51])) +
             ((src[52] + src[53]) + (src[54] + src[55])) +
             ((src[56] + src[57]) + (src[58] + src[59])) +
             ((src[60] + src[61]) + (src[62] + src[63]));

    const float sum    = loc[0] + loc[1] + loc[2] + loc[3];
    const float factor = 1.f / sum;

    for (int i = 0; i < gf_size; i++) {
#pragma HLS PIPELINE
#pragma HLS UNROLL factor=16
        dst[i] = src[i] * factor;
    }
}
//
//
//
//////////////////////////////////////////////////////////////////////
//
//
//
