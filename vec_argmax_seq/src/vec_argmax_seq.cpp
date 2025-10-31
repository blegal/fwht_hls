#include <cstdio>
#include <cstdlib>
#include <cmath>

#define gf_size 64

int argmax(const float value[gf_size])
{
    int    max_index = 0;
    float  max_value = value[0];

    for (int i = 1; i < gf_size; i++)
    {
        if (value[i] > max_value)
        {
            max_value = value[i];
            max_index = i;
        }
    }
    return max_index;
}

