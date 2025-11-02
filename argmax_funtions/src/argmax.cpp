#include <cstdio>
#include <cstdlib>
#include <cmath>
#include <ap_int.h>
#include <cstdint>

#define gf_size      64
#define log2_gf_size 64


typedef struct tuple{
    float value;
    int   index; // range [0...63]
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
int argmax_float32_t(const float value[gf_size])
{
    int    max_index = 0;
    float  max_value = value[0];

    for (int i = 1; i < gf_size; i++)
    {
#pragma HLS PIPELINE II=1
        if (value[i] > max_value)
        {
            max_value = value[i];
            max_index = i;
        }
    }
    return max_index;
}
//
//
//
//////////////////////////////////////////////////////////////////////
//
//
//
int argmax_float32x2_t(const float value[gf_size])
{
#pragma HLS ARRAY_PARTITION dim=1 factor=2 type=cyclic variable=value

	tuple local[2] = { {0.f, 0},{0.f, 0} };
#pragma HLS ARRAY_PARTITION dim=1 type=complete variable=local

    for (int i = 0; i < gf_size; i += 2)
    {
#pragma HLS PIPELINE
        for (int k = 0; k < 2; k += 1)
        {
#pragma HLS UNROLL
        	const tuple A = {value[i+k], i+k};
            local[k] = f_max(local[k], A);
        }
    }

    const tuple r1 = f_max(local[0], local[1]);

    return r1.index;
}
//
//
//
//////////////////////////////////////////////////////////////////////
//
//
//
int argmax_float32x4_t(const float value[gf_size])
{
#pragma HLS ARRAY_PARTITION dim=1 factor=4 type=cyclic variable=value

	tuple local[4] = { {0.f, 0},{0.f, 0}, {0.f, 0}, {0.f, 0}};
#pragma HLS ARRAY_PARTITION dim=1 type=complete variable=local

    for (int i = 0; i < gf_size; i += 4)
    {
#pragma HLS PIPELINE
        for (int k = 0; k < 4; k += 1)
        {
#pragma HLS UNROLL
        	const tuple A = {value[i+k], i+k};
            local[k] = f_max(local[k], A);
        }
    }

    const tuple r1 = f_max(local[0], local[1]);
	const tuple r2 = f_max(local[2], local[3]);
	const tuple r3 = f_max(r1, r2);

    return r3.index;
}
//
//
//
//////////////////////////////////////////////////////////////////////
//
//
//
int argmax_float32x8_t(const float value[gf_size])
{
#pragma HLS ARRAY_PARTITION dim=1 factor=8 type=cyclic variable=value

	tuple local[8] = { {0.f, 0},{0.f, 0}, {0.f, 0}, {0.f, 0}, {0.f, 0},{0.f, 0}, {0.f, 0}, {0.f, 0}};
#pragma HLS ARRAY_PARTITION dim=1 type=complete variable=local

    for (int i = 0; i < gf_size; i += 8)
    {
#pragma HLS PIPELINE
        for (int k = 0; k < 8; k += 1)
        {
#pragma HLS UNROLL
        	const tuple A = {value[i+k], i+k};
            local[k] = f_max(local[k], A);
        }
    }

    const tuple r1 = f_max(local[0], local[1]);
	const tuple r2 = f_max(local[2], local[3]);
    const tuple r3 = f_max(local[4], local[5]);
	const tuple r4 = f_max(local[6], local[7]);

    const tuple r5 = f_max(r1, r2);
	const tuple r6 = f_max(r3, r4);

	const tuple r7 = f_max(r5, r6);

    return r7.index;
}
//
//
//
//////////////////////////////////////////////////////////////////////
//
//
//

//
//
//
//////////////////////////////////////////////////////////////////////
//
//
//
uint8_t argmax_float32x64_t(const float value[gf_size])
{
#pragma HLS ARRAY_PARTITION dim=1 type=complete variable=value
    tuple s1[gf_size/ 2];
#pragma HLS ARRAY_PARTITION dim=1 type=complete variable=s1
    tuple s2[gf_size/ 4];
#pragma HLS ARRAY_PARTITION dim=1 type=complete variable=s2
    tuple s3[gf_size/ 8];
#pragma HLS ARRAY_PARTITION dim=1 type=complete variable=s3
    tuple s4[gf_size/16];
#pragma HLS ARRAY_PARTITION dim=1 type=complete variable=s4
    tuple s5[gf_size/32];
#pragma HLS ARRAY_PARTITION dim=1 type=complete variable=s5
    tuple s6;


    //
    // stage 0
    //
    for (int i = 0; i < gf_size; i += 2) // 64
    {
#pragma HLS UNROLL
        const tuple A = {value[  i], i  };
        const tuple B = {value[i+1], i+1};
        s1[i >> 1] = f_max(A, B);
    }
    //
    // stage 1
    //
    for (int i = 0; i < gf_size/2; i += 2)  // 32
    {
#pragma HLS UNROLL
        s2[i >> 1] = f_max(s1[i], s1[i+1]);
    }
    for (int i = 0; i < gf_size/4; i += 2)  // 16
    {
#pragma HLS UNROLL
        s3[i >> 1] = f_max(s2[i], s2[i+1]);
    }
    for (int i = 0; i < gf_size/8; i += 2)  // 8
    {
#pragma HLS UNROLL
        s4[i >> 1] = f_max(s3[i], s3[i+1]);
    }
    for (int i = 0; i < gf_size/16; i += 2) // 4
    {
#pragma HLS UNROLL
        s5[i >> 1] = f_max(s4[i], s4[i+1]);
    }
    s6 = f_max(s5[0], s5[1]);

    return s6.index;
}
