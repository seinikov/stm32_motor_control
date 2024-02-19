#include "main.h"
#include "arm_math.h"
#include "algorithm_pid.h"

float PID_INC_Process(PID_INC_Typedef *pid_obj,float32_t current_val){
    pid_obj->err=pid_obj->target_val-current_val;

    float32_t delta_val=pid_obj->Kp*(pid_obj->err-pid_obj->err_last)
                        +pid_obj->Ki*pid_obj->err
                        +pid_obj->Kd*(pid_obj->err-2*pid_obj->err_last+pid_obj->err_before_last);
    pid_obj->control_val+=delta_val;

    pid_obj->err_before_last=pid_obj->err_last;
    pid_obj->err_last=pid_obj->err;
    
    return pid_obj->control_val;
}
