/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.c
  * @brief          : Main program body
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2024 STMicroelectronics.
  * All rights reserved.
  *
  * This software is licensed under terms that can be found in the LICENSE file
  * in the root directory of this software component.
  * If no LICENSE file comes with this software, it is provided AS-IS.
  *
  ******************************************************************************
  */
/* USER CODE END Header */
/* Includes ------------------------------------------------------------------*/
#include "main.h"
#include "adc.h"
#include "dma.h"
#include "tim.h"
#include "usart.h"
#include "gpio.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include "bsp_motor.h"
#include "bsp_hall.h"
#include "observer_bemf.h"
#include "protocol_niming_upper.h"
#include "protocol_uart_sei.h"
#include "algorithm_pid.h"
#include "algorithm_filtering.h"
#include "math.h"
#include "debug.h"
/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */

/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */

/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/

/* USER CODE BEGIN PV */
MotorSta_Typedef global_motorsta;
MotorDir_Typedef global_motordir;
FOLPF_HandleTypeDef global_speed_hz;
PID_LOC_HandleTypedef motor_speed_pid;
uint32_t global_pwm_duty=500;
uint8_t global_state=0x00;
uint8_t uart_rx_buffer[UART_BUFFER_LEN];
UINT16_SINGLE_DATA_RING_BUFFER global_adc_bemf_u_buffer,global_adc_bemf_v_buffer,global_adc_bemf_w_buffer;
float32_t motor_control_val=0;
/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
void PeriphCommonClock_Config(void);
static void MPU_Config(void);
/* USER CODE BEGIN PFP */

/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */

/* USER CODE END 0 */

/**
  * @brief  The application entry point.
  * @retval int
  */
int main(void)
{

  /* USER CODE BEGIN 1 */

  /* USER CODE END 1 */

  /* MPU Configuration--------------------------------------------------------*/
  MPU_Config();

  /* Enable the CPU Cache */

  /* Enable I-Cache---------------------------------------------------------*/
  SCB_EnableICache();

  /* Enable D-Cache---------------------------------------------------------*/
  SCB_EnableDCache();

  /* MCU Configuration--------------------------------------------------------*/

  /* Reset of all peripherals, Initializes the Flash interface and the Systick. */
  HAL_Init();

  /* USER CODE BEGIN Init */

  /* USER CODE END Init */

  /* Configure the system clock */
  SystemClock_Config();

/* Configure the peripherals common clocks */
  PeriphCommonClock_Config();

  /* USER CODE BEGIN SysInit */
  SysTick_Config(SystemCoreClock/1000);

  LL_mDelay(200);

  /* USER CODE END SysInit */

  /* Initialize all configured peripherals */
  MX_GPIO_Init();
  MX_DMA_Init();
  MX_TIM1_Init();
  MX_ADC3_Init();
  MX_UART4_Init();
  MX_TIM3_Init();
  MX_TIM6_Init();
  /* USER CODE BEGIN 2 */
  
  // HALLSENSOR_TIMxStart(TIM3);
  global_motorsta=MOTOR_STA_DISABLE;
  
  FLOAT_FirstOrderLowPassFiltering_DataInit(&global_speed_hz,SPEED_HZ_FILTERING_ALPHA);
  UINT16_SINGLE_InitRingBuf(&global_adc_bemf_u_buffer);
  UINT16_SINGLE_InitRingBuf(&global_adc_bemf_v_buffer);
  UINT16_SINGLE_InitRingBuf(&global_adc_bemf_w_buffer);
  
  PID_LOC_Init(&motor_speed_pid,round(0./60.*PPR),0.75f,0.45f,0.f);

  __HAL_UART_ENABLE_IT(&huart4,UART_IT_IDLE);
  HAL_UART_Receive_DMA(&huart4,(uint8_t *)uart_rx_buffer,UART_BUFFER_LEN);
  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
  MOTOR_BEMFStart(TIM1);
  BEMF_ADCxStart(&hadc3);
  BEMF_TIMxStart(&htim6);

  // MOTOR_HallStart(TIM1,TIM3);
  while (1)
  {
    Protocol_UARTxRXProcess();

    if(GPIO_PIN_RESET==LL_GPIO_IsInputPinSet(KEY1_GPIO_Port,KEY1_Pin)){
      MOTOR_ENABLE();
      global_motorsta=MOTOR_STA_ENABLE;
    }
    
    if(GPIO_PIN_RESET==LL_GPIO_IsInputPinSet(KEY2_GPIO_Port,KEY2_Pin)){

#if BREAKING_INERTIA
      MOTOR_Breaking_Inertia();
#endif
      /*speed_duty or control_val must be zero when motor enable*/
      /********if not motor will shake while motor runing********/
      motor_control_val=0;
      MOTOR_SpeedControl(TIM1,round(motor_control_val));

      global_speed_hz.current_val = 0;
      global_speed_hz.last_val    = 0;
      motor_speed_pid.control_val = 0;
      motor_speed_pid.err         = 0;
      motor_speed_pid.err_last    = 0;
      motor_speed_pid.integral    = 0;
    }
#if 0
    if(global_state&0x01){
      global_speed_hz.current_val=HALLSENSOR_SpeedFrequency_Hz();
      FLOAT_FirstOrderLowPassFiltering_Process(&global_speed_hz);
      if(0==global_speed_hz.current_val){
        uint8_t hall_phase=0;
        hall_phase=HALLSENSOR_GetPhase();
        
#if BREAKING_INERTIA
        /*aim to phase when motor enable*/
        global_pwm_duty=30;
#endif  
        MOTOR_SixStepPhaseChange(TIM1,hall_phase);
        LL_TIM_GenerateEvent_COM(TIM1);
      }
      motor_control_val=PID_LOC_Process(&motor_speed_pid,global_speed_hz.current_val);
      MOTOR_SpeedControl(TIM1,round(motor_control_val));
      global_state&=~0x01;
    }
#endif    
    if(global_state&0x02){
      if(MOTOR_STA_DISABLE==global_motorsta){
        global_speed_hz.current_val=HALLSENSOR_SpeedFrequency_Hz();
        FLOAT_FirstOrderLowPassFiltering_Process(&global_speed_hz);
      }
      Protocol_NIMING_Mortor(&huart4,0xF1,global_speed_hz.current_val,global_speed_hz.current_val/PPR,(global_speed_hz.current_val/PPR)*60);
      global_state&=~0x02;
    }
    /* USER CODE END WHILE */

    /* USER CODE BEGIN 3 */
  }
  /* USER CODE END 3 */
}

/**
  * @brief System Clock Configuration
  * @retval None
  */
void SystemClock_Config(void)
{
  LL_FLASH_SetLatency(LL_FLASH_LATENCY_2);
  while(LL_FLASH_GetLatency()!= LL_FLASH_LATENCY_2)
  {
  }
  LL_PWR_ConfigSupply(LL_PWR_LDO_SUPPLY);
  LL_PWR_SetRegulVoltageScaling(LL_PWR_REGU_VOLTAGE_SCALE0);
  while (LL_PWR_IsActiveFlag_VOS() == 0)
  {
  }
  LL_RCC_HSE_Enable();

   /* Wait till HSE is ready */
  while(LL_RCC_HSE_IsReady() != 1)
  {

  }
  LL_RCC_PLL_SetSource(LL_RCC_PLLSOURCE_HSE);
  LL_RCC_PLL1P_Enable();
  LL_RCC_PLL1R_Enable();
  LL_RCC_PLL1_SetVCOInputRange(LL_RCC_PLLINPUTRANGE_8_16);
  LL_RCC_PLL1_SetVCOOutputRange(LL_RCC_PLLVCORANGE_WIDE);
  LL_RCC_PLL1_SetM(2);
  LL_RCC_PLL1_SetN(64);
  LL_RCC_PLL1_SetP(2);
  LL_RCC_PLL1_SetQ(2);
  LL_RCC_PLL1_SetR(2);
  LL_RCC_PLL1_Enable();

   /* Wait till PLL is ready */
  while(LL_RCC_PLL1_IsReady() != 1)
  {
  }

   /* Intermediate AHB prescaler 2 when target frequency clock is higher than 80 MHz */
   LL_RCC_SetAHBPrescaler(LL_RCC_AHB_DIV_2);

  LL_RCC_SetSysClkSource(LL_RCC_SYS_CLKSOURCE_PLL1);

   /* Wait till System clock is ready */
  while(LL_RCC_GetSysClkSource() != LL_RCC_SYS_CLKSOURCE_STATUS_PLL1)
  {

  }
  LL_RCC_SetSysPrescaler(LL_RCC_SYSCLK_DIV_1);
  LL_RCC_SetAHBPrescaler(LL_RCC_AHB_DIV_2);
  LL_RCC_SetAPB1Prescaler(LL_RCC_APB1_DIV_2);
  LL_RCC_SetAPB2Prescaler(LL_RCC_APB2_DIV_2);
  LL_RCC_SetAPB3Prescaler(LL_RCC_APB3_DIV_2);
  LL_RCC_SetAPB4Prescaler(LL_RCC_APB4_DIV_2);
  LL_SetSystemCoreClock(400000000);

   /* Update the time base */
  if (HAL_InitTick (TICK_INT_PRIORITY) != HAL_OK)
  {
    Error_Handler();
  }
}

/**
  * @brief Peripherals Common Clock Configuration
  * @retval None
  */
void PeriphCommonClock_Config(void)
{
  LL_RCC_PLL2P_Enable();
  LL_RCC_PLL2_SetVCOInputRange(LL_RCC_PLLINPUTRANGE_8_16);
  LL_RCC_PLL2_SetVCOOutputRange(LL_RCC_PLLVCORANGE_MEDIUM);
  LL_RCC_PLL2_SetM(2);
  LL_RCC_PLL2_SetN(12);
  LL_RCC_PLL2_SetP(6);
  LL_RCC_PLL2_SetQ(2);
  LL_RCC_PLL2_SetR(2);
  LL_RCC_PLL2_Enable();

   /* Wait till PLL is ready */
  while(LL_RCC_PLL2_IsReady() != 1)
  {
  }

}

/* USER CODE BEGIN 4 */

/* USER CODE END 4 */

 /* MPU Configuration */

void MPU_Config(void)
{

  /* Disables the MPU */
  LL_MPU_Disable();

  /** Initializes and configures the Region and the memory to be protected
  */
  LL_MPU_ConfigRegion(LL_MPU_REGION_NUMBER0, 0x00, 0x24000000, LL_MPU_REGION_SIZE_512KB|LL_MPU_TEX_LEVEL0|LL_MPU_REGION_FULL_ACCESS|LL_MPU_INSTRUCTION_ACCESS_ENABLE|LL_MPU_ACCESS_SHAREABLE|LL_MPU_ACCESS_CACHEABLE|LL_MPU_ACCESS_NOT_BUFFERABLE);
  /* Enables the MPU */
  LL_MPU_Enable(LL_MPU_CTRL_HFNMI_PRIVDEF);

}

/**
  * @brief  This function is executed in case of error occurrence.
  * @retval None
  */
void Error_Handler(void)
{
  /* USER CODE BEGIN Error_Handler_Debug */
  /* User can add his own implementation to report the HAL error return state */
  __disable_irq();
  while (1)
  {
  }
  /* USER CODE END Error_Handler_Debug */
}

#ifdef  USE_FULL_ASSERT
/**
  * @brief  Reports the name of the source file and the source line number
  *         where the assert_param error has occurred.
  * @param  file: pointer to the source file name
  * @param  line: assert_param error line source number
  * @retval None
  */
void assert_failed(uint8_t *file, uint32_t line)
{
  /* USER CODE BEGIN 6 */
  /* User can add his own implementation to report the file name and line number,
     ex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */
  /* USER CODE END 6 */
}
#endif /* USE_FULL_ASSERT */
