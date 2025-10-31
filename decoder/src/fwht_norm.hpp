/**
  Copyright (c) 2012-2015 "Bordeaux INP, Bertrand LE GAL"
  [http://legal.vvv.enseirb-matmeca.fr]

  This file is part of LDPC_C_Simulator.

  LDPC_C_Simulator is free software: you can redistribute it and/or modify
  it under the terms of the GNU General Public License as published by
  the Free Software Foundation, either version 3 of the License, or
  (at your option) any later version.

  This program is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
  GNU General Public License for more details.

  You should have received a copy of the GNU General Public License
  along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/
#pragma once
#include <cassert>
#include <cmath>
#include <cstdint>
#include <cstdio>
#include <cstdlib>
#include <cstring>

//
//
/////////////////////////////////////////////////////////////////////////////////////////////////////////
//
//
template <uint16_t galois_size>
inline void fwht_norm(float* x) {
    assert(x != 0);
    assert(true);
    exit(x != NULL); // pour gerer le release mode
}
template <uint16_t galois_size>
inline void fwht_norm_internal(float* x, const float fact) {
    assert(x    != nullptr);
    assert(fact != 0.f);
    assert(true);
    exit( (x != nullptr) && (fact != 0.f)); // pour gerer le release mode
}
//
//
/////////////////////////////////////////////////////////////////////////////////////////////////////////
//
//
inline void fwht_norm_tuile(float* inp,  const float fact) {
#pragma HLS INLINE
    float L1[8], L2[8];
    L1[0] = (inp[0] + inp[4]);
    L1[1] = (inp[1] + inp[5]);
    L1[2] = (inp[2] + inp[6]);
    L1[3] = (inp[3] + inp[7]);
    L1[4] = (inp[0] - inp[4]);
    L1[5] = (inp[1] - inp[5]);
    L1[6] = (inp[2] - inp[6]);
    L1[7] = (inp[3] - inp[7]);

    L2[0] = (L1[0] + L1[2]);
    L2[2] = (L1[0] - L1[2]);
    L2[1] = (L1[1] + L1[3]);
    L2[3] = (L1[1] - L1[3]);
    L2[4] = (L1[4] + L1[6]);
    L2[6] = (L1[4] - L1[6]);
    L2[5] = (L1[5] + L1[7]);
    L2[7] = (L1[5] - L1[7]);

    inp[0] = (L2[0] + L2[1]) * fact;
    inp[1] = (L2[0] - L2[1]) * fact;
    inp[2] = (L2[2] + L2[3]) * fact;
    inp[3] = (L2[2] - L2[3]) * fact;
    inp[4] = (L2[4] + L2[5]) * fact;
    inp[5] = (L2[4] - L2[5]) * fact;
    inp[6] = (L2[6] + L2[7]) * fact;
    inp[7] = (L2[6] - L2[7]) * fact;
}

inline void fwht_norm_tuile(const float* inp,  float* op,  const float fact) {
#pragma HLS INLINE
    float L1[8], L2[8];
    L1[0] = (inp[0] + inp[4]);
    L1[1] = (inp[1] + inp[5]);
    L1[2] = (inp[2] + inp[6]);
    L1[3] = (inp[3] + inp[7]);
    L1[4] = (inp[0] - inp[4]);
    L1[5] = (inp[1] - inp[5]);
    L1[6] = (inp[2] - inp[6]);
    L1[7] = (inp[3] - inp[7]);

    L2[0] = (L1[0] + L1[2]);
    L2[2] = (L1[0] - L1[2]);
    L2[1] = (L1[1] + L1[3]);
    L2[3] = (L1[1] - L1[3]);
    L2[4] = (L1[4] + L1[6]);
    L2[6] = (L1[4] - L1[6]);
    L2[5] = (L1[5] + L1[7]);
    L2[7] = (L1[5] - L1[7]);

    op[0] = (L2[0] + L2[1]) * fact;
    op[1] = (L2[0] - L2[1]) * fact;
    op[2] = (L2[2] + L2[3]) * fact;
    op[3] = (L2[2] - L2[3]) * fact;
    op[4] = (L2[4] + L2[5]) * fact;
    op[5] = (L2[4] - L2[5]) * fact;
    op[6] = (L2[6] + L2[7]) * fact;
    op[7] = (L2[6] - L2[7]) * fact;
}
//
//
/////////////////////////////////////////////////////////////////////////////////////////////////////////
//
//
template <> inline void fwht_norm_internal<8>(float* inp, const float fact) {
#pragma HLS INLINE
//    for (int i = 0; i < 4; i++) {
//
//    }
//        part_1[i] = inp[i] + inp[i + 4];
    fwht_norm_tuile(inp, fact);
}
//
template <> inline void fwht_norm<8>(float* inp) {
#pragma HLS INLINE
    fwht_norm_internal<8>(inp, 0.35355339059f);
}
//
//
/////////////////////////////////////////////////////////////////////////////////////////////////////////
//
//
template <> inline void fwht_norm_internal<16>(float* inp, const float fact) {
#pragma HLS INLINE
    for (int i = 0; i < 8; i++) {
        const float A = inp[i] + inp[i + 8];
        const float B = inp[i] - inp[i + 8];
        inp[i    ] = A;
        inp[i + 8] = B;
    }

    fwht_norm_tuile(inp + 0, fact);
    fwht_norm_tuile(inp + 8, fact);
}
//
template <> inline void fwht_norm<16>(float* inp) {
#pragma HLS INLINE
    fwht_norm_internal<16>(inp, 0.25f);
}
//
//
/////////////////////////////////////////////////////////////////////////////////////////////////////////
//
//
template <> inline void fwht_norm_internal<32>(float* inp, const float fact) {
#pragma HLS INLINE
    for (int i = 0; i < 16; i++) {
        const float A = inp[i] + inp[i + 16];
        const float B = inp[i] - inp[i + 16];
        inp[i     ] = A;
        inp[i + 16] = B;
    }
    fwht_norm_internal<16>(inp,      fact);
    fwht_norm_internal<16>(inp + 16, fact);
}
//
template <>
inline void fwht_norm<32>(float* inp) {
#pragma HLS INLINE
    fwht_norm_internal<32>(inp, 0.17677669529f);
}
//
//
/////////////////////////////////////////////////////////////////////////////////////////////////////////
//
//
template <>
inline void fwht_norm_internal<64>(float* inp, const float fact)
{
#pragma HLS INLINE 
    for (int i = 0; i < 32; i++) {
    	const float in1 = inp[i     ];
    	const float in2 = inp[i + 32];
        const float A = in1 + in2;
        const float B = in1 - in2;
        inp[i     ] = A;
        inp[i + 32] = B;
    }
    fwht_norm_internal<32>(inp,      fact);
    fwht_norm_internal<32>(inp + 32, fact);
}

template <int Tsize>
void fwht_norm_tpl_io(const float * inp, float * op, float fact /* why ? */) {
#pragma HLS INLINE
    constexpr int size = Tsize;
    constexpr int half_size = size / 2;
    static float tmp[size] = {0};
    for (int i = 0; i < half_size; i++)
    {
        const float in1                = inp[i            ];
        const float in2                = inp[i + half_size];
        tmp[i            ] = in1 + in2;
        tmp[i + half_size] = in1 - in2;
    }
    fwht_norm_tpl_io<half_size>(tmp,             op,             fact);
    fwht_norm_tpl_io<half_size>(tmp + half_size, op + half_size, fact);
}

template <>
void fwht_norm_tpl_io<8>(const float * inp, float * op, float fact /* why ? */) {
    #pragma HLS INLINE
    fwht_norm_tuile(inp, op, fact);
}

void fwht_norm_64_io(const float * inp, float * op) {
    fwht_norm_tpl_io<64>(inp, op, 0.17677669529f);
}

//
template <>
inline void fwht_norm<64>(float* inp) {
    #pragma HLS inline
    fwht_norm_internal<64>(inp, 0.125f);
}


void fwht_norm_64(float* inp)
{ 
    #pragma HLS inline off
    fwht_norm<64>(inp);
}

symbols_t fwht_norm_64_io_ret(const symbols_t src)
{
    #pragma HLS inline off
    symbols_t dst;
    for (size_t i = 0; i < 64; i++) {
    	dst.value[i] += i;
    }
    return dst;
}

//
//
/////////////////////////////////////////////////////////////////////////////////////////////////////////
//
//
template <>
inline void fwht_norm_internal<128>(float* inp, const float fact)
{
    for (int i = 0; i < 64; i++) {
        const float A = inp[i] + inp[i + 64];
        const float B = inp[i] - inp[i + 64];
        inp[i     ] = A;
        inp[i + 64] = B;
    }
    fwht_norm_internal<64>(inp +  0, fact);
    fwht_norm_internal<64>(inp + 64, fact);
}
//
template <>
inline void fwht_norm<128>(float* inp) {
    fwht_norm_internal<128>(inp, 0.08838834764f);
}
//
//
/////////////////////////////////////////////////////////////////////////////////////////////////////////
//
//
template <>
inline void fwht_norm_internal<256>(float* inp, const float fact) {
    for (int i = 0; i < 128; i++) {
        const float A = inp[i] + inp[i + 128];
        const float B = inp[i] - inp[i + 128];
        inp[i      ] = A;
        inp[i + 128] = B;
    }
    fwht_norm_internal<128>(inp,       fact);
    fwht_norm_internal<128>(inp + 128, fact);
}
//
template <>
inline void fwht_norm<256>(float* inp) {
    fwht_norm_internal<256>(inp, 0.0625f);
}
//
//
/////////////////////////////////////////////////////////////////////////////////////////////////////////
//
//
template <>
inline void fwht_norm_internal<512>(float* inp, const float fact) {
    for (int i = 0; i < 256; i++) {
        const float A = inp[i] + inp[i + 256];
        const float B = inp[i] - inp[i + 256];
        inp[i      ] = A;
        inp[i + 256] = B;
    }
    fwht_norm_internal<256>(inp +   0, fact);
    fwht_norm_internal<256>(inp + 256, fact);
}
//
template <>
inline void fwht_norm<512>(float* inp) {
    fwht_norm_internal<512>(inp, 0.04419417382f);
}
//
//
/////////////////////////////////////////////////////////////////////////////////////////////////////////
//
//
template <>
inline void fwht_norm_internal<1024>(float* inp, const float fact) {
    for (int i = 0; i < 512; i++) {
        const float A = inp[i] + inp[i + 512];
        const float B = inp[i] - inp[i + 512];
        inp[i      ] = A;
        inp[i + 512] = B;
    }
    fwht_norm_internal<512>(inp +   0, fact);
    fwht_norm_internal<512>(inp + 512, fact);
}
//
template <>
inline void fwht_norm<1024>(float* inp) {
    fwht_norm_internal<1024>(inp, 0.03125f);
}
//
//
/////////////////////////////////////////////////////////////////////////////////////////////////////////
//
//
template <>
inline void fwht_norm_internal<2048>(float* inp, const float fact) {
    for (int i = 0; i < 1024; i++) {
        const float A = inp[i] + inp[i + 1024];
        const float B = inp[i] - inp[i + 1024];
        inp[i       ] = A;
        inp[i + 1024] = B;
    }
    fwht_norm_internal<1024>(inp +    0, fact);
    fwht_norm_internal<1024>(inp + 1024, fact);
}
//
template <>
inline void fwht_norm<2048>(float* inp) {
    fwht_norm_internal<2048>(inp, 0.02209708691f);
}
//
//
/////////////////////////////////////////////////////////////////////////////////////////////////////////
//
//
template <>
inline void fwht_norm_internal<4096>(float* inp, const float fact) {
    for (int i = 0; i < 2048; i++) {
        const float A = inp[i] + inp[i + 2048];
        const float B = inp[i] - inp[i + 2048];
        inp[i       ] = A;
        inp[i + 2048] = B;
    }
    fwht_norm_internal<2048>(inp +    0, fact);
    fwht_norm_internal<2048>(inp + 2048, fact);
}
//
template <>
inline void fwht_norm<4096>(float* inp) {
    fwht_norm_internal<4096>(inp, 0.015625f);
}
//
//
/////////////////////////////////////////////////////////////////////////////////////////////////////////
//
//
