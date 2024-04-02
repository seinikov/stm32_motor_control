#ifndef __ALGORITHM_FILTERING_H__
#define __ALGORITHM_FILTERING_H__

#include "main.h"
#include "arm_math.h"
#include "data_ring_buffer.h"

#define LOW_PASS_FILTERING_ALPHA 0.05f //1~0

typedef struct {
    float current_val;
    float last_val;
    float alpha;
} FOLPF_HandleTypeDef;

void UINT16_DOUBLE_AverageFiltering(UINT16_DOUBLE_DATA_RING_BUFFER *use_ringbuf,uint16_t *res1,uint16_t *res2);

void UINT16_SINGLE_AverageFiltering(UINT16_SINGLE_DATA_RING_BUFFER *use_ringbuf,uint16_t *res);

void FLOAT_FirstOrderLowPassFiltering_DataInit(FOLPF_HandleTypeDef *folpf_obj,float32_t alpha_value);

void FLOAT_FirstOrderLowPassFiltering_Process(FOLPF_HandleTypeDef *folpf_obj);

#endif
