#include "main.h"
#include "tim.h"
#include "bsp_encoder.h"

__IO int32_t overflow_count=0;

void ENCODER_TIMxStart(TIM_TypeDef *ENCODER_TIMx)
{
    LL_TIM_ClearFlag_UPDATE(ENCODER_TIMx);

    LL_TIM_EnableIT_UPDATE(ENCODER_TIMx);
    LL_TIM_SetUpdateSource(ENCODER_TIMx,LL_TIM_UPDATESOURCE_COUNTER);
    LL_TIM_CC_EnableChannel(ENCODER_TIMx,LL_TIM_CHANNEL_CH1);
    LL_TIM_CC_EnableChannel(ENCODER_TIMx,LL_TIM_CHANNEL_CH2);

    LL_TIM_EnableCounter(ENCODER_TIMx);
}

void ENCODER_TIMxIRQCallback(TIM_TypeDef *ENCODER_TIMx)
{
    LL_TIM_ClearFlag_UPDATE(ENCODER_TIMx);
    if(LL_TIM_COUNTERMODE_DOWN==LL_TIM_GetCounterMode(ENCODER_TIMx)){
        overflow_count--;
    }else{
        overflow_count++;
    }
}

int32_t ENCODER_GetCounting(TIM_TypeDef *ENCODER_TIMx)
{
    int32_t val=LL_TIM_GetCounter(ENCODER_TIMx);
    int32_t period=ENCODER_TIMx->ARR;
    
    return val+overflow_count*period;
}
