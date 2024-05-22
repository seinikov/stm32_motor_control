#include "main.h"
#include "math.h"
#include "tim.h"
#include "usart.h"
#include "bsp_hall.h"
#include "bsp_motor.h"
#include "algorithm_pid.h"
#include "protocol_uart_sei.h"
#include "debug.h"

extern uint8_t idleflag;
extern uint8_t global_motordir;
extern float32_t global_speed_set;
extern PID_LOC_HandleTypedef motor_speed_pid,motor_location_pid;
extern DMA_HandleTypeDef hdma_uart4_rx;
extern uint8_t uart_rx_buffer[UART_BUFFER_LEN];

void Protocol_UARTxRXProcess(void){
  if(1==idleflag){
    HAL_UART_DMAStop(&huart4);
    uint8_t rx_num=0;
    idleflag=0;
    rx_num=UART_BUFFER_LEN-__HAL_DMA_GET_COUNTER(&hdma_uart4_rx);
    if(7==rx_num){
#if MPU_DISABLE
      SCB_InvalidateDCache_by_Addr((uint8_t *)uart_rx_buffer,rx_num);
#endif
      if(0xC0==uart_rx_buffer[0]){
        uint8_t checksum=uart_rx_buffer[0];
        uint8_t counter;
        for(counter=1;counter<rx_num-1;counter++){
          checksum+=uart_rx_buffer[counter];
        }
        if(checksum==uart_rx_buffer[rx_num-1]){
          uint32_t temp_para=uart_rx_buffer[2]<<24|uart_rx_buffer[3]<<16|uart_rx_buffer[4]<<8|uart_rx_buffer[5];
          switch (uart_rx_buffer[1])
          {
          case CMD_SET_SPEED_PARA_TARGET:
          {
            if(0>roundf(*((float*)&temp_para)/60.f*PPR)){
              global_motordir=MOTOR_DIR_CCW;
            } else {
              global_motordir=MOTOR_DIR_CW;
            }
            motor_speed_pid.target_val=fabs(roundf(*((float*)&temp_para)/60.f*PPR));
            break;
          }
          case CMD_SET_SPEED_PARA_P:
          {
            motor_speed_pid.Kp=*((float*)&temp_para);
            break;
          }
          case CMD_SET_SPEED_PARA_I:
          {
            motor_speed_pid.Ki=*((float*)&temp_para);
            break;
          }
          case CMD_SET_SPEED_PARA_D:
          {
            motor_speed_pid.Kd=*((float*)&temp_para);
            break;
          }
          case CMD_SET_LOCATION_PARA_TARGET:
          {
            motor_location_pid.target_val=*((float*)&temp_para);
            break;
          }
          case CMD_SET_LOCATION_PARA_P:
          {
            motor_location_pid.Kp=*((float*)&temp_para);
            break;
          }
          case CMD_SET_LOCATION_PARA_I:
          {
            motor_location_pid.Ki=*((float*)&temp_para);
            break;
          }
          case CMD_SET_LOCATION_PARA_D:
          {
            motor_location_pid.Kd=*((float*)&temp_para);
            break;
          }
#if CONTROL_CONSTANT_SPEED
          case CMD_SET_MOTION_SPEED:
          {
            global_speed_set=*((float*)&temp_para);
            break;
          }
#endif
          default:
            break;
          }
        }
      }
    }
    for(uint8_t after_counter=0;after_counter<rx_num;after_counter++){
      uart_rx_buffer[after_counter]=0;
    }
    HAL_UART_Receive_DMA(&huart4,(uint8_t *)uart_rx_buffer,UART_BUFFER_LEN);
    return ;
  }
}
