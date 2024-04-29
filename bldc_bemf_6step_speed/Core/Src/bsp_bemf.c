#include "main.h"
#include "adc.h"
#include "bsp_bemf.h"

extern uint16_t adc_value[3];

void ADC_Demo(void)
{
    for(uint8_t cnt=0;cnt<3;cnt++){
        HAL_ADC_PollForConversion(&hadc3,10);
        adc_value[cnt] = HAL_ADC_GetValue(&hadc3);
    }

    return ;
}
