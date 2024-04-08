#include "main.h"
#include "stm32h7xx_hal_tim.h"
#include "tim.h"
#include "bsp_motor.h"
#include "bsp_hall.h"
#include "debug.h"

extern MotorSta_Typedef global_motorsta;
extern MotorDir_Typedef global_motordir;
extern uint32_t global_pwm_duty;

void MOTOR_TIMxDriveOutConfigInit(TIM_HandleTypeDef *motor_tim_handle,TIM_OC_InitTypeDef *oc_handle,
                        uint32_t use_channel_1,uint32_t use_channel_2,uint32_t use_channel_3){
    HAL_TIM_OC_ConfigChannel(motor_tim_handle,oc_handle,use_channel_1);
    HAL_TIM_OC_ConfigChannel(motor_tim_handle,oc_handle,use_channel_2);
    HAL_TIM_OC_ConfigChannel(motor_tim_handle,oc_handle,use_channel_3);

    HAL_TIMEx_ConfigCommutationEvent(motor_tim_handle,TIM_TS_ITR2,TIM_COMMUTATION_TRGI);
}

void MOTOR_Init(MotorDir_Typedef *obj_dir,MotorSta_Typedef *obj_sta,MotorDir_Typedef dir_choice){
    global_motorsta=MOTOR_STA_DISABLE;
    global_motordir=dir_choice;
}

void MOTOR_Control(TIM_HandleTypeDef *motor_tim_handle,uint8_t hall_phase){
    if(MOTOR_DIR_CW==global_motordir){
        hall_phase=0x07^hall_phase;
    } 
    switch (hall_phase)
    {
    case HALL_PHASE_B2A:{
        HAL_TIM_PWM_Stop(motor_tim_handle,TIM_CHANNEL_3);
        HAL_TIMEx_PWMN_Stop(motor_tim_handle,TIM_CHANNEL_3);

        __HAL_TIM_SET_COMPARE(motor_tim_handle,TIM_CHANNEL_2,global_pwm_duty);
        HAL_TIM_PWM_Start(motor_tim_handle,TIM_CHANNEL_2);
        HAL_TIMEx_PWMN_Stop(motor_tim_handle,TIM_CHANNEL_2);

        __HAL_TIM_SET_COMPARE(motor_tim_handle,TIM_CHANNEL_1,MOTOR_TIM_PERIOD+1);
        HAL_TIM_PWM_Stop(motor_tim_handle,TIM_CHANNEL_1);
        HAL_TIMEx_PWMN_Start(motor_tim_handle,TIM_CHANNEL_1);

        break;
    }
    case HALL_PHASE_C2A:{
        HAL_TIM_PWM_Stop(motor_tim_handle,TIM_CHANNEL_2);
        HAL_TIMEx_PWMN_Stop(motor_tim_handle,TIM_CHANNEL_2);

        __HAL_TIM_SET_COMPARE(motor_tim_handle,TIM_CHANNEL_3,global_pwm_duty);
        HAL_TIM_PWM_Start(motor_tim_handle,TIM_CHANNEL_3);
        HAL_TIMEx_PWMN_Stop(motor_tim_handle,TIM_CHANNEL_3);

        __HAL_TIM_SET_COMPARE(motor_tim_handle,TIM_CHANNEL_1,MOTOR_TIM_PERIOD+1);
        HAL_TIM_PWM_Stop(motor_tim_handle,TIM_CHANNEL_1);
        HAL_TIMEx_PWMN_Start(motor_tim_handle,TIM_CHANNEL_1);

        break;
    }
    case HALL_PHASE_C2B:{
        HAL_TIM_PWM_Stop(motor_tim_handle,TIM_CHANNEL_1);
        HAL_TIMEx_PWMN_Stop(motor_tim_handle,TIM_CHANNEL_1);

        __HAL_TIM_SET_COMPARE(motor_tim_handle,TIM_CHANNEL_3,global_pwm_duty);
        HAL_TIM_PWM_Start(motor_tim_handle,TIM_CHANNEL_3);
        HAL_TIMEx_PWMN_Stop(motor_tim_handle,TIM_CHANNEL_3);

        __HAL_TIM_SET_COMPARE(motor_tim_handle,TIM_CHANNEL_2,MOTOR_TIM_PERIOD+1);
        HAL_TIM_PWM_Stop(motor_tim_handle,TIM_CHANNEL_2);
        HAL_TIMEx_PWMN_Start(motor_tim_handle,TIM_CHANNEL_2);

        break;
    }
    case HALL_PHASE_A2B:{
        HAL_TIM_PWM_Stop(motor_tim_handle,TIM_CHANNEL_3);
        HAL_TIMEx_PWMN_Stop(motor_tim_handle,TIM_CHANNEL_3);

        __HAL_TIM_SET_COMPARE(motor_tim_handle,TIM_CHANNEL_1,global_pwm_duty);
        HAL_TIM_PWM_Start(motor_tim_handle,TIM_CHANNEL_1);
        HAL_TIMEx_PWMN_Stop(motor_tim_handle,TIM_CHANNEL_1);

        __HAL_TIM_SET_COMPARE(motor_tim_handle,TIM_CHANNEL_2,MOTOR_TIM_PERIOD+1);
        HAL_TIM_PWM_Stop(motor_tim_handle,TIM_CHANNEL_2);
        HAL_TIMEx_PWMN_Start(motor_tim_handle,TIM_CHANNEL_2);

        break;
    }
    case HALL_PHASE_A2C:{
        HAL_TIM_PWM_Stop(motor_tim_handle,TIM_CHANNEL_2);
        HAL_TIMEx_PWMN_Stop(motor_tim_handle,TIM_CHANNEL_2);

        __HAL_TIM_SET_COMPARE(motor_tim_handle,TIM_CHANNEL_1,global_pwm_duty);
        HAL_TIM_PWM_Start(motor_tim_handle,TIM_CHANNEL_1);
        HAL_TIMEx_PWMN_Stop(motor_tim_handle,TIM_CHANNEL_1);

        __HAL_TIM_SET_COMPARE(motor_tim_handle,TIM_CHANNEL_3,MOTOR_TIM_PERIOD+1);
        HAL_TIM_PWM_Stop(motor_tim_handle,TIM_CHANNEL_3);
        HAL_TIMEx_PWMN_Start(motor_tim_handle,TIM_CHANNEL_3);

        break;
    }
    case HALL_PHASE_B2C:{
        HAL_TIM_PWM_Stop(motor_tim_handle,TIM_CHANNEL_1);
        HAL_TIMEx_PWMN_Stop(motor_tim_handle,TIM_CHANNEL_1);

        __HAL_TIM_SET_COMPARE(motor_tim_handle,TIM_CHANNEL_2,global_pwm_duty);
        HAL_TIM_PWM_Start(motor_tim_handle,TIM_CHANNEL_2);
        HAL_TIMEx_PWMN_Stop(motor_tim_handle,TIM_CHANNEL_2);

        __HAL_TIM_SET_COMPARE(motor_tim_handle,TIM_CHANNEL_3,MOTOR_TIM_PERIOD+1);
        HAL_TIM_PWM_Stop(motor_tim_handle,TIM_CHANNEL_3);
        HAL_TIMEx_PWMN_Start(motor_tim_handle,TIM_CHANNEL_3);

        break;
    }
    default:
        break;
    }
}

void MOTOR_Breaking_LowBridge(TIM_HandleTypeDef *motor_tim_handle){
    global_motorsta=MOTOR_STA_DISABLE;
    __HAL_TIM_SET_COMPARE(motor_tim_handle,TIM_CHANNEL_1,0);
    __HAL_TIM_SET_COMPARE(motor_tim_handle,TIM_CHANNEL_2,0);
    __HAL_TIM_SET_COMPARE(motor_tim_handle,TIM_CHANNEL_3,0);
    HAL_TIM_PWM_Start(motor_tim_handle,TIM_CHANNEL_1);
    HAL_TIM_PWM_Start(motor_tim_handle,TIM_CHANNEL_2);
    HAL_TIM_PWM_Start(motor_tim_handle,TIM_CHANNEL_3);
    HAL_TIMEx_PWMN_Start(motor_tim_handle,TIM_CHANNEL_1);
    HAL_TIMEx_PWMN_Start(motor_tim_handle,TIM_CHANNEL_2);
    HAL_TIMEx_PWMN_Start(motor_tim_handle,TIM_CHANNEL_3);
    HAL_TIM_GenerateEvent(motor_tim_handle,TIM_EVENTSOURCE_COM);

}

void MOTOR_Breaking_Inertia(void){
    MOTOR_DISABLE();
    global_motorsta=MOTOR_STA_DISABLE;
}

void MOTOR_Un_Breaking_LowBridge(TIM_HandleTypeDef *motor_tim_handle){
    HAL_TIM_PWM_Stop(motor_tim_handle,TIM_CHANNEL_1);
    HAL_TIM_PWM_Stop(motor_tim_handle,TIM_CHANNEL_2);
    HAL_TIM_PWM_Stop(motor_tim_handle,TIM_CHANNEL_3);
    HAL_TIMEx_PWMN_Stop(motor_tim_handle,TIM_CHANNEL_1);
    HAL_TIMEx_PWMN_Stop(motor_tim_handle,TIM_CHANNEL_2);
    HAL_TIMEx_PWMN_Stop(motor_tim_handle,TIM_CHANNEL_3);
    HAL_TIM_GenerateEvent(motor_tim_handle,TIM_EVENTSOURCE_COM);

}

void MOTOR_Start(TIM_HandleTypeDef *motor_tim_handle,TIM_HandleTypeDef *hall_sensor_tim_handle){
    uint8_t hall_current_phase;
    MOTOR_ENABLE();
    MOTOR_Breaking_LowBridge(motor_tim_handle);
    HAL_Delay(9);

    __HAL_TIM_CLEAR_FLAG(hall_sensor_tim_handle,TIM_FLAG_CC1);
    HAL_TIMEx_HallSensor_Start_IT(hall_sensor_tim_handle);

    hall_current_phase=HALLSENSOR_GetPhase();

    MOTOR_Control(motor_tim_handle,hall_current_phase);
    HAL_TIM_GenerateEvent(motor_tim_handle,TIM_EVENTSOURCE_COM);
    __HAL_TIM_CLEAR_FLAG(motor_tim_handle,TIM_FLAG_COM);

    global_motorsta=MOTOR_STA_ENABLE;

}

void MOTOR_SpeedControl(TIM_HandleTypeDef *motor_tim_handle,int32_t tim_control_val){
    uint32_t hall_current_phase=0;
    if(tim_control_val>(MOTOR_TIM_PERIOD-20)){
        tim_control_val=(MOTOR_TIM_PERIOD-20);
    }
    else if(tim_control_val<200){
        tim_control_val=200;
    }
    global_pwm_duty=tim_control_val;
    hall_current_phase=HALLSENSOR_GetPhase();
    if(MOTOR_DIR_CW==global_motordir){
        hall_current_phase=0x07^hall_current_phase;
    }
    switch (hall_current_phase)
    {
    case HALL_PHASE_B2A:{
        __HAL_TIM_SET_COMPARE(motor_tim_handle,TIM_CHANNEL_2,tim_control_val);
        break;
    }
    case HALL_PHASE_C2A:{
        __HAL_TIM_SET_COMPARE(motor_tim_handle,TIM_CHANNEL_3,tim_control_val);
        break;
    }
    case HALL_PHASE_C2B:{
        __HAL_TIM_SET_COMPARE(motor_tim_handle,TIM_CHANNEL_3,tim_control_val);
        break;
    }
    case HALL_PHASE_A2B:{
        __HAL_TIM_SET_COMPARE(motor_tim_handle,TIM_CHANNEL_1,tim_control_val);
        break;
    }
    case HALL_PHASE_A2C:{
        __HAL_TIM_SET_COMPARE(motor_tim_handle,TIM_CHANNEL_1,tim_control_val);
        break;
    }
    case HALL_PHASE_B2C:{
        __HAL_TIM_SET_COMPARE(motor_tim_handle,TIM_CHANNEL_2,tim_control_val);
        break;
    }
    default:
        break;
    }

}
