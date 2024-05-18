#ifndef __PROTOCOL_NIMING_MONITOR_H__
#define __PROTOCOL_NIMING_MONITOR_H__

void Protocol_NIMING_HallWithMortor(UART_HandleTypeDef *use_huart,uint8_t ID,
                            float speed_hz,float rps,float rpm);

void Protocol_NIMING_HallAndEncoderWihtMortor(UART_HandleTypeDef *use_huart,uint8_t ID,float speed_hz,float rps,float rpm,int32_t encoder_num);

void Protocol_NIMING_Mortor_EMF(UART_HandleTypeDef *use_huart,uint8_t ID,
                            float u,float v,float w);

#endif
