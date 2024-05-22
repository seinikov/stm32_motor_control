#ifndef __BSP_ENCODER_H__
#define __BSP_ENCODER_H__

void ENCODER_TIMxStart(TIM_TypeDef *ENCODER_TIMx);

void ENCODER_TIMxIRQCallback(TIM_TypeDef *ENCODER_TIMx);

int32_t ENCODER_GetCounting(TIM_TypeDef *ENCODER_TIMx);

#endif
