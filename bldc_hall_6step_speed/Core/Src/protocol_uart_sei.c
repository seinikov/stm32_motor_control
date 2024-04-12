#include "main.h"
#include "tim.h"
#include "usart.h"
#include "bsp_hall.h"
#include "algorithm_pid.h"
#include "protocol_uart_sei.h"

extern uint8_t idleflag;
extern PID_LOC_HandleTypedef motor_speed_pid;
extern DMA_HandleTypeDef hdma_uart4_rx;
extern uint8_t uart_rx_buffer[UART_BUFFER_LEN];

void Protocol_UARTxRXProcess(void){
  if(1==idleflag){
    HAL_UART_DMAStop(&huart4);
    uint8_t rx_num=0;
    idleflag=0;
    rx_num=UART_BUFFER_LEN-__HAL_DMA_GET_COUNTER(&hdma_uart4_rx);
    if(7==rx_num){
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
          case CMD_SET_PARA_TARGET:
          {
            motor_speed_pid.target_val=roundf(*((float*)&temp_para)/60.f*PPR);
            break;
          }
          case CMD_SET_PARA_P:
          {
            motor_speed_pid.Kp=*((float*)&temp_para);
            break;
          }
          case CMD_SET_PARA_I:
          {
            motor_speed_pid.Ki=*((float*)&temp_para);
            break;
          }
          case CMD_SET_PARA_D:
          {
            motor_speed_pid.Kd=*((float*)&temp_para);
            break;
          }
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
