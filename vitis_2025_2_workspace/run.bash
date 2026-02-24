#!/bin/bash

COMPONENTS=("hls_argmax3_gf4" "hls_argmax_gf256" "hls_decoder_v2" "hls_fwht_gf4" "hls_interleave_12b_gf256" "hls_interleave_gf128" "hls_interleave_gf64" "hls_mul_gf256" "hls_norm_gf64" "hls_argmax3_gf128" "hls_argmax3_gf64" "hls_argmax_gf32" "hls_fwht_gf128" "hls_fwht_gf64" "hls_interleave_12b_gf32" "hls_interleave_gf16" "hls_interleave_gf8" "hls_mul_gf32" "hls_argmax3_gf16" "hls_argmax3_gf8" "hls_argmax_gf4" "hls_fwht_gf16" "hls_fwht_gf8" "hls_interleave_12b_gf4" "hls_interleave_gf256" "hls_mul_12b_gf4" "hls_mul_gf4" "hls_argmax3_gf256" "hls_argmax_gf128" "hls_argmax_gf64" "hls_fwht_gf256" "hls_interleave_12b_gf128" "hls_interleave_12b_gf64" "hls_interleave_gf32" "hls_mul_gf128" "hls_mul_gf64" "hls_argmax3_gf32" "hls_argmax_gf16" "hls_argmax_gf8" "hls_fwht_gf32" "hls_interleave_12b_gf16" "hls_interleave_12b_gf8" " hls_interleave_gf4" "hls_mul_gf16" "hls_mul_gf8")

for c in "${COMPONENTS[@]}"; do
	echo $c
	v++ -c --mode hls --config ./$c/hls_config.cfg --work_dir ./$c/solution
	vitis-run --mode hls --impl --config ./$c/hls_config.cfg --work_dir ./$c/solution
	#vitis component build --component $c --step synth > log_$c.txt 2>&1 &
done

wait
echo "All HLS synthesis finished"
