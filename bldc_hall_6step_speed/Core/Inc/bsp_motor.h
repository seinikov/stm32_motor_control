#ifndef __BSP_MOTOR_H__
#define __BSP_MOTOR_H__

#include "main.h"

#define MOTOR_ENABLE()    HAL_GPIO_WritePin(MOTOR_ENABLE_GPIO_Port,MOTOR_ENABLE_Pin,GPIO_PIN_SET)
#define MOTOR_DISABLE()   HAL_GPIO_WritePin(MOTOR_ENABLE_GPIO_Port,MOTOR_ENABLE_Pin,GPIO_PIN_RESET)

#define MOTOR_TIM_PERIOD 4999

typedef enum {
  MOTOR_DIR_CW = 0, // clock wise
  MOTOR_DIR_CCW     // counter clock wise
}MotorDir_Typedef;

typedef enum {
  MOTOR_STA_DISABLE  = 0, 
  MOTOR_STA_ENABLE
}MotorSta_Typedef ;

void MOTOR_TIMxDriveOutConfigInit(TIM_HandleTypeDef *use_tim_handle,TIM_OC_InitTypeDef *oc_handle,
                        uint32_t use_channel_1,uint32_t use_channel_2,uint32_t use_channel_3);

void MOTOR_Control(TIM_HandleTypeDef *motor_tim_handle,uint8_t hall_phase);

void MOTOR_Start(TIM_HandleTypeDef *motor_tim_handle,TIM_HandleTypeDef *hall_sensor_tim_handle);

void MOTOR_SpeedControl(TIM_HandleTypeDef *motor_tim_handle,int32_t tim_control_val);

#endif
