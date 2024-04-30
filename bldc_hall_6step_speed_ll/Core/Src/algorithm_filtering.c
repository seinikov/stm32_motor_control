#include "algorithm_filtering.h"
#include "arm_math.h"

void UINT16_DOUBLE_AverageFiltering(UINT16_DOUBLE_DATA_RING_BUFFER *use_ringbuf,uint16_t *res1,uint16_t *res2){
    uint32_t sum1=0,sum2=0;
    for(uint8_t counter=0;counter<NUM_RINGBUF_ELE;counter++){
        sum1+=use_ringbuf->buffer[counter].value1;
        sum2+=use_ringbuf->buffer[counter].value2;
    }
    *res1=sum1/NUM_RINGBUF_ELE;
    *res2=sum2/NUM_RINGBUF_ELE;
}

void UINT16_SINGLE_AverageFiltering(UINT16_SINGLE_DATA_RING_BUFFER *use_ringbuf,uint16_t *res){
    uint32_t sum=0;
    for(uint8_t counter=0;counter<NUM_RINGBUF_ELE;counter++){
        sum+=use_ringbuf->buffer[counter];
    }
    *res=sum/NUM_RINGBUF_ELE;
}

void FLOAT_FirstOrderLowPassFiltering_DataInit(FOLPF_HandleTypeDef *folpf_obj,float32_t alpha_value){
    folpf_obj->current_val=0.f;
    folpf_obj->last_val=0.f;
    folpf_obj->alpha=alpha_value;
}

void FLOAT_FirstOrderLowPassFiltering_Process(FOLPF_HandleTypeDef *folpf_obj){
    folpf_obj->current_val=((1-folpf_obj->alpha)*folpf_obj->last_val)+(folpf_obj->alpha *folpf_obj->current_val);
    folpf_obj->last_val=folpf_obj->current_val;
}
