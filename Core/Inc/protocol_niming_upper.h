#ifndef __PROTOCOL_NIMING_MONITOR_H__
#define __PROTOCOL_NIMING_MONITOR_H__
#include "main.h"

void Protocol_NIMING_TemperatureDataPostback(UART_HandleTypeDef *use_huart,uint8_t ID,
                                            float heater_tempature,float pres_temperature,
                                            float pres_pressure,float ias,float aoa,float aos);

#endif
