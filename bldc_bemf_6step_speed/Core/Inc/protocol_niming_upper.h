#ifndef __PROTOCOL_NIMING_MONITOR_H__
#define __PROTOCOL_NIMING_MONITOR_H__
#include "main.h"

void Protocol_NIMING_Mortor(UART_HandleTypeDef *use_huart,uint8_t ID,
                                            float speed_hz,float rps,float rpm);

#endif
