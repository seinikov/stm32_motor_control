#ifndef __BSP_MOTOR_H__
#define __BSP_MOTOR_H__

#include "main.h"

#define MOTOR_ENABLE()    LL_GPIO_SetOutputPin(MOTOR_ENABLE_GPIO_Port,MOTOR_ENABLE_Pin)

#define MOTOR_DISABLE()   LL_GPIO_ResetOutputPin(MOTOR_ENABLE_GPIO_Port,MOTOR_ENABLE_Pin)

#define MOTOR_TIM_PERIOD 4999

typedef enum {
  MOTOR_DIR_CW = 0, // clock wise
  MOTOR_DIR_CCW     // counter clock wise
}MotorDir_Typedef;

typedef enum {
  MOTOR_STA_DISABLE  = 0, 
  MOTOR_STA_ENABLE
}MotorSta_Typedef ;

void MOTOR_TIMxDriveOutConfigInit(TIM_TypeDef *TIMx);

void MOTOR_SixStepPhaseChange(TIM_TypeDef *TIMx,uint8_t bemf_phase);

void MOTOR_HallStart(TIM_TypeDef *MOTOR_TIMx,TIM_TypeDef *HALL_TIMx);

void MOTOR_Breaking_LowBridge(TIM_TypeDef *TIMx);

void MOTOR_Breaking_Inertia(void);

void MOTOR_SpeedControl(TIM_TypeDef *TIMx,int32_t tim_control_val);

void MOTOR_BEMFStart(TIM_TypeDef *MOTOR_TIMx);

#endif
