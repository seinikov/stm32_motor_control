#ifndef __DATA_RING_BUFFER__
#define __DATA_RING_BUFFER__

#include "main.h"

#define NUM_RINGBUF_ELE 20

typedef struct {
    uint16_t value1;
    uint16_t value2;
} UINT16_DOUBLE_ELEMENT;

typedef struct {
    UINT16_DOUBLE_ELEMENT buffer[NUM_RINGBUF_ELE];
    uint8_t nRidx;
    uint8_t nWidx;
} UINT16_DOUBLE_DATA_RING_BUFFER;

typedef struct {
    uint16_t buffer[NUM_RINGBUF_ELE];
    uint8_t nRidx;
    uint8_t nWidx;
} UINT16_SINGLE_DATA_RING_BUFFER;


void UINT16_DOUBLE_InitRingBuf(UINT16_DOUBLE_DATA_RING_BUFFER *use_ringbuf);

void UINT16_DOUBLE_WriteIntoRingBuf(UINT16_DOUBLE_DATA_RING_BUFFER *use_ringbuf,uint16_t write_value1,uint16_t write_value2);

uint8_t UINT16_DOUBLE_ReadFromRingBuf(UINT16_DOUBLE_DATA_RING_BUFFER *use_ringbuf,uint16_t *read_value1,uint16_t *read_value2);

void UINT16_SINGLE_InitRingBuf(UINT16_SINGLE_DATA_RING_BUFFER *use_ringbuf);

void UINT16_SINGLE_WriteIntoRingBuf(UINT16_SINGLE_DATA_RING_BUFFER *use_ringbuf,uint16_t write_value);

uint8_t UINT16_DOUBLE_ReadFromRingBuf(UINT16_DOUBLE_DATA_RING_BUFFER *use_ringbuf,uint16_t *read_value1,uint16_t *read_value2);

#endif

