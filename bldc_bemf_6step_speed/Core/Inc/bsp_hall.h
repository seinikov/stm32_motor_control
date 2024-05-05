#ifndef __BSP_HALL_H__
#define __BSP_HALL_H__

#define HALL_TIM_PRESCALER 199
#define HALL_TIM_FREQ      (2e8/(HALL_TIM_PRESCALER+1))

#define POLE_PAIRES 4
#define PPR         (POLE_PAIRES*2*3)

#define HALL_PHASE_B2A 5
#define HALL_PHASE_C2A 4
#define HALL_PHASE_C2B 6
#define HALL_PHASE_A2B 2
#define HALL_PHASE_A2C 3
#define HALL_PHASE_B2C 1

void HALLSENSOR_TIMxStart(TIM_TypeDef *HALL_TIMx);

void HALLSENSOR_TIMxIRQCallback(TIM_TypeDef *HALL_TIMx);

uint8_t HALLSENSOR_GetPhase(void);

float HALLSENSOR_SpeedFrequency_Hz(void);

#endif
