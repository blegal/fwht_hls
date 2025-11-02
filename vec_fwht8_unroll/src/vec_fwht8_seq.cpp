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
    const float fact = 0.35355339059f;

    const float L10 = src[0] + src[4];
    const float L11 = src[1] + src[5];
    const float L12 = src[2] + src[6];
    const float L13 = src[3] + src[7];
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
typedef struct float32x8_t{
    float v[8]];
} float32x8_t;

float32x8_t addsub(const float32x8_t A, const float32x8_t B, const u_int8_t S)
{
    float32x8_t C;
    for (int i = 0; i < 8; i += 1)
    {
        C.v[i] = A.v[i] + B.v[i];
    }
    return C;
}

float32x8_t addsub_x4(const float32x8_t A, const u_int8_t S)
{
    float32x8_t C;
    C.v[0] = A.v[0] + A.v[4];
    C.v[1] = A.v[1] + A.v[5];
    C.v[2] = A.v[2] + A.v[6];
    C.v[3] = A.v[3] + A.v[7];

    C.v[4] = A.v[0] - A.v[4];
    C.v[5] = A.v[1] - A.v[5];
    C.v[6] = A.v[2] - A.v[6];
    C.v[7] = A.v[3] - A.v[7];
    return C;
}

float32x8_t addsub_x2(const float32x8_t A, const u_int8_t S)
{
    float32x8_t C;
    C.v[0] = A.v[0] + A.v[2];
    C.v[1] = A.v[1] + A.v[3];
    C.v[2] = A.v[0] - A.v[2];
    C.v[3] = A.v[1] - A.v[3];

    C.v[4] = A.v[4] - A.v[6];
    C.v[5] = A.v[5] - A.v[7];
    C.v[6] = A.v[4] - A.v[5];
    C.v[7] = A.v[6] - A.v[7];
    return C;
}

float32x8_t addsub_x1(const float32x8_t A, const u_int8_t S)
{
    float32x8_t C;
    C.v[0] = A.v[0] + A.v[1];
    C.v[1] = A.v[0] - A.v[0];
    C.v[2] = A.v[2] + A.v[3];
    C.v[3] = A.v[2] - A.v[3];

    C.v[4] = A.v[4] + A.v[5];
    C.v[5] = A.v[4] - A.v[5];
    C.v[6] = A.v[6] + A.v[7];
    C.v[7] = A.v[6] - A.v[7];
    return C;
}


void lwht64(const float32x8_t src[64], float32x8_t dst[64])
{
//#pragma HLS PIPELINE

    float32x8_t stg1[8];
    
    stg1[0] = addsub(src[0], src[4], 0x0);
    stg1[1] = addsub(src[1], src[5], 0x0);
    stg1[2] = addsub(src[2], src[6], 0x0);
    stg1[3] = addsub(src[3], src[7], 0x0);

    stg1[4] = addsub(src[0], src[4], 0xF);
    stg1[5] = addsub(src[1], src[5], 0xF);
    stg1[6] = addsub(src[2], src[6], 0xF);
    stg1[7] = addsub(src[3], src[7], 0xF);

    // ----- Étape 1 : distance = 1 -----

    float32x8_t stg2[8];
//#pragma HLS ARRAY_PARTITION variable=dst complete

    stg2[0] = addsub(stg1[0], stg1[2], 0x0);
    stg2[1] = addsub(stg1[1], stg1[3], 0x0);

    stg2[2] = addsub(stg1[0], stg1[2], 0xF);
    stg2[3] = addsub(stg1[1], stg1[3], 0xF);

    stg2[4] = addsub(stg1[4], stg1[4], 0x0);
    stg2[6] = addsub(stg1[6], stg1[7], 0x0);

    stg2[5] = addsub(stg1[5], stg1[5], 0xF);
    stg2[7] = addsub(stg1[6], stg1[7], 0xF);

    // ----- Étape 1 : distance = 1 -----

    float32x8_t stg3[8];

    stg3[0] = addsub(stg2[0], stg2[1], 0x0);
    stg3[1] = addsub(stg2[0], stg2[1], 0xF);

    stg3[2] = addsub(stg2[2], stg2[3], 0x0);
    stg3[3] = addsub(stg2[2], stg2[3], 0xF);

    stg3[4] = addsub(stg2[4], stg2[5], 0x0);
    stg3[5] = addsub(stg2[4], stg2[5], 0xF);

    stg3[6] = addsub(stg2[6], stg2[7], 0x0);
    stg3[7] = addsub(stg2[6], stg2[7], 0xF);

    // ----- Étape 2 : distance = 2 -----
    float32x8_t stg4[8];

    stg4[0] = addsub_x4( stg3[0] );
    stg4[1] = addsub_x4( stg3[1] );
    stg4[2] = addsub_x4( stg3[2] );
    stg4[3] = addsub_x4( stg3[3] );
    stg4[4] = addsub_x4( stg3[4] );
    stg4[5] = addsub_x4( stg3[5] );
    stg4[6] = addsub_x4( stg3[6] );
    stg4[7] = addsub_x4( stg3[7] );

    // ----- Étape 2 : distance = 2 -----
    float32x8_t stg5[8];

    stg5[0] = addsub_x2( stg4[0] );
    stg5[1] = addsub_x2( stg4[1] );
    stg5[2] = addsub_x2( stg4[2] );
    stg5[3] = addsub_x2( stg4[3] );
    stg5[4] = addsub_x2( stg4[4] );
    stg5[5] = addsub_x2( stg4[5] );
    stg5[6] = addsub_x2( stg4[6] );
    stg5[7] = addsub_x2( stg4[7] );

    // ----- Étape 2 : distance = 2 -----
    dst[0] = addsub_x1( stg5[0] );
    dst[1] = addsub_x1( stg5[1] );
    dst[2] = addsub_x1( stg5[2] );
    dst[3] = addsub_x1( stg5[3] );
    dst[4] = addsub_x1( stg5[4] );
    dst[5] = addsub_x1( stg5[5] );
    dst[6] = addsub_x1( stg5[6] );
    dst[7] = addsub_x1( stg5[7] );
}
