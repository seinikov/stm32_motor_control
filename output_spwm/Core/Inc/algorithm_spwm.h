#ifndef __ALGORITHM_SPWM_H__
#define __ALGORITHM_SPWM_H__

#include "arm_math.h"

#define PI_X2           (2.0f*PI)    // 2π
#define PI_X2_DIV3      (PI_X2/3.0f) // (2/3)π

/* 根据实际需求调整频率和幅值 */
// 调制波频率  // 本例程可调范围是10~210Hz,如果需要其他范围的频率，需要调整载波比
#define  MODULATED_FREQ_Hz     20.0f  // 调制波形(正弦波)频率
// 调制比 输出波形电压幅值与直流电压幅值之比 0< r <100
#define  MODULATION_RATIO      20.0f   //

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

void SPWM_Start(TIM_HandleTypeDef *htim,SPWM_HandelTypedef *spwm_obj);

void SPWM_ParaInit(SPWM_HandelTypedef *spwm_obj,
                float32_t carrier_ration,float32_t modulation_ration,float32_t PI_divN,
                float32_t UV_phase,float32_t UW_phase,float32_t voltage_div_frequence);

#endif
