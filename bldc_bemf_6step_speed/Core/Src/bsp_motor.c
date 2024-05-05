#include "main.h"
#include "tim.h"
#include "bsp_motor.h"
#include "bsp_hall.h"
#include "debug.h"

extern MotorSta_Typedef global_motorsta;
extern MotorDir_Typedef global_motordir;
extern uint32_t global_pwm_duty;

void MOTOR_TIMxDriveOutConfigInit(TIM_TypeDef *TIMx)
{
    LL_TIM_SetSlaveMode(TIMx,LL_TIM_TS_ITR2);
    LL_TIM_CC_SetUpdate(TIMx,LL_TIM_CCUPDATESOURCE_COMG_AND_TRGI);
}

void MOTOR_Init(MotorDir_Typedef *obj_dir,MotorSta_Typedef *obj_sta,MotorDir_Typedef dir_choice)
{
    global_motorsta=MOTOR_STA_DISABLE;
    global_motordir=dir_choice;
}

void MOTOR_SixStepPhaseChange(TIM_TypeDef *TIMx,uint8_t bemf_phase)
{
    if(MOTOR_DIR_CW==global_motordir){
        bemf_phase=0x07^bemf_phase;
    }
    switch (bemf_phase)
    {
    case HALL_PHASE_B2A:{
        LL_TIM_CC_DisableChannel(TIMx,LL_TIM_CHANNEL_CH1);
        LL_TIM_CC_DisableChannel(TIMx,LL_TIM_CHANNEL_CH2N);
        LL_TIM_CC_DisableChannel(TIMx,LL_TIM_CHANNEL_CH3);
        LL_TIM_CC_DisableChannel(TIMx,LL_TIM_CHANNEL_CH3N);

        LL_TIM_DisableAllOutputs(TIMx);
        LL_TIM_DisableCounter(TIMx);
        

        LL_TIM_OC_SetCompareCH2(TIMx,global_pwm_duty);
        LL_TIM_OC_SetCompareCH1(TIMx,TIMx->ARR);

        LL_TIM_CC_EnableChannel(TIMx,LL_TIM_CHANNEL_CH2);
        LL_TIM_CC_EnableChannel(TIMx,LL_TIM_CHANNEL_CH1N);

        LL_TIM_EnableAllOutputs(TIMx);
        LL_TIM_EnableCounter(TIMx);

        break;
    }
    case HALL_PHASE_C2A:{
        LL_TIM_CC_DisableChannel(TIMx,LL_TIM_CHANNEL_CH1);
        LL_TIM_CC_DisableChannel(TIMx,LL_TIM_CHANNEL_CH2);
        LL_TIM_CC_DisableChannel(TIMx,LL_TIM_CHANNEL_CH2N);
        LL_TIM_CC_DisableChannel(TIMx,LL_TIM_CHANNEL_CH3N);
        
        LL_TIM_DisableAllOutputs(TIMx);
        LL_TIM_DisableCounter(TIMx);
        

        LL_TIM_OC_SetCompareCH3(TIMx,global_pwm_duty);
        LL_TIM_OC_SetCompareCH1(TIMx,TIMx->ARR);

        LL_TIM_CC_EnableChannel(TIMx,LL_TIM_CHANNEL_CH3);
        LL_TIM_CC_EnableChannel(TIMx,LL_TIM_CHANNEL_CH1N);

        LL_TIM_EnableAllOutputs(TIMx);
        LL_TIM_EnableCounter(TIMx);

        break;
    }
    case HALL_PHASE_C2B:{
        LL_TIM_CC_DisableChannel(TIMx,LL_TIM_CHANNEL_CH1);
        LL_TIM_CC_DisableChannel(TIMx,LL_TIM_CHANNEL_CH1N);
        LL_TIM_CC_DisableChannel(TIMx,LL_TIM_CHANNEL_CH2);
        LL_TIM_CC_DisableChannel(TIMx,LL_TIM_CHANNEL_CH3N);
        
        LL_TIM_DisableAllOutputs(TIMx);
        LL_TIM_DisableCounter(TIMx);
        

        LL_TIM_OC_SetCompareCH3(TIMx,global_pwm_duty);
        LL_TIM_OC_SetCompareCH2(TIMx,TIMx->ARR);

        LL_TIM_CC_EnableChannel(TIMx,LL_TIM_CHANNEL_CH3);
        LL_TIM_CC_EnableChannel(TIMx,LL_TIM_CHANNEL_CH2N);

        LL_TIM_EnableAllOutputs(TIMx);
        LL_TIM_EnableCounter(TIMx);

        break;
    }
    case HALL_PHASE_A2B:{
        LL_TIM_CC_DisableChannel(TIMx,LL_TIM_CHANNEL_CH1N);
        LL_TIM_CC_DisableChannel(TIMx,LL_TIM_CHANNEL_CH2);
        LL_TIM_CC_DisableChannel(TIMx,LL_TIM_CHANNEL_CH3);
        LL_TIM_CC_DisableChannel(TIMx,LL_TIM_CHANNEL_CH3N);
        
        LL_TIM_DisableAllOutputs(TIMx);
        LL_TIM_DisableCounter(TIMx);
        

        LL_TIM_OC_SetCompareCH1(TIMx,global_pwm_duty);
        LL_TIM_OC_SetCompareCH2(TIMx,TIMx->ARR);

        LL_TIM_CC_EnableChannel(TIMx,LL_TIM_CHANNEL_CH1);
        LL_TIM_CC_EnableChannel(TIMx,LL_TIM_CHANNEL_CH2N);

        LL_TIM_EnableAllOutputs(TIMx);
        LL_TIM_EnableCounter(TIMx);

        break;
    }
    case HALL_PHASE_A2C:{
        LL_TIM_CC_DisableChannel(TIMx,LL_TIM_CHANNEL_CH1N);
        LL_TIM_CC_DisableChannel(TIMx,LL_TIM_CHANNEL_CH2);
        LL_TIM_CC_DisableChannel(TIMx,LL_TIM_CHANNEL_CH2N);
        LL_TIM_CC_DisableChannel(TIMx,LL_TIM_CHANNEL_CH3);
        
        LL_TIM_DisableAllOutputs(TIMx);
        LL_TIM_DisableCounter(TIMx);
        

        LL_TIM_OC_SetCompareCH1(TIMx,global_pwm_duty);
        LL_TIM_OC_SetCompareCH3(TIMx,TIMx->ARR);

        LL_TIM_CC_EnableChannel(TIMx,LL_TIM_CHANNEL_CH1);
        LL_TIM_CC_EnableChannel(TIMx,LL_TIM_CHANNEL_CH3N);

        LL_TIM_EnableAllOutputs(TIMx);
        LL_TIM_EnableCounter(TIMx);

        break;
    }
    case HALL_PHASE_B2C:{
        LL_TIM_CC_DisableChannel(TIMx,LL_TIM_CHANNEL_CH1);
        LL_TIM_CC_DisableChannel(TIMx,LL_TIM_CHANNEL_CH1N);
        LL_TIM_CC_DisableChannel(TIMx,LL_TIM_CHANNEL_CH2N);
        LL_TIM_CC_DisableChannel(TIMx,LL_TIM_CHANNEL_CH3);

        
        LL_TIM_DisableAllOutputs(TIMx);
        LL_TIM_DisableCounter(TIMx);
        

        LL_TIM_OC_SetCompareCH2(TIMx,global_pwm_duty);
        LL_TIM_OC_SetCompareCH3(TIMx,TIMx->ARR);

        LL_TIM_CC_EnableChannel(TIMx,LL_TIM_CHANNEL_CH2);
        LL_TIM_CC_EnableChannel(TIMx,LL_TIM_CHANNEL_CH3N);

        LL_TIM_EnableAllOutputs(TIMx);
        LL_TIM_EnableCounter(TIMx);

        break;
    }
    default:
        break;
    }
}

void MOTOR_Breaking_LowBridge(TIM_TypeDef *TIMx)
{
    global_motorsta=MOTOR_STA_DISABLE;
    
    LL_TIM_OC_SetCompareCH1(TIMx,0);
    LL_TIM_OC_SetCompareCH2(TIMx,0);
    LL_TIM_OC_SetCompareCH3(TIMx,0);
    
    LL_TIM_CC_EnableChannel(TIMx,LL_TIM_CHANNEL_CH1);
    LL_TIM_CC_EnableChannel(TIMx,LL_TIM_CHANNEL_CH2);
    LL_TIM_CC_EnableChannel(TIMx,LL_TIM_CHANNEL_CH3);
    LL_TIM_CC_EnableChannel(TIMx,LL_TIM_CHANNEL_CH1N);
    LL_TIM_CC_EnableChannel(TIMx,LL_TIM_CHANNEL_CH2N);
    LL_TIM_CC_EnableChannel(TIMx,LL_TIM_CHANNEL_CH3N);
    
    LL_TIM_EnableCounter(TIMx);
    LL_TIM_EnableAllOutputs(TIMx);
    
    LL_TIM_GenerateEvent_COM(TIMx);
}

void MOTOR_Breaking_Inertia(void)
{
    MOTOR_DISABLE();
    global_motorsta=MOTOR_STA_DISABLE;
}

void MOTOR_Un_Breaking_LowBridge(TIM_TypeDef *TIMx)
{
    LL_TIM_CC_DisableChannel(TIMx,LL_TIM_CHANNEL_CH1);
    LL_TIM_CC_DisableChannel(TIMx,LL_TIM_CHANNEL_CH2);
    LL_TIM_CC_DisableChannel(TIMx,LL_TIM_CHANNEL_CH3);
    LL_TIM_CC_DisableChannel(TIMx,LL_TIM_CHANNEL_CH1N);
    LL_TIM_CC_DisableChannel(TIMx,LL_TIM_CHANNEL_CH2N);
    LL_TIM_CC_DisableChannel(TIMx,LL_TIM_CHANNEL_CH3N);
    
    LL_TIM_GenerateEvent_COM(TIMx);
}

void MOTOR_HallStart(TIM_TypeDef *MOTOR_TIMx,TIM_TypeDef *HALL_TIMx)
{
    uint8_t hall_current_phase;
    MOTOR_ENABLE();
    MOTOR_Breaking_LowBridge(MOTOR_TIMx);
    LL_mDelay(9);

    LL_TIM_ClearFlag_CC1(HALL_TIMx);
    LL_TIM_EnableIT_CC1(HALL_TIMx);
    LL_TIM_CC_EnableChannel(HALL_TIMx,LL_TIM_CHANNEL_CH1);
    LL_TIM_EnableCounter(HALL_TIMx);

    hall_current_phase=HALLSENSOR_GetPhase();

    MOTOR_SixStepPhaseChange(MOTOR_TIMx,hall_current_phase);

    LL_TIM_GenerateEvent_COM(MOTOR_TIMx);
    LL_TIM_ClearFlag_COM(MOTOR_TIMx);

    global_motorsta=MOTOR_STA_ENABLE;

}

void MOTOR_SpeedControl(TIM_TypeDef *TIMx,int32_t tim_control_val)
{
    uint32_t hall_current_phase=0;
    
    if(tim_control_val>TIMx->ARR){
        tim_control_val=TIMx->ARR;
    }else if(tim_control_val<0){
        tim_control_val=0;
    }
    global_pwm_duty=tim_control_val;
    
    hall_current_phase=HALLSENSOR_GetPhase();
    if(MOTOR_DIR_CW==global_motordir){
        hall_current_phase=0x07^hall_current_phase;
    }
    
    switch (hall_current_phase)
    {
    case HALL_PHASE_B2A:{
        LL_TIM_OC_SetCompareCH2(TIMx,global_pwm_duty);
        break;
    }
    case HALL_PHASE_C2A:{
        LL_TIM_OC_SetCompareCH3(TIMx,global_pwm_duty);
        break;
    }
    case HALL_PHASE_C2B:{
        LL_TIM_OC_SetCompareCH3(TIMx,global_pwm_duty);
        break;
    }
    case HALL_PHASE_A2B:{
        LL_TIM_OC_SetCompareCH1(TIMx,global_pwm_duty);
        break;
    }
    case HALL_PHASE_A2C:{
        LL_TIM_OC_SetCompareCH1(TIMx,global_pwm_duty);
        break;
    }
    case HALL_PHASE_B2C:{
        LL_TIM_OC_SetCompareCH2(TIMx,global_pwm_duty);
        break;
    }
    default:
        break;
    }
}

void MOTOR_BEMFStart(TIM_TypeDef *MOTOR_TIMx)
{
    MOTOR_ENABLE();
    MOTOR_Breaking_LowBridge(MOTOR_TIMx);
    LL_mDelay(9);

    MOTOR_SixStepPhaseChange(MOTOR_TIMx,HALL_PHASE_B2A);

    LL_TIM_GenerateEvent_COM(MOTOR_TIMx);
    LL_TIM_ClearFlag_COM(MOTOR_TIMx);

    global_motorsta=MOTOR_STA_ENABLE;

}
