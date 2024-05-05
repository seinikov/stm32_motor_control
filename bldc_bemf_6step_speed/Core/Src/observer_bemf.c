#include "main.h" 
#include "adc.h"
#include "tim.h"
#include "data_ring_buffer.h"
#include "algorithm_filtering.h"
#include "bsp_motor.h"
#include "observer_bemf.h"

extern UINT16_SINGLE_DATA_RING_BUFFER global_adc_bemf_u_buffer,global_adc_bemf_v_buffer,global_adc_bemf_w_buffer;
extern MotorSta_Typedef global_motorsta;
extern MotorDir_Typedef global_motordir;

uint8_t hall_dir_cw [6] = {1,3,2,6,4,5};

void BEMF_TIMxStart(TIM_HandleTypeDef *htim)
{
    HAL_TIM_Base_Start_IT(htim);
}

void BEMF_ADCxStart(ADC_HandleTypeDef *hadc)
{
    HAL_ADC_Start(hadc);
    HAL_ADCEx_InjectedStart(hadc);
    HAL_ADCEx_InjectedStart_IT(hadc);
}

void HAL_ADCEx_InjectedConvCpltCallback(ADC_HandleTypeDef *hadc)
{
    UINT16_SINGLE_WriteIntoRingBuf(&global_adc_bemf_u_buffer,HAL_ADCEx_InjectedGetValue(hadc,ADC_INJECTED_RANK_1));
    UINT16_SINGLE_WriteIntoRingBuf(&global_adc_bemf_v_buffer,HAL_ADCEx_InjectedGetValue(hadc,ADC_INJECTED_RANK_2));
    UINT16_SINGLE_WriteIntoRingBuf(&global_adc_bemf_w_buffer,HAL_ADCEx_InjectedGetValue(hadc,ADC_INJECTED_RANK_3));
}

void BEMF_Process(UINT16_SINGLE_DATA_RING_BUFFER *which_bemf_buffer_process,ADC_HandleTypeDef *hadc)
{
    uint16_t bemf_val;
    HAL_ADC_Stop(hadc);
    HAL_ADCEx_InjectedStop(hadc);
    HAL_ADCEx_InjectedStop_IT(hadc);
    UINT16_SINGLE_AverageFiltering(&which_bemf_buffer_process,&bemf_val);
    UINT16_SINGLE_InitRingBuf(&which_bemf_buffer_process);
    HAL_ADC_Start(hadc);
    HAL_ADCEx_InjectedStart(hadc);
    HAL_ADCEx_InjectedStart_IT(hadc);
}

void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim)
{
    static uint8_t phase_counter=0;
    if(htim==&htim6){
        if(phase_counter>5){
            phase_counter=0;
        }
        MOTOR_SixStepPhaseChange(TIM1,hall_dir_cw[phase_counter]);
        phase_counter++;
    }
}
