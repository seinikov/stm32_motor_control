#ifndef __ALGORITHM_FILTERING_H__
#define __ALGORITHM_FILTERING_H__

#include "main.h"
#include "data_ring_buffer.h"

#define LOW_PASS_FILTERING_COEFFCIENT 0.01f //1~0

typedef struct {
    float value_current;
    float value_last;
} FOLPF_DATATypeDef;

void UINT16_DOUBLE_AverageFiltering(UINT16_DOUBLE_DATA_RING_BUFFER *use_ringbuf,uint16_t *res1,uint16_t *res2);

void UINT16_SINGLE_AverageFiltering(UINT16_SINGLE_DATA_RING_BUFFER *use_ringbuf,uint16_t *res);

void FLOAT_FirstOrderLowPassFiltering_DataInit(FOLPF_DATATypeDef *data_pointer);

void FLOAT_FirstOrderLowPassFiltering_Process(FOLPF_DATATypeDef *data_pointer);

#endif
