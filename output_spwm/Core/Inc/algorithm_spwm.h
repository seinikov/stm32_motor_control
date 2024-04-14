#ifndef __ALGORITHM_SPWM_H__
#define __ALGORITHM_SPWM_H__

#include "arm_math.h"

typedef struct {
    float32_t vpp_percent;
    float32_t modulation_ration;
    float32_t carrier_ration;
    float32_t voltage_div_frequence;
    float32_t PI_divN;
    float32_t UV_phase;
    float32_t UW_phase;
} SPWM_HandelTypedef;


#endif
