#include "main.h"
#include "string.h"
#include "data_ring_buffer.h"

void UINT16_DOUBLE_InitRingBuf(UINT16_DOUBLE_DATA_RING_BUFFER *use_ringbuf){
    memset((void *)use_ringbuf,0,sizeof(UINT16_DOUBLE_DATA_RING_BUFFER));
}

void UINT16_SINGLE_InitRingBuf(UINT16_SINGLE_DATA_RING_BUFFER *use_ringbuf){
    memset((void *)use_ringbuf,0,sizeof(UINT16_SINGLE_DATA_RING_BUFFER));
}

void UINT16_DOUBLE_WriteIntoRingBuf(UINT16_DOUBLE_DATA_RING_BUFFER *use_ringbuf,uint16_t write_value1,uint16_t write_value2){
    use_ringbuf->buffer[use_ringbuf->nWidx].value1=write_value1;
    use_ringbuf->buffer[use_ringbuf->nWidx].value2=write_value2;
    if(++use_ringbuf->nWidx>=NUM_RINGBUF_ELE){
        use_ringbuf->nWidx=0;
    }
    if(use_ringbuf->nWidx==use_ringbuf->nRidx){
        if(++use_ringbuf->nRidx>=NUM_RINGBUF_ELE){
            use_ringbuf->nRidx=0;
        }
    }
}

void UINT16_SINGLE_WriteIntoRingBuf(UINT16_SINGLE_DATA_RING_BUFFER *use_ringbuf,uint16_t write_value){
    use_ringbuf->buffer[use_ringbuf->nWidx]=write_value;
    if(++use_ringbuf->nWidx>=NUM_RINGBUF_ELE){
        use_ringbuf->nWidx=0;
    }
    if(use_ringbuf->nWidx==use_ringbuf->nRidx){
        if(++use_ringbuf->nRidx>=NUM_RINGBUF_ELE){
            use_ringbuf->nRidx=0;
        }
    }
}

uint8_t UINT16_DOUBLE_ReadFromRingBuf(UINT16_DOUBLE_DATA_RING_BUFFER *use_ringbuf,uint16_t *read_value1,uint16_t *read_value2){
    if (use_ringbuf->nRidx==use_ringbuf->nWidx){
        return 1;
    }
    else{
        *read_value1=use_ringbuf->buffer[use_ringbuf->nRidx].value1;
        *read_value1=use_ringbuf->buffer[use_ringbuf->nRidx].value2;
        if(++use_ringbuf->nRidx>=NUM_RINGBUF_ELE){
            use_ringbuf->nRidx=0;
        }
        return 0;
    }    
}

uint8_t UINT16_SINGLE_ReadFromRingBuf(UINT16_SINGLE_DATA_RING_BUFFER *use_ringbuf,uint16_t *read_value){
    if (use_ringbuf->nRidx==use_ringbuf->nWidx){
        return 1;
    }
    else{
        *read_value=use_ringbuf->buffer[use_ringbuf->nRidx];
        if(++use_ringbuf->nRidx>=NUM_RINGBUF_ELE){
            use_ringbuf->nRidx=0;
        }
        return 0;
    }    
}
