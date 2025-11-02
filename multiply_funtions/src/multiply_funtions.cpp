#include <cstdio>
#include <cstdlib>
#include <cmath>
#include <ap_int.h>
#include <cstdint>

#define gf_size      64
#define log2_gf_size 64

//
//
//
//////////////////////////////////////////////////////////////////////
//
//
//
void multiply_float32_t(const float src_1[gf_size], const float src_2[gf_size], float dst[gf_size])
{
    for (uint8_t i = 0; i < gf_size; i++)
    {
#pragma HLS PIPELINE II=1
    	dst[i] =  src_1[i] * src_2[i];
    }
}
//
//
//
//////////////////////////////////////////////////////////////////////
//
//
//
void multiply_float32x2_t(const float src_1[gf_size], const float src_2[gf_size], float dst[gf_size])
{
#pragma HLS ARRAY_PARTITION dim=1 factor=2 type=cyclic variable=src_1
#pragma HLS ARRAY_PARTITION dim=1 factor=2 type=cyclic variable=src_2
#pragma HLS ARRAY_PARTITION dim=1 factor=2 type=cyclic variable=dst
    for (uint8_t i = 0; i < gf_size; i++)
    {
#pragma HLS PIPELINE II=1
#pragma HLS UNROLL factor=2
    	dst[i] =  src_1[i] * src_2[i];
    }
}
//
//
//
//////////////////////////////////////////////////////////////////////
//
//
//
void multiply_float32x4_t(const float src_1[gf_size], const float src_2[gf_size], float dst[gf_size])
{
#pragma HLS ARRAY_PARTITION dim=1 factor=4 type=cyclic variable=src_1
#pragma HLS ARRAY_PARTITION dim=1 factor=4 type=cyclic variable=src_2
#pragma HLS ARRAY_PARTITION dim=1 factor=4 type=cyclic variable=dst
    for (uint8_t i = 0; i < gf_size; i++)
    {
#pragma HLS PIPELINE II=1
#pragma HLS UNROLL factor=4
    	dst[i] =  src_1[i] * src_2[i];
    }
}
//
//
//
//////////////////////////////////////////////////////////////////////
//
//
//
void multiply_float32x8_t(const float src_1[gf_size], const float src_2[gf_size], float dst[gf_size])
{
#pragma HLS ARRAY_PARTITION dim=1 factor=8 type=cyclic variable=src_1
#pragma HLS ARRAY_PARTITION dim=1 factor=8 type=cyclic variable=src_2
#pragma HLS ARRAY_PARTITION dim=1 factor=8 type=cyclic variable=dst
    for (uint8_t i = 0; i < gf_size; i++)
    {
#pragma HLS PIPELINE II=1
#pragma HLS UNROLL factor=8
    	dst[i] =  src_1[i] * src_2[i];
    }
}
//
//
//
//////////////////////////////////////////////////////////////////////
//
//
//
void multiply_float32x16_t(const float src_1[gf_size], const float src_2[gf_size], float dst[gf_size])
{
#pragma HLS ARRAY_PARTITION dim=1 factor=16 type=cyclic variable=src_1
#pragma HLS ARRAY_PARTITION dim=1 factor=16 type=cyclic variable=src_2
#pragma HLS ARRAY_PARTITION dim=1 factor=16 type=cyclic variable=dst
    for (uint8_t i = 0; i < gf_size; i++)
    {
#pragma HLS PIPELINE II=1
#pragma HLS UNROLL factor=16
    	dst[i] =  src_1[i] * src_2[i];
    }
}
//
//
//
//////////////////////////////////////////////////////////////////////
//
//
//
void multiply_float32x32_t(const float src_1[gf_size], const float src_2[gf_size], float dst[gf_size])
{
#pragma HLS ARRAY_PARTITION dim=1 factor=32 type=cyclic variable=src_1
#pragma HLS ARRAY_PARTITION dim=1 factor=32 type=cyclic variable=src_2
#pragma HLS ARRAY_PARTITION dim=1 factor=32 type=cyclic variable=dst
    for (uint8_t i = 0; i < gf_size; i++)
    {
#pragma HLS PIPELINE II=1
#pragma HLS UNROLL factor=32
    	dst[i] =  src_1[i] * src_2[i];
    }
}
//
//
//
//////////////////////////////////////////////////////////////////////
//
//
//
void multiply_float32x64_t(const float src_1[gf_size], const float src_2[gf_size], float dst[gf_size])
{
#pragma HLS ARRAY_PARTITION dim=1 factor=64 type=cyclic variable=src_1
#pragma HLS ARRAY_PARTITION dim=1 factor=64 type=cyclic variable=src_2
#pragma HLS ARRAY_PARTITION dim=1 factor=64 type=cyclic variable=dst
    for (uint8_t i = 0; i < gf_size; i++)
    {
#pragma HLS PIPELINE II=1
#pragma HLS UNROLL factor=64
    	dst[i] =  src_1[i] * src_2[i];
    }
}
//
//
//
//////////////////////////////////////////////////////////////////////
//
//
//
