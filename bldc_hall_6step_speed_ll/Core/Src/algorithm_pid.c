#include "main.h"
#include "algorithm_pid.h"

void PID_LOC_Init(PID_LOC_HandleTypedef *pid_obj,float32_t init_target,float32_t init_kp,float32_t init_ki,float32_t init_kd){
    pid_obj->err=0.f;
    pid_obj->err_last=0.f;
    pid_obj->control_val=0.f;
    pid_obj->target_val=init_target;
    pid_obj->Kp=init_kp;
    pid_obj->Ki=init_ki;
    pid_obj->Kd=init_kd;
}

float PID_LOC_Process(PID_LOC_HandleTypedef *pid_obj,float current_val){
    pid_obj->err=pid_obj->target_val-current_val;
    pid_obj->integral+=pid_obj->err;

    /*积分器抗饱和超调*/
    /*需要仿真验证理论*/
    if(pid_obj->integral>12000){
        pid_obj->integral=12000;
    }
    
    pid_obj->control_val = pid_obj->Kp*pid_obj->err
                        + pid_obj->Ki*pid_obj->integral
                        + pid_obj->Kd*(pid_obj->err-pid_obj->err_last);
    
    pid_obj->err_last=pid_obj->err;
    
    return pid_obj->control_val;
}

void PID_INC_Init(PID_INC_HandleTypedef *pid_obj,float32_t init_target,float32_t init_kp,float32_t init_ki,float32_t init_kd){
    pid_obj->err=0.f;
    pid_obj->err_last=0.f;
    pid_obj->err_before_last=0.f;
    pid_obj->control_val=0.f;
    pid_obj->target_val=init_target;
    pid_obj->Kp=init_kp;
    pid_obj->Ki=init_ki;
    pid_obj->Kd=init_kd;
}

float PID_INC_Process(PID_INC_HandleTypedef *pid_obj,float32_t current_val){
    pid_obj->err=pid_obj->target_val-current_val;

    float32_t delta_val=pid_obj->Kp*(pid_obj->err-pid_obj->err_last)
                        +pid_obj->Ki*pid_obj->err
                        +pid_obj->Kd*(pid_obj->err-2*pid_obj->err_last+pid_obj->err_before_last);
    pid_obj->control_val+=delta_val;

    pid_obj->err_before_last=pid_obj->err_last;
    pid_obj->err_last=pid_obj->err;
    
    return pid_obj->control_val;
}
