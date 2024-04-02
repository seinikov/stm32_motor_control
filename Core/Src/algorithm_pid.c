#include "main.h"
#include "algorithm_pid.h"

void PID_INC_Init(PID_INC_HandleTypedef *pid_obj,float32_t init_target,float32_t kp,float32_t ki,float32_t kd){
    pid_obj->err=0.f;
    pid_obj->err_last=0.f;
    pid_obj->err_before_last=0.f;
    pid_obj->control_val=0.f;
    pid_obj->target_val=init_target;
    pid_obj->Kp=kp;
    pid_obj->Ki=ki;
    pid_obj->Kd=kd;
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
