#include "main.h"
#include "bsp_motor.h"
#include "bsp_hall.h"
#include "tim.h"
#include "debug.h"

uint8_t hall_current_phase=0,hall_last_pahse=0;
uint8_t hall_dir=MOTOR_DIR_CW;
uint8_t hall_dir_ccw [7] = {0, 3, 6, 2, 5, 1, 4};
extern MotorSta_Typedef global_motorsta;
extern MotorDir_Typedef global_motordir;

uint32_t hall_compare;
uint32_t hall_count;

void HALLSENSOR_TIMxStart(TIM_HandleTypeDef *use_tim_handle){
    HAL_TIMEx_HallSensor_Start_IT(use_tim_handle);
    hall_current_phase=hall_last_pahse;
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
    hall_current_phase=HALLSENSOR_GetPhase();
    if(global_motorsta==MOTOR_STA_ENABLE){
        /********************/
        /*change phase logic*/
    }
    hall_compare=__HAL_TIM_GET_COMPARE(htim,TIM_CHANNEL_1);
    hall_count++;
    if(hall_dir_ccw[hall_current_phase]==hall_last_pahse){
        hall_dir=MOTOR_DIR_CCW;
    }
    else{
        hall_dir=MOTOR_DIR_CW;
    }
    hall_last_pahse=hall_current_phase;
}

float HALLSENSOR_SpeedFrequency_Hz(){
    float compare_pre_time=0;
    if((0==hall_count)||(0==hall_compare)){
        return 0;
    }
    else{
        compare_pre_time=(float)hall_compare/(float)hall_count;
        hall_compare=0;
        hall_count=0;
        return ((float)HALL_TIM_FREQ/compare_pre_time);
    }
}
