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

uint8_t vec_argmax_unroll(const float value[gf_size])
{
    tuple s1[gf_size/ 2];
    tuple s2[gf_size/ 4];
    tuple s3[gf_size/ 8];
    tuple s4[gf_size/16];
    tuple s5[gf_size/32];
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
