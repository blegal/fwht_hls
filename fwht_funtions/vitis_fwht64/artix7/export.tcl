############################################################
## This file is generated automatically by Vitis HLS.
## Please DO NOT edit it.
## Copyright 1986-2022 Xilinx, Inc. All Rights Reserved.
## Copyright 2022-2023 Advanced Micro Devices, Inc. All Rights Reserved.
############################################################
open_project vitis_fwht64
set_top lwht64
add_files src/fwht64.cpp
open_solution "artix7" -flow_target vivado
set_part {xc7a200t-fbg676-2}
create_clock -period 10 -name default
config_export -flow impl -format ip_catalog -rtl verilog -vivado_clock 10
source "./vitis_fwht64/artix7/directives.tcl"
export_design -flow impl -rtl verilog -format ip_catalog
