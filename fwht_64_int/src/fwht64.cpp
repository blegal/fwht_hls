#include <cstdio>
#include <cstdlib>
#include <cmath>
#include <cstdint>
#include "ap_int.h"
//
//
/////////////////////////////////////////////////////////////////////////////////////////////////////////
//
//

#define dtype ap_int<32>

typedef struct dtypex8_t{
	dtype v[8];
} dtypex8_t;

float flip_sign_bit(const dtype x, const ap_uint<1> bit)
{
    // Si bit == 1, on inverse le bit de signe (bit 31)
    // Si bit == 0, on ne change rien
	const dtype y = -x;
    if( bit == 1 )
    	return y;
    else
    	return x;
}

dtypex8_t addsub_fx(const dtypex8_t A, const dtypex8_t B, const u_int8_t S, const int stage)
{
#pragma HLS INLINE off
#pragma HLS PIPELINE

	dtypex8_t Ta, Tb;
    if( stage == 0 ){
        Ta.v[0] = A.v[0]; Tb.v[0] = B.v[0];
        Ta.v[1] = A.v[1]; Tb.v[1] = B.v[1];
        Ta.v[2] = A.v[2]; Tb.v[2] = B.v[2];
        Ta.v[3] = A.v[3]; Tb.v[3] = B.v[3];
        Ta.v[4] = A.v[4]; Tb.v[4] = B.v[4];
        Ta.v[5] = A.v[5]; Tb.v[5] = B.v[5];
        Ta.v[6] = A.v[6]; Tb.v[6] = B.v[6];
        Ta.v[7] = A.v[7]; Tb.v[7] = B.v[7];
    }
    else if( stage == 1 )
    {
        Ta.v[0] = A.v[0]; Tb.v[0] = A.v[4];
        Ta.v[1] = A.v[1]; Tb.v[1] = A.v[5];
        Ta.v[2] = A.v[2]; Tb.v[2] = A.v[6];
        Ta.v[3] = A.v[3]; Tb.v[3] = A.v[7];
        Ta.v[4] = A.v[0]; Tb.v[4] = A.v[4];
        Ta.v[5] = A.v[1]; Tb.v[5] = A.v[5];
        Ta.v[6] = A.v[2]; Tb.v[6] = A.v[6];
        Ta.v[7] = A.v[3]; Tb.v[7] = A.v[7];
    }
    else if( stage == 1 )
    {
        Ta.v[0] = A.v[0]; Tb.v[0] = A.v[2];
        Ta.v[1] = A.v[1]; Tb.v[1] = A.v[3];
        Ta.v[2] = A.v[0]; Tb.v[2] = A.v[2];
        Ta.v[3] = A.v[1]; Tb.v[3] = A.v[3];
        Ta.v[4] = A.v[4]; Tb.v[4] = A.v[5];
        Ta.v[5] = A.v[6]; Tb.v[5] = A.v[7];
        Ta.v[6] = A.v[4]; Tb.v[6] = A.v[5];
        Ta.v[7] = A.v[6]; Tb.v[7] = A.v[7];
    }
    else
    {
        Ta.v[0] = A.v[0]; Tb.v[0] = A.v[1];
        Ta.v[1] = A.v[0]; Tb.v[1] = A.v[1];
        Ta.v[2] = A.v[2]; Tb.v[2] = A.v[3];
        Ta.v[3] = A.v[4]; Tb.v[3] = A.v[3];
        Ta.v[4] = A.v[4]; Tb.v[4] = A.v[5];
        Ta.v[5] = A.v[4]; Tb.v[5] = A.v[5];
        Ta.v[6] = A.v[6]; Tb.v[6] = A.v[7];
        Ta.v[7] = A.v[6]; Tb.v[7] = A.v[7];
    }

    for (int i = 0; i < 8; i += 1)
    {
#pragma HLS UNROLL
        Tb.v[i] = flip_sign_bit(Tb.v[i], (S >> i) & 0x01);
    }

    dtypex8_t C;
    for (int i = 0; i < 8; i += 1)
    {
#pragma HLS UNROLL
        C.v[i] = Ta.v[i] + Tb.v[i];
    }
    return C;
}

//#define IN_LUTs

void lwht64(const dtypex8_t src[64], dtypex8_t dst[64])
{
#ifdef IN_LUTs
	#pragma HLS ARRAY_PARTITION dim=8 factor=1 type=cyclic variable=src
	#pragma HLS ARRAY_PARTITION dim=8 factor=1 type=cyclic variable=dst
#endif

	dtypex8_t stg1[8];
#ifdef IN_LUTs
	#pragma HLS ARRAY_PARTITION dim=1 factor=8 type=cyclic variable=stg1
#endif

//#pragma HLS ALLOCATION function instances=addsub_fx limit=1


    stg1[0] = addsub_fx(src[0], src[4], 0x00, 0);
    stg1[1] = addsub_fx(src[1], src[5], 0x00, 0);
    stg1[2] = addsub_fx(src[2], src[6], 0x00, 0);
    stg1[3] = addsub_fx(src[3], src[7], 0x00, 0);
    stg1[4] = addsub_fx(src[0], src[4], 0xF0, 0);
    stg1[5] = addsub_fx(src[1], src[5], 0xF0, 0);
    stg1[6] = addsub_fx(src[2], src[6], 0xF0, 0);
    stg1[7] = addsub_fx(src[3], src[7], 0xF0, 0);

    // ----- Étape 1 : distance = 1 -----

    dtypex8_t stg2[8];
#ifdef IN_LUTs
	#pragma HLS ARRAY_PARTITION dim=1 factor=8 type=cyclic variable=stg2
#endif

    stg2[0] = addsub_fx(stg1[0], stg1[2], 0x00, 0 );
    stg2[1] = addsub_fx(stg1[1], stg1[3], 0x00, 0 );
    stg2[2] = addsub_fx(stg1[0], stg1[2], 0xF0, 0 );
    stg2[3] = addsub_fx(stg1[1], stg1[3], 0xF0, 0 );
    stg2[4] = addsub_fx(stg1[4], stg1[4], 0x00, 0 );
    stg2[6] = addsub_fx(stg1[6], stg1[7], 0x00, 0 );
    stg2[5] = addsub_fx(stg1[5], stg1[5], 0xF0, 0 );
    stg2[7] = addsub_fx(stg1[6], stg1[7], 0xF0, 0 );

    // ----- Étape 1 : distance = 1 -----

    dtypex8_t stg3[8];
#ifdef IN_LUTs
	#pragma HLS ARRAY_PARTITION dim=1 factor=8 type=cyclic variable=stg3
#endif

    stg3[0] = addsub_fx(stg2[0], stg2[1], 0x00, 0 );
    stg3[1] = addsub_fx(stg2[0], stg2[1], 0xF0, 0 );
    stg3[2] = addsub_fx(stg2[2], stg2[3], 0x00, 0 );
    stg3[3] = addsub_fx(stg2[2], stg2[3], 0xF0, 0 );
    stg3[4] = addsub_fx(stg2[4], stg2[5], 0x00, 0 );
    stg3[5] = addsub_fx(stg2[4], stg2[5], 0xF0, 0 );
    stg3[6] = addsub_fx(stg2[6], stg2[7], 0x00, 0 );
    stg3[7] = addsub_fx(stg2[6], stg2[7], 0xF0, 0 );

    // ----- Étape 2 : distance = 2 -----
    dtypex8_t stg4[8];
#ifdef IN_LUTs
	#pragma HLS ARRAY_PARTITION dim=1 factor=8 type=cyclic variable=stg4
#endif

    stg4[0] = addsub_fx( stg3[0], stg3[0], 0xF0, 1 );
    stg4[1] = addsub_fx( stg3[1], stg3[1], 0xF0, 1 );
    stg4[2] = addsub_fx( stg3[2], stg3[2], 0xF0, 1 );
    stg4[3] = addsub_fx( stg3[3], stg3[3], 0xF0, 1 );
    stg4[4] = addsub_fx( stg3[4], stg3[4], 0xF0, 1 );
    stg4[5] = addsub_fx( stg3[5], stg3[5], 0xF0, 1 );
    stg4[6] = addsub_fx( stg3[6], stg3[6], 0xF0, 1 );
    stg4[7] = addsub_fx( stg3[7], stg3[7], 0xF0, 1 );

    // ----- Étape 2 : distance = 2 -----
    dtypex8_t stg5[8];
#ifdef IN_LUTs
	#pragma HLS ARRAY_PARTITION dim=1 factor=8 type=cyclic variable=stg5
#endif

    stg5[0] = addsub_fx( stg4[0], stg4[0], 0xCC, 2 );
    stg5[1] = addsub_fx( stg4[1], stg4[1], 0xCC, 2 );
    stg5[2] = addsub_fx( stg4[2], stg4[2], 0xCC, 2 );
    stg5[3] = addsub_fx( stg4[3], stg4[3], 0xCC, 2 );
    stg5[4] = addsub_fx( stg4[4], stg4[4], 0xCC, 2 );
    stg5[5] = addsub_fx( stg4[5], stg4[5], 0xCC, 2 );
    stg5[6] = addsub_fx( stg4[6], stg4[6], 0xCC, 2 );
    stg5[7] = addsub_fx( stg4[7], stg4[7], 0xCC, 2 );

    // ----- Étape 2 : distance = 2 -----
    dst[0] = addsub_fx( stg5[0], stg5[0], 0xAA, 3 );
    dst[1] = addsub_fx( stg5[1], stg5[1], 0xAA, 3 );
    dst[2] = addsub_fx( stg5[2], stg5[2], 0xAA, 3 );
    dst[3] = addsub_fx( stg5[3], stg5[3], 0xAA, 3 );
    dst[4] = addsub_fx( stg5[4], stg5[4], 0xAA, 3 );
    dst[5] = addsub_fx( stg5[5], stg5[5], 0xAA, 3 );
    dst[6] = addsub_fx( stg5[6], stg5[6], 0xAA, 3 );
    dst[7] = addsub_fx( stg5[7], stg5[7], 0xAA, 3 );
}
