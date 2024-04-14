#include "main.h"
#include "arm_math.h"
#include "algorithm_spwm.h"

#define PI_X2           (2.0f*PI)    // 2π
#define PI_X2_DIV3      (PI_X2/3.0f) // (2/3)π


// 定时器半周期
#define  TIM_HALF_PERIOD       (float)((ADVANCED_TIM_PERIOD+1)/2)
// 载波(三角波)频率 ,用于计算的数值,非设定值
#define  CARRIER_FREQ_Hz       (float)(1.68e8/(ADVANCED_TIM_PRESCALER+1))/(2*(ADVANCED_TIM_PERIOD+1))// 定时器脉冲频率

/* 根据实际需求调整频率和幅值 */
// 调制波频率  // 本例程可调范围是10~210Hz,如果需要其他范围的频率，需要调整载波比
#define  MODULATED_FREQ_Hz     20.0f  // 调制波形(正弦波)频率
// 调制比 输出波形电压幅值与直流电压幅值之比 0< r <100
#define  MODULATION_RATIO      20.0f   //

/* 私有变量 ------------------------------------------------------------------*/
float UVPhase      = PI_X2_DIV3;  // UV相位差
float UWPhase      = -PI_X2_DIV3; // UW相位差
float Modulation   = 400;         // 载波比  // 载波比 R = 载波频率/调制波频率
float Amplitude    = 0;           // 调制比  // 0< Amplitude <1
float Pi_divN      = 0;           // 常数
float  Volt_Freq   = 1;           // V/F 控制参数 电压/频率 实际上是 调制比/频率
int32_t Accel      = 1;           // 加速度

void SPWM_Modulation(TIM_HandleTypeDef *htim,SPWM_HandelTypedef *spwm_obj,float32_t frequence){
    if(frequence>0.f){
        spwm_obj->vpp_percent=frequence*spwm_obj->voltage_div_frequence;
        if(spwm_obj->vpp_percent>100.f){
            spwm_obj->vpp_percent=100.f;
        }
        spwm_obj->modulation_ration=spwm_obj->vpp_percent/100.f;
        spwm_obj->carrier_ration=(1.68e8/(htim->Init.Prescaler+1))/(2*(htim->Init.Period+1));
        spwm_obj->PI_divN=PI_X2/Modulation;
        spwm_obj->UV_phase=+PI_X2_DIV3;
        spwm_obj->UW_phase=-PI_X2_DIV3;
    }
    else if(frequence<0.0f){
        frequence=-frequence;
        if(spwm_obj->vpp_percent>100.f){
            spwm_obj->vpp_percent=100.f;
        }
        spwm_obj->modulation_ration=spwm_obj->vpp_percent/100.f;
        spwm_obj->carrier_ration=(1.68e8/(htim->Init.Prescaler+1))/(2*(htim->Init.Period+1));
        spwm_obj->PI_divN=PI_X2/Modulation;
        spwm_obj->UV_phase=-PI_X2_DIV3;
        spwm_obj->UW_phase=+PI_X2_DIV3;
    }
    else {
        spwm_obj->modulation_ration=0;
        spwm_obj->PI_divN=0;
    }
}
