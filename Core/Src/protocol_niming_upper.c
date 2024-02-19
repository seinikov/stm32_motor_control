#include "main.h"
#include "protocol_niming_upper.h"

void Protocol_NIMING_TemperatureDataPostback(UART_HandleTypeDef *use_huart,uint8_t ID,
                                            float heater_tempature,float pres_temperature,
                                            float pres_pressure,float ias,float aoa,float aos){
    uint8_t tx_buf[16]={0};
    uint8_t counter = 0;
    tx_buf [counter++]  = 0xAA; //HEAD
    tx_buf [counter++]  = 0xFF; //D_ADDR
    tx_buf [counter++]  = ID;   //ID
    tx_buf [counter++]  = 0x00; //Longth after this byte, will be reset later
    int16_t f2i16_tmp=heater_tempature*10;
    tx_buf [counter++]  = (f2i16_tmp)&0xFF;
    tx_buf [counter++]  = ((f2i16_tmp)>>8)&0xFF;
    f2i16_tmp=pres_temperature*10;
    tx_buf [counter++]  = (f2i16_tmp)&0xFF;
    tx_buf [counter++]  = ((f2i16_tmp)>>8)&0xFF;
    f2i16_tmp=pres_pressure*10;
    tx_buf [counter++]  = (f2i16_tmp)&0xFF;
    tx_buf [counter++]  = ((f2i16_tmp)>>8)&0xFF;
    f2i16_tmp=ias*10;
    tx_buf [counter++]  = (f2i16_tmp)&0xFF;
    tx_buf [counter++]  = ((f2i16_tmp)>>8)&0xFF;
    f2i16_tmp=aoa*10;
    tx_buf [counter++]  = (f2i16_tmp)&0xFF;
    tx_buf [counter++]  = ((f2i16_tmp)>>8)&0xFF;
    f2i16_tmp=aos*10;
    tx_buf [counter++]  = (f2i16_tmp)&0xFF;
    tx_buf [counter++]  = ((f2i16_tmp)>>8)&0xFF;

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
