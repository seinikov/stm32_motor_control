#include "main.h"
#include "tim.h"
#include "bsp_encoder.h"

__IO int32_t overflow_count=0;

void ENCODER_Init(TIM_HandleTypeDef *encoder_htim)
{
    __HAL_TIM_CLEAR_IT(encoder_htim,TIM_IT_UPDATE);
    __HAL_TIM_URS_ENABLE(encoder_htim);
    __HAL_TIM_ENABLE_IT(encoder_htim,TIM_IT_UPDATE);

    HAL_TIM_Encoder_Start(encoder_htim,TIM_CHANNEL_ALL);
}

void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim)
{
    if(htim==&htim4)
    {
        if(__HAL_TIM_IS_TIM_COUNTING_DOWN(&htim4)){
            overflow_count--;
        } else {
            overflow_count++;
        }
    }
}

int32_t ENCODER_GetCounting(TIM_HandleTypeDef *encoder_htim)
{
        int32_t val=__HAL_TIM_GET_COUNTER(encoder_htim);
        int32_t period=encoder_htim->Instance->ARR;
        return val+overflow_count*period;
}
