#include "bsp_motor.h"

uint8_t current_hall_phase = 0;
uint8_t last_hall_pahse    = 0;

uint8_t motor_dir=MOTOR_DIR_CW;
uint8_t hall_dir;

void MOTOR_TIMxDriveOutConfigInit(TIM_HandleTypeDef *use_tim_handle,TIM_OC_InitTypeDef *oc_handle,
                        uint32_t use_channel_1,uint32_t use_channel_2,uint32_t use_channel_3){
    HAL_TIM_OC_ConfigChannel(use_tim_handle,oc_handle,use_channel_1);
    HAL_TIM_OC_ConfigChannel(use_tim_handle,oc_handle,use_channel_2);
    HAL_TIM_OC_ConfigChannel(use_tim_handle,oc_handle,use_channel_3);

    HAL_TIMEx_ConfigCommutationEvent(use_tim_handle,TIM_TS_ITR2,TIM_COMMUTATION_TRGI);
}

void MOTOR_TIMxHallStart(TIM_HandleTypeDef *use_tim_handle){
    HAL_TIMEx_HallSensor_Start_IT(use_tim_handle);
    current_hall_phase=last_hall_pahse;
    hall_dir=motor_dir;
}
