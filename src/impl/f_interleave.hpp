#pragma once
//
//
//
//////////////////////////////////////////////////////////////////////
//
//
//
#include "types.hpp"
//
//
//
//////////////////////////////////////////////////////////////////////
//
extern t_ram<14,   4> hls_interleaver_gf4  (const t_ram<14,   4> src, const ap_uint<2> symbol);
extern t_ram<15,   8> hls_interleaver_gf8  (const t_ram<15,   8> src, const ap_uint<3> symbol);
extern t_ram<16,  16> hls_interleaver_gf16 (const t_ram<16,  16> src, const ap_uint<4> symbol);
extern t_ram<17,  32> hls_interleaver_gf32 (const t_ram<17,  32> src, const ap_uint<5> symbol);
extern t_ram<18,  64> hls_interleaver_gf64 (const t_ram<18,  64> src, const ap_uint<6> symbol);
extern t_ram<19, 128> hls_interleaver_gf128(const t_ram<19, 128> src, const ap_uint<7> symbol);
extern t_ram<20, 256> hls_interleaver_gf256(const t_ram<20, 256> src, const ap_uint<8> symbol);
//
//////////////////////////////////////////////////////////////////////
//
//
//
