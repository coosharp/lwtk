#include "lw_filter.h"



static void bubble_sort(float * data, int size)
{
    for (int i = 0; i < size - 1; i++) {
        for (int j = 0; j < size - i - 1; j++) {
            if (data[j] > data[j + 1]) {
                float temp = data[j];
                data[j] = data[j + 1];
                data[j + 1] = temp;
            }
        }
    }
}

void lw_amplitude_limit_filter(float max_value, 
                               float min_value, 
                               float smooth_factor, 
                               float * src,
                               float * dst,
                               uint32_t len)
{
    uint32_t i = 0;
    float output_value = 0.0f;
    float input_value  = 0.0f;
    LW_FILTER_MEMSET(dst, 0, len * sizeof(float));

    for(i = 0; i < len; i++) {
        input_value = src[i];
        if(input_value > max_value) {
            output_value = max_value;
        }
        else if(input_value < min_value) {
            output_value = min_value;
        }
        else {
            output_value = input_value;
        }

        output_value = smooth_factor * output_value + (1.0f - smooth_factor) * output_value;

        dst[i] = output_value;
    }
}


void lw_median_filter(float * src, float * dst, uint32_t len)
{
    static uint32_t index = 0;
}