#ifndef __BSP_MOTOR_H__
#define __BSP_MOTOR_H__

#include "main.h"
#include "stm32h7xx_hal_tim.h"
#include "tim.h"

typedef enum 
{
  MOTOR_DIR_CW = 0, // clock wise
  MOTOR_DIR_CCW     // counter clock wise
}MotorDir_Typedef;

typedef enum 
{
  MOTOR_ENABLE  = 0, 
  MOTOR_DISABLE
}MotorSta_Typedef ;

void MOTOR_TIMxDriveOutConfigInit(TIM_HandleTypeDef *use_tim_handle,TIM_OC_InitTypeDef *oc_handle,
                        uint32_t use_channel_1,uint32_t use_channel_2,uint32_t use_channel_3);

void MOTOR_TIMxHallStart(TIM_HandleTypeDef *use_tim_handle);

#endif
