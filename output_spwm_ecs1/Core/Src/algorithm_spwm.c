#include "main.h"
#include "tim.h"
#include "math.h"
#include "algorithm_spwm.h"

extern SPWM_HandelTypedef global_spwm;

void SPWM_ParaInit(SPWM_HandelTypedef *spwm_obj,
                float32_t carrier_ration,float32_t modulation_ration,float32_t PI_divN,
                float32_t UV_phase,float32_t UW_phase,float32_t voltage_div_frequence){
    spwm_obj->carrier_ration=carrier_ration;
    spwm_obj->modulation_ration=modulation_ration;
    spwm_obj->PI_divN=PI_divN;
    spwm_obj->UV_phase=UV_phase;
    spwm_obj->UW_phase=UW_phase;
    spwm_obj->voltage_div_frequence=voltage_div_frequence;
}

void SPWM_Modulation(TIM_TypeDef *TIMx,SPWM_HandelTypedef *spwm_obj,float32_t frequence){
    if(frequence>0.f){
        spwm_obj->vpp_percent=frequence*spwm_obj->voltage_div_frequence;
        if(spwm_obj->vpp_percent>100.f){
            spwm_obj->vpp_percent=100.f;
        }
        spwm_obj->modulation_ration=spwm_obj->vpp_percent/100.f;
        spwm_obj->carrier_ration=((1.68e8/(TIMx->PSC+1))/(2*(TIMx->ARR+1)))/frequence;
        spwm_obj->PI_divN=PI_X2/spwm_obj->carrier_ration;
        spwm_obj->UV_phase=+PI_X2_DIV3;
        spwm_obj->UW_phase=-PI_X2_DIV3;
    }
    else if(frequence<0.0f){
        frequence=-frequence;
        spwm_obj->vpp_percent=frequence*spwm_obj->voltage_div_frequence;
        if(spwm_obj->vpp_percent>100.f){
            spwm_obj->vpp_percent=100.f;
        }
        spwm_obj->modulation_ration=spwm_obj->vpp_percent/100.f;
        spwm_obj->carrier_ration=((1.68e8/(TIMx->PSC+1))/(2*(TIMx->ARR+1)))/frequence;
        spwm_obj->PI_divN=PI_X2/spwm_obj->carrier_ration;
        spwm_obj->UV_phase=-PI_X2_DIV3;
        spwm_obj->UW_phase=+PI_X2_DIV3;
    }
    else {
        spwm_obj->carrier_ration=0;
        spwm_obj->PI_divN=0;
    }
}

void SPWM_Start(TIM_TypeDef *TIMx,SPWM_HandelTypedef *spwm_obj){
    uint16_t ccr2=0;
    uint16_t ccr3=0;

    ccr2=((TIMx->ARR+1)/2)*(1.f+MODULATION_RATIO*(sinf(spwm_obj->UV_phase)));
    ccr3=((TIMx->ARR+1)/2)*(1.f+MODULATION_RATIO*(sinf(spwm_obj->UW_phase)));

    LL_TIM_EnableAllOutputs(TIMx);
    LL_TIM_EnableCounter(TIMx);

    LL_TIM_OC_SetCompareCH1(TIMx,((TIMx->ARR+1)/2));
    LL_TIM_OC_SetCompareCH2(TIMx,ccr2);
    LL_TIM_OC_SetCompareCH3(TIMx,ccr3);

    LL_TIM_GenerateEvent_UPDATE(TIMx);
    LL_TIM_ClearFlag_UPDATE(TIMx);

    LL_TIM_EnableIT_UPDATE(TIMx);

    LL_TIM_CC_EnableChannel(TIMx,LL_TIM_CHANNEL_CH1);
    LL_TIM_CC_EnableChannel(TIMx,LL_TIM_CHANNEL_CH2);
    LL_TIM_CC_EnableChannel(TIMx,LL_TIM_CHANNEL_CH3);
    LL_TIM_CC_EnableChannel(TIMx,LL_TIM_CHANNEL_CH1N);
    LL_TIM_CC_EnableChannel(TIMx,LL_TIM_CHANNEL_CH2N);
    LL_TIM_CC_EnableChannel(TIMx,LL_TIM_CHANNEL_CH3N);

    SPWM_TIMxIRQCallback(TIMx,spwm_obj);
}

void SPWM_TIMxIRQCallback(TIM_TypeDef *TIMx,SPWM_HandelTypedef *spwm_obj){
    uint32_t ccr1=0;
    uint32_t ccr2=0;
    uint32_t ccr3=0;
    static float32_t i=1.f;
    
    float32_t tmp=spwm_obj->PI_divN*i;
    ccr1=(float32_t)((TIMx->ARR+1)/2)*(global_spwm.modulation_ration+global_spwm.modulation_ration*sinf(tmp));
    ccr2=(float32_t)((TIMx->ARR+1)/2)*(global_spwm.modulation_ration+global_spwm.modulation_ration*sinf(tmp+global_spwm.UV_phase));
    ccr3=(float32_t)((TIMx->ARR+1)/2)*(global_spwm.modulation_ration+global_spwm.modulation_ration*sinf(tmp+global_spwm.UW_phase));

    LL_TIM_OC_SetCompareCH1(TIMx,ccr1);
    LL_TIM_OC_SetCompareCH2(TIMx,ccr2);
    LL_TIM_OC_SetCompareCH3(TIMx,ccr3);
    
    i++;
    if(i>=global_spwm.carrier_ration){
        i=0;
    }
}

