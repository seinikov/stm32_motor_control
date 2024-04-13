#ifndef __DEBUG_H__
#define __DEBUG_H__

#include "bsp_motor.h"

#define MOTOR_INIT_DIR MOTOR_DIR_CW

#define SPEED_HZ_FILTERING_ALPHA 0.8f

#define BREAKING_LOWBRIDGE       0
#define BREAKING_INERTIA         !BREAKING_LOWBRIDGE

#define MPU_ENABLE               1
#define MPU_DISABLE              !MPU_ENABLE

#endif
