#ifndef __BSP_ENCODER_H__
#define __BSP_ENCODER_H__

void ENCODER_Init(TIM_HandleTypeDef *encoder_htim);

int32_t ENCODER_GetCounting(TIM_HandleTypeDef *encoder_htim);

#endif
