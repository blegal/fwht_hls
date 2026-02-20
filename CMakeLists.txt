cmake_minimum_required(VERSION 3.21)

set (CMAKE_EXPORT_COMPILE_COMMANDS ON)

set (CMAKE_CXX_STANDARD 17)
set (CMAKE_BUILD_TYPE Release)

set (CMAKE_CXX_STANDARD_REQUIRED ON)
set (CMAKE_INTERPROCEDURAL_OPTIMIZATION OFF)

project(NB_SC_DECODER_EXPLORER LANGUAGES CXX)

option (SANITIZE_DECODERS "Add sanitization values" ON)

if (SANITIZE_DECODERS)
	set (SANITIZE_CXXFLAGS "-fsanitize=address;-fsanitize=undefined;-fno-omit-frame-pointer;-ggdb")
	set (SANITIZE_LDFLAGS  "-fsanitize=address;-fsanitize=undefined;-fno-omit-frame-pointer;-ggdb")
endif ()

add_compile_options (-march=native -mtune=native -O3 -g0 ${SANITIZE_CXXFLAGS})
# add_compile_options(-g -O0 -march=native -mtune=native -Wall -Wextra ${SANITIZE_CXXFLAGS})#debug2
add_compile_options (-Wall -Wextra)
# to remove warnings from ap_int
add_compile_options (-Wno-unused-parameter -Wno-deprecated-copy -Wno-int-in-bool-context -Wno-type-limits -Wno-strict-aliasing -Wno-extra -Wno-unused-label -Wno-unknown-pragmas)
add_link_options (${SANITIZE_LDFLAGS})

#######################################################################################################################################

add_executable(hls_generator
		${CMAKE_CURRENT_SOURCE_DIR}/apps/hls_generator.cpp
)
target_include_directories (hls_generator PUBLIC ${CMAKE_SOURCE_DIR}/src ${CMAKE_SOURCE_DIR}/src/common)

#######################################################################################################################################

add_executable(hls_test
		src/catch2v3/catch_amalgamated.cpp
		src/impl/f_argmax.cpp
		src/impl/f_argmax2.cpp
		src/impl/f_datapath.cpp
		src/impl/f_decision.cpp
		src/impl/f_extend.cpp
		src/impl/f_fwht.cpp
		src/impl/f_interleave.cpp
		src/impl/f_mult.cpp
		src/impl/f_norm.cpp
		src/impl/f_truncate.cpp
		src/impl/f_xor_processor.cpp
		src/hls_decoder.cpp
		src/gen_decoder.cpp
		src/test.cpp
	)
target_include_directories (hls_test PUBLIC ${CMAKE_SOURCE_DIR}/src ${CMAKE_SOURCE_DIR}/src/common)

#######################################################################################################################################
