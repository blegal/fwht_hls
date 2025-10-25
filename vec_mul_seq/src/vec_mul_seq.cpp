#include <cstdio>
#include <cstdlib>
#include <cmath>

#define gf_size 64

void vec_mul(float dst[gf_size], const float src_1[gf_size], const float src_2[gf_size])
{
    for (int i = 0; i < gf_size; i++)
    {
#pragma HLS pipeline II=1
        dst[i] = src_1[i] * src_2[i];
    }
    return max_index;
}
