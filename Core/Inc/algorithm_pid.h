#ifndef __ALGORITHM_PID__
#define __ALGORITHM_PID__

#include "arm_math.h"

typedef struct {
    float32_t target_val;     
	float32_t err;
	float32_t err_last;
	float32_t err_before_last;
	float32_t Kp, Ki, Kd;
	float32_t control_val;
} PID_INC_HandleTypedef;

void PID_INC_Init(PID_INC_HandleTypedef *pid_obj,float32_t init_target,float32_t kp,float32_t ki,float32_t kd);

float PID_INC_Process(PID_INC_HandleTypedef *pid_obj,float32_t current_val);

#endif
