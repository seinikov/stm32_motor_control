#include "main.h"
#include "bsp_motor.h"
#include "bsp_hall.h"
#include "tim.h"
#include "debug.h"

uint8_t current_hall_phase=0,last_hall_pahse=0;
uint8_t hall_dir=MOTOR_DIR_CW;

void HALLSENSOR_TIMxStart(TIM_HandleTypeDef *use_tim_handle){
    HAL_TIMEx_HallSensor_Start_IT(use_tim_handle);
    current_hall_phase=last_hall_pahse;
}

uint8_t HALLSENSOR_GetPhase(void){
    uint8_t phase=0;
    phase |= HAL_GPIO_ReadPin(GPIOC,GPIO_PIN_6);
    phase <<= 1;
    phase |= HAL_GPIO_ReadPin(GPIOC,GPIO_PIN_7);
    phase <<= 1;
    phase |= HAL_GPIO_ReadPin(GPIOC,GPIO_PIN_8);
    return (phase&0x07);
}

void HAL_TIM_IC_CaptureCallback(TIM_HandleTypeDef *htim){
    current_hall_phase=HALLSENSOR_GetPhase();
    if(MOTOR_ENABLE)
}
