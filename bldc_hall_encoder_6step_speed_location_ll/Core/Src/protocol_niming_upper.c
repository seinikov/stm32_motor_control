#include "main.h"
#include "protocol_niming_upper.h"

void Protocol_NIMING_HallWithMortor(UART_HandleTypeDef *use_huart,uint8_t ID,float speed_hz,float rps,float rpm){
    uint8_t tx_buf[64]={0};
    uint8_t counter = 0;
    tx_buf [counter++]  = 0xAA; //HEAD
    tx_buf [counter++]  = 0xFF; //D_ADDR
    tx_buf [counter++]  = ID;   //ID
    tx_buf [counter++]  = 0x00; //Longth after this byte, will be reset later
    int32_t f2i32_tmp=speed_hz*100;
    tx_buf [counter++]  = (f2i32_tmp)&0xFF;
    tx_buf [counter++]  = ((f2i32_tmp)>>8)&0xFF;
    tx_buf [counter++]  = ((f2i32_tmp)>>16)&0xFF;
    tx_buf [counter++]  = ((f2i32_tmp)>>24)&0xFF;
    f2i32_tmp=rps*100;
    tx_buf [counter++]  = (f2i32_tmp)&0xFF;
    tx_buf [counter++]  = ((f2i32_tmp)>>8)&0xFF;
    tx_buf [counter++]  = ((f2i32_tmp)>>16)&0xFF;
    tx_buf [counter++]  = ((f2i32_tmp)>>24)&0xFF;
    f2i32_tmp=rpm*100;
    tx_buf [counter++]  = (f2i32_tmp)&0xFF;
    tx_buf [counter++]  = ((f2i32_tmp)>>8)&0xFF;
    tx_buf [counter++]  = ((f2i32_tmp)>>16)&0xFF;
    tx_buf [counter++]  = ((f2i32_tmp)>>24)&0xFF;

    tx_buf [3] = counter - 4;   //Longth, re-load longth
    uint8_t sum = 0;
    uint8_t ac  = 0;
    for(int8_t i = 0; i < counter; i++) {
        sum += tx_buf[i];
        ac+=sum;
    }
    tx_buf[counter++] = sum;
    tx_buf[counter++]   =ac;

    HAL_UART_Transmit(use_huart,tx_buf,counter,HAL_MAX_DELAY);
}

void Protocol_NIMING_HallAndEncoderWihtMortor(UART_HandleTypeDef *use_huart,uint8_t ID,float speed_hz,float rps,float rpm,int32_t encoder_num){
    uint8_t tx_buf[64]={0};
    uint8_t counter = 0;
    tx_buf [counter++]  = 0xAA; //HEAD
    tx_buf [counter++]  = 0xFF; //D_ADDR
    tx_buf [counter++]  = ID;   //ID
    tx_buf [counter++]  = 0x00; //Longth after this byte, will be reset later

    int32_t f2i32_tmp=speed_hz*100;
    tx_buf [counter++]  = (f2i32_tmp)&0xFF;
    tx_buf [counter++]  = ((f2i32_tmp)>>8)&0xFF;
    tx_buf [counter++]  = ((f2i32_tmp)>>16)&0xFF;
    tx_buf [counter++]  = ((f2i32_tmp)>>24)&0xFF;

    f2i32_tmp=rps*100;
    tx_buf [counter++]  = (f2i32_tmp)&0xFF;
    tx_buf [counter++]  = ((f2i32_tmp)>>8)&0xFF;
    tx_buf [counter++]  = ((f2i32_tmp)>>16)&0xFF;
    tx_buf [counter++]  = ((f2i32_tmp)>>24)&0xFF;

    f2i32_tmp=rpm*100;
    tx_buf [counter++]  = (f2i32_tmp)&0xFF;
    tx_buf [counter++]  = ((f2i32_tmp)>>8)&0xFF;
    tx_buf [counter++]  = ((f2i32_tmp)>>16)&0xFF;
    tx_buf [counter++]  = ((f2i32_tmp)>>24)&0xFF;

    tx_buf [counter++]  = (encoder_num)&0xFF;
    tx_buf [counter++]  = ((encoder_num)>>8)&0xFF;
    tx_buf [counter++]  = ((encoder_num)>>16)&0xFF;
    tx_buf [counter++]  = ((encoder_num)>>24)&0xFF;

    tx_buf [3] = counter - 4;   //Longth, re-load longth
    uint8_t sum = 0;
    uint8_t ac  = 0;
    for(int8_t i = 0; i < counter; i++) {
        sum += tx_buf[i];
        ac+=sum;
    }
    tx_buf[counter++] = sum;
    tx_buf[counter++]   =ac;

    HAL_UART_Transmit(use_huart,tx_buf,counter,HAL_MAX_DELAY);
}

void Protocol_NIMING_Mortor_EMF(UART_HandleTypeDef *use_huart,uint8_t ID,float u,float v,float w){
    uint8_t tx_buf[64]={0};
    uint8_t counter = 0;
    tx_buf [counter++]  = 0xAA; //HEAD
    tx_buf [counter++]  = 0xFF; //D_ADDR
    tx_buf [counter++]  = ID;   //ID
    tx_buf [counter++]  = 0x00; //Longth after this byte, will be reset later
    int32_t f2i32_tmp=u;
    tx_buf [counter++]  = (f2i32_tmp)&0xFF;
    tx_buf [counter++]  = ((f2i32_tmp)>>8)&0xFF;
    tx_buf [counter++]  = ((f2i32_tmp)>>16)&0xFF;
    tx_buf [counter++]  = ((f2i32_tmp)>>24)&0xFF;
    f2i32_tmp=v;
    tx_buf [counter++]  = (f2i32_tmp)&0xFF;
    tx_buf [counter++]  = ((f2i32_tmp)>>8)&0xFF;
    tx_buf [counter++]  = ((f2i32_tmp)>>16)&0xFF;
    tx_buf [counter++]  = ((f2i32_tmp)>>24)&0xFF;
    f2i32_tmp=w;
    tx_buf [counter++]  = (f2i32_tmp)&0xFF;
    tx_buf [counter++]  = ((f2i32_tmp)>>8)&0xFF;
    tx_buf [counter++]  = ((f2i32_tmp)>>16)&0xFF;
    tx_buf [counter++]  = ((f2i32_tmp)>>24)&0xFF;

    tx_buf [3] = counter - 4;   //Longth, re-load longth
    uint8_t sum = 0;
    uint8_t ac  = 0;
    for(int8_t i = 0; i < counter; i++) {
        sum += tx_buf[i];
        ac+=sum;
    }
    tx_buf[counter++] = sum;
    tx_buf[counter++]   =ac;

    HAL_UART_Transmit(use_huart,tx_buf,counter,HAL_MAX_DELAY);
}
