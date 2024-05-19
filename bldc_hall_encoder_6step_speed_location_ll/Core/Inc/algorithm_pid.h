#ifndef __ALGORITHM_PID__
#define __ALGORITHM_PID__

#include "arm_math.h"

#define INNER_LOOP_INPUT_MAX    4000

#define PID_INTEGRAL_MAX        12000

typedef struct {
    float target_val;     //目标值
    float err;            //定义当前偏差值
    float err_last;       //定义上一个偏差值
    float Kp, Ki, Kd;     //定义比例、积分、微分系数
    float integral;       //积分值
    float control_val;    //控制值
} PID_LOC_HandleTypedef;

typedef struct {
    float32_t target_val;     
	float32_t err;
	float32_t err_last;
	float32_t err_before_last;
	float32_t Kp, Ki, Kd;
	float32_t control_val;
} PID_INC_HandleTypedef;

void PID_LOC_Init(PID_LOC_HandleTypedef *pid_obj,float32_t init_target,float32_t init_kp,float32_t init_ki,float32_t init_kd);

float PID_LOC_Process(PID_LOC_HandleTypedef *pid_obj,float current_val);

float PID_LOC_Cascaded_TwoLoops(PID_LOC_HandleTypedef *outer_loop_pid_obj,
                                PID_LOC_HandleTypedef *inner_loop_pid_obj,
                                float outer_back_val,float inner_back_val);

void PID_INC_Init(PID_INC_HandleTypedef *pid_obj,float32_t init_target,float32_t init_kp,float32_t init_ki,float32_t init_kd);

float PID_INC_Process(PID_INC_HandleTypedef *pid_obj,float32_t current_val);

#endif
