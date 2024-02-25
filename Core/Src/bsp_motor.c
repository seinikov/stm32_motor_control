#include "main.h"
#include "stm32h7xx_hal_tim.h"
#include "tim.h"
#include "bsp_motor.h"
#include "debug.h"

extern MotorSta_Typedef global_motorsta;
extern MotorDir_Typedef global_motordir;

void MOTOR_TIMxDriveOutConfigInit(TIM_HandleTypeDef *use_tim_handle,TIM_OC_InitTypeDef *oc_handle,
                        uint32_t use_channel_1,uint32_t use_channel_2,uint32_t use_channel_3){
    HAL_TIM_OC_ConfigChannel(use_tim_handle,oc_handle,use_channel_1);
    HAL_TIM_OC_ConfigChannel(use_tim_handle,oc_handle,use_channel_2);
    HAL_TIM_OC_ConfigChannel(use_tim_handle,oc_handle,use_channel_3);

    HAL_TIMEx_ConfigCommutationEvent(use_tim_handle,TIM_TS_ITR2,TIM_COMMUTATION_TRGI);
}

void MOTOR_Init(MotorDir_Typedef *obj_dir,MotorSta_Typedef *obj_sta,MotorDir_Typedef dir_choice){
    global_motorsta=MOTOR_STA_ENABLE;
    global_motordir=dir_choice;
    MOTOR_ENABLE();
}

void Motor_Control(uint8_t hall_phase){
    
}
