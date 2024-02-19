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
} PID_INC_Typedef;

#endif
