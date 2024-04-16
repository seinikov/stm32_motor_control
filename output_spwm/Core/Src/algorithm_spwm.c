#include "main.h"
#include "arm_math.h"
#include "math.h"
#include "algorithm_spwm.h"

extern SPWM_HandelTypedef global_spwm;

void SPWM_ParaInit(SPWM_HandelTypedef *spwm_obj,
                float32_t carrier_ration,float32_t modulation_ration,float32_t PI_divN,
                float32_t UV_phase,float32_t UW_phase,float32_t voltage_div_frequence){
    spwm_obj->carrier_ration=carrier_ration;
    spwm_obj->modulation_ration=modulation_ration;
    spwm_obj->PI_divN=PI_divN;
    spwm_obj->UV_phase=UV_phase;
    spwm_obj->UW_phase=UW_phase;
    spwm_obj->voltage_div_frequence=voltage_div_frequence;
}

void SPWM_Modulation(TIM_HandleTypeDef *htim,SPWM_HandelTypedef *spwm_obj,float32_t frequence){
    if(frequence>0.f){
        spwm_obj->vpp_percent=frequence*spwm_obj->voltage_div_frequence;
        if(spwm_obj->vpp_percent>100.f){
            spwm_obj->vpp_percent=100.f;
        }
        spwm_obj->modulation_ration=spwm_obj->vpp_percent/100.f;
        spwm_obj->carrier_ration=((1.68e8/(htim->Init.Prescaler+1))/(2*(htim->Init.Period+1)))/frequence;
        spwm_obj->PI_divN=PI_X2/spwm_obj->modulation_ration;
        spwm_obj->UV_phase=+PI_X2_DIV3;
        spwm_obj->UW_phase=-PI_X2_DIV3;
    }
    else if(frequence<0.0f){
        frequence=-frequence;
        if(spwm_obj->vpp_percent>100.f){
            spwm_obj->vpp_percent=100.f;
        }
        spwm_obj->modulation_ration=spwm_obj->vpp_percent/100.f;
        spwm_obj->carrier_ration=((1.68e8/(htim->Init.Prescaler+1))/(2*(htim->Init.Period+1)))/frequence;
        spwm_obj->PI_divN=PI_X2/spwm_obj->modulation_ration;
        spwm_obj->UV_phase=-PI_X2_DIV3;
        spwm_obj->UW_phase=+PI_X2_DIV3;
    }
    else {
        spwm_obj->modulation_ration=0;
        spwm_obj->PI_divN=0;
    }
}

void SPWM_Drive(TIM_HandleTypeDef *htim,SPWM_HandelTypedef *spwm_obj){
    uint16_t ccr2=0;
    uint16_t ccr3=0;

    ccr2=((htim->Init.Period+1)/2)*(1.f+spwm_obj->modulation_ration*(arm_sin_f32(spwm_obj->UV_phase)));
    ccr3=((htim->Init.Period+1)/2)*(1.f+spwm_obj->modulation_ration*(sinf(spwm_obj->UW_phase)));

    __HAL_TIM_SetCompare(htim,TIM_CHANNEL_1,((htim->Init.Period+1)/2));
    __HAL_TIM_SetCompare(htim,TIM_CHANNEL_2,ccr2);
    __HAL_TIM_SetCompare(htim,TIM_CHANNEL_3,ccr3);

    HAL_TIM_GenerateEvent(htim,TIM_EVENTSOURCE_UPDATE);
    __HAL_TIM_CLEAR_FLAG(htim,TIM_FLAG_UPDATE);

    __HAL_TIM_ENABLE_IT(htim,TIM_IT_UPDATE);

    HAL_TIM_PWM_Start(htim,TIM_CHANNEL_1);
    HAL_TIM_PWM_Start(htim,TIM_CHANNEL_2);
    HAL_TIM_PWM_Start(htim,TIM_CHANNEL_3);

    HAL_TIMEx_PWMN_Start(htim,TIM_CHANNEL_1);
    HAL_TIMEx_PWMN_Start(htim,TIM_CHANNEL_2);
    HAL_TIMEx_PWMN_Start(htim,TIM_CHANNEL_3);

    HAL_TIM_PeriodElapsedCallback(htim);
}

void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim){
    uint16_t ccr1=0;
    uint16_t ccr2=0;
    uint16_t ccr3=0;
    static float32_t i=1.f;
    
    float32_t tmp=global_spwm.PI_divN*1;
    ccr1=((htim->Init.Period+1)/2)*(global_spwm.modulation_ration+global_spwm.modulation_ration*(sinf(tmp)));
    ccr2=((htim->Init.Period+1)/2)*(global_spwm.modulation_ration+global_spwm.modulation_ration*(sinf(tmp+global_spwm.UV_phase)));
    ccr3=((htim->Init.Period+1)/2)*(global_spwm.modulation_ration+global_spwm.modulation_ration*(sinf(tmp+global_spwm.UW_phase)));

    __HAL_TIM_SetCompare(htim,TIM_CHANNEL_1,ccr1);
    __HAL_TIM_SetCompare(htim,TIM_CHANNEL_2,ccr2);
    __HAL_TIM_SetCompare(htim,TIM_CHANNEL_3,ccr3);
    
    i++;
    if(i>=global_spwm.carrier_ration){
        i=0;
    }
}

