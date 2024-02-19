#ifndef __ALGORITHM_FILTERING_H__
#define __ALGORITHM_FILTERING_H__

#include "main.h"
#include "data_ring_buffer.h"

void UINT16_DOUBLE_AverageFiltering(UINT16_DOUBLE_DATA_RING_BUFFER *use_ringbuf,uint16_t *res1,uint16_t *res2);

void UINT16_SINGLE_AverageFiltering(UINT16_SINGLE_DATA_RING_BUFFER *use_ringbuf,uint16_t *res);

#endif
