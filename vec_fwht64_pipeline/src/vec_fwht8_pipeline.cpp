#include <cstdio>
#include <cstdlib>
#include <cmath>
//
//
/////////////////////////////////////////////////////////////////////////////////////////////////////////
//
//
inline float vec_fwht8(float dst[8], const float src[8])
{
#pragma HLS pipeline II=1
    const float fact = 0.35355339059f;

    const float L10 = src[0] + src[4]);
    const float L11 = src[1] + src[5]);
    const float L12 = src[2] + src[6]);
    const float L13 = src[3] + src[7]);
    const float L14 = src[0] - src[4];
    const float L15 = src[1] - src[5];
    const float L16 = src[2] - src[6];
    const float L17 = src[3] - src[7];

    const float L20 = L10 + L12;
    const float L22 = L10 - L12;
    const float L21 = L11 + L13;
    const float L23 = L11 - L13;
    const float L24 = L14 + L16;
    const float L26 = L14 - L16;
    const float L25 = L15 + L17;
    const float L27 = L15 - L17;

    const float v0 = L20 + L21 * fact;
    const float v1 = L20 - L21 * fact;
    const float v2 = L22 + L23 * fact;
    const float v3 = L22 - L23 * fact;
    const float v4 = L24 + L25 * fact;
    const float v5 = L24 - L25 * fact;
    const float v6 = L26 + L27 * fact;
    const float v7 = L26 - L27 * fact;

    dst[0] = v0;
    dst[1] = v1;
    dst[2] = v2;
    dst[3] = v3;
    dst[4] = v4;
    dst[5] = v5;
    dst[6] = v6;
    dst[7] = v7;
}
//
//
/////////////////////////////////////////////////////////////////////////////////////////////////////////
//
//
