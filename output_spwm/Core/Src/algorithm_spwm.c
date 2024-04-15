#include "main.h"
#include "arm_math.h"
#include "algorithm_spwm.h"

#define PI_X2           (2.0f*PI)    // 2π
#define PI_X2_DIV3      (PI_X2/3.0f) // (2/3)π

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

void SPWM_Drive(TIM_HandleTypeDef *htim){
    uint16_t ccr2=0;
    uint16_t ccr3=0;

    ccr2=((htim->Init.Period+1)/2);
}

void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim,SPWM_HandelTypedef *spwm_obj){
    uint16_t ccr1=0;
    uint16_t ccr2=0;
    uint16_t ccr3=0;
    static float32_t i=1.f;
    
    float32_t tmp=spwm_obj->PI_divN*1;
    ccr1=((htim->Init.Period+1)/2)*
}

