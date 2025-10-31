############################################################
## This file is generated automatically by Vitis HLS.
## Please DO NOT edit it.
## Copyright 1986-2022 Xilinx, Inc. All Rights Reserved.
## Copyright 2022-2023 Advanced Micro Devices, Inc. All Rights Reserved.
############################################################
open_project decoder_gf64
set_top the_decoder
add_files src/archi.hpp
add_files src/argmax_x86.hpp
add_files src/decoder.cpp
add_files src/dedicated_execute.hpp
add_files src/f_function_freq_in.hpp
add_files src/f_function_proba_in.hpp
add_files src/fix_xor_list.hpp
add_files src/fwht.hpp
add_files src/fwht_norm.hpp
add_files src/g_function_freq_in.hpp
add_files src/g_function_proba_in.hpp
add_files src/middle_node_pruned_rate_0.hpp
add_files src/middle_node_pruned_rate_1_after_f.hpp
add_files src/middle_node_pruned_rate_1_after_g.hpp
add_files src/middle_node_pruned_rep_after_f.hpp
add_files src/middle_node_pruned_rep_after_g.hpp
add_files src/normalize_c.hpp
open_solution "solution1" -flow_target vivado
set_part {xc7vx690tffg1761-2}
create_clock -period 10 -name default
#source "./decoder_gf64/solution1/directives.tcl"
csynth_design
