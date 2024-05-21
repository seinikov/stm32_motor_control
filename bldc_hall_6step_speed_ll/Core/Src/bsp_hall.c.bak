#include "main.h"
#include "bsp_motor.h"
#include "bsp_hall.h"
#include "bsp_motor.h"
#include "tim.h"
#include "debug.h"

uint8_t hall_current_phase=0,hall_last_pahse=0;
uint8_t hall_dir=MOTOR_DIR_CW;
uint8_t hall_dir_ccw [7] = {0, 3, 6, 2, 5, 1, 4};
extern MotorSta_Typedef global_motorsta;
extern MotorDir_Typedef global_motordir;

uint32_t hall_compare;
uint32_t hall_count;

void HALLSENSOR_TIMxStart(TIM_TypeDef *HALL_TIMx)
{
    LL_TIM_EnableIT_CC1(HALL_TIMx);
    LL_TIM_CC_EnableChannel(HALL_TIMx,LL_TIM_CHANNEL_CH1);
    LL_TIM_EnableCounter(HALL_TIMx);

    hall_current_phase=hall_last_pahse;
}

uint8_t HALLSENSOR_GetPhase(void){
    uint8_t phase=0;
    phase |= LL_GPIO_IsInputPinSet(HALL_U_GPIO_Port,HALL_U_Pin);
    phase <<= 1;
    phase |= LL_GPIO_IsInputPinSet(HALL_V_GPIO_Port,HALL_V_Pin);
    phase <<= 1;
    phase |= LL_GPIO_IsInputPinSet(HALL_W_GPIO_Port,HALL_W_Pin);
    return (phase&0x07);
}

void HALLSENSOR_TIMxIRQCallback(TIM_TypeDef *HALL_TIMx)
{
    LL_TIM_ClearFlag_CC1(HALL_TIMx);

    hall_current_phase=HALLSENSOR_GetPhase();
    if(global_motorsta==MOTOR_STA_ENABLE){
        MOTOR_SixStepPhaseChange(TIM1,hall_current_phase);
    }
    hall_compare+=LL_TIM_OC_GetCompareCH1(HALL_TIMx);
    hall_count++;
    if(hall_dir_ccw[hall_current_phase]==hall_last_pahse){
        hall_dir=MOTOR_DIR_CCW;
    }
    else{
        hall_dir=MOTOR_DIR_CW;
    }
    hall_last_pahse=hall_current_phase;
}

float HALLSENSOR_SpeedFrequency_Hz(void){
    float compare_pre_time=0;
    if((0==hall_count)|(0==hall_compare)){
        return 0;
    }
    else{
        compare_pre_time=(float)hall_compare/(float)hall_count;
        hall_compare=0;
        hall_count=0;
        return ((float)HALL_TIM_FREQ/compare_pre_time);
    }
}
