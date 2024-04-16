#ifndef __ALGORITHM_SPWM_H__
#define __ALGORITHM_SPWM_H__

#include "arm_math.h"

#define PI_X2           (2.0f*PI)    // 2π
#define PI_X2_DIV3      (PI_X2/3.0f) // (2/3)π

typedef struct {
    float32_t vpp_percent;
    float32_t modulation_ration;
    float32_t carrier_ration;
    float32_t voltage_div_frequence;
    float32_t PI_divN;
    float32_t UV_phase;
    float32_t UW_phase;
} SPWM_HandelTypedef;

void SPWM_Modulation(TIM_HandleTypeDef *htim,SPWM_HandelTypedef *spwm_obj,float32_t frequence);

void SPWM_Drive(TIM_HandleTypeDef *htim,SPWM_HandelTypedef *spwm_obj);

void SPWM_ParaInit(SPWM_HandelTypedef *spwm_obj,
                float32_t carrier_ration,float32_t modulation_ration,float32_t PI_divN,
                float32_t UV_phase,float32_t UW_phase,float32_t voltage_div_frequence);

#endif
