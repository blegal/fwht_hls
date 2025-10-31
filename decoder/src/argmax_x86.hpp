//!
//!     Copyright (c) 2020-2023, Bertrand LE GAL
//!     All rights reserved.
//!
//!     Redistribution and use in source and binary forms, with or without
//!     modification, are not permitted with written authorization.
//!
//!
#include <cstdint>
//
//
//
///////////////////////////////////////////////////////////////////////////////////////////////////////////
//
//
//

int argmax(const float * value)
{
#pragma HLS INLINE off
	const int gf_size = 64;
    int    max_index = 0;
    float  max_value = value[0];
    for (int i = 1; i < gf_size; i++) {
        if (value[i] > max_value) {
            max_value = value[i];
            max_index = i;
        }
    }
    return max_index;
}
//
//
//
///////////////////////////////////////////////////////////////////////////////////////////////////////////
//
//
//
