/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.c
  * @brief          : Main program body
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2022 STMicroelectronics.
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
#include "tim.h"
#include "gpio.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */

/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */

/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */
	#define T0 0
	#define T1 125
	#define T2 500
	#define T3 625
	
	#define Shift_Second 125
	#define Shift_Third 250
	#define Shift_Fourth 375
	
	#define Cycle_Length 1000
	#define Max_PWM 1000
	#define Min_PWM 0	

/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/

/* USER CODE BEGIN PV */
	uint16_t steps_first[1000] = {0};
	uint16_t Steps_Second[1000] = {0};
	uint16_t Steps_Third[1000] = {0};
	uint16_t Steps_Fourth[1000] = {0};
		
	uint16_t index = 0;
	uint16_t coefficient = 0;
	
	GPIO_PinState button_state = GPIO_PIN_RESET;
/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
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

  /* MCU Configuration--------------------------------------------------------*/

  /* Reset of all peripherals, Initializes the Flash interface and the Systick. */
  HAL_Init();

  /* USER CODE BEGIN Init */

  /* USER CODE END Init */

  /* Configure the system clock */
  SystemClock_Config();

  /* USER CODE BEGIN SysInit */

  /* USER CODE END SysInit */

  /* Initialize all configured peripherals */
  MX_GPIO_Init();
  MX_TIM4_Init();
  /* USER CODE BEGIN 2 */
	HAL_TIM_Base_Start_IT(&htim4);
	HAL_TIM_PWM_Start(&htim4, TIM_CHANNEL_1);
	HAL_TIM_PWM_Start(&htim4, TIM_CHANNEL_2);
	HAL_TIM_PWM_Start(&htim4, TIM_CHANNEL_3);
	HAL_TIM_PWM_Start(&htim4, TIM_CHANNEL_4);
	
	coefficient = (Max_PWM - Min_PWM)/(T1 - T0);
	for(int i = T0; i < Cycle_Length; i++)
		{					
			if(i < T1)
				{					
					steps_first[i] = i * coefficient;					
				} 
				else if (i < T2)
					{
					steps_first[i] = Max_PWM;	
					}
					
				else if(i < T3)
					{
						steps_first[i] = Max_PWM - (i - T2) * (coefficient);
					}
					
				else
					{
						steps_first[i] = Min_PWM;
					}
		}
		
	for (int i = 0; i < Cycle_Length; i++)
		{
			int j = i + Shift_Second;
			if (j >= Cycle_Length) j = j - 1000;
			Steps_Second[j] = steps_first[i];
			
			j = i + Shift_Third;
			if (j >= Cycle_Length) j = j - 1000;
			Steps_Third[j] = steps_first[i];
			
			j = i + Shift_Fourth;
			if (j >= Cycle_Length) j = j - 1000;
			Steps_Fourth[j] = steps_first[i];			
		}

	
  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
  while (1)
  {
		
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
  RCC_OscInitTypeDef RCC_OscInitStruct = {0};
  RCC_ClkInitTypeDef RCC_ClkInitStruct = {0};

  /** Configure the main internal regulator output voltage
  */
  __HAL_RCC_PWR_CLK_ENABLE();
  __HAL_PWR_VOLTAGESCALING_CONFIG(PWR_REGULATOR_VOLTAGE_SCALE1);

  /** Initializes the RCC Oscillators according to the specified parameters
  * in the RCC_OscInitTypeDef structure.
  */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSI;
  RCC_OscInitStruct.HSIState = RCC_HSI_ON;
  RCC_OscInitStruct.HSICalibrationValue = RCC_HSICALIBRATION_DEFAULT;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_NONE;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    Error_Handler();
  }

  /** Initializes the CPU, AHB and APB buses clocks
  */
  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
                              |RCC_CLOCKTYPE_PCLK1|RCC_CLOCKTYPE_PCLK2;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_HSI;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV1;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_0) != HAL_OK)
  {
    Error_Handler();
  }
}

/* USER CODE BEGIN 4 */
void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim)
{
	button_state = HAL_GPIO_ReadPin(Button_GPIO_Port, Button_Pin); //Check if button is pressed
	if (button_state == GPIO_PIN_SET) 
	{
		
	__HAL_TIM_SET_COMPARE(&htim4, TIM_CHANNEL_1, Steps_Third[index]);  //Green - 3
  __HAL_TIM_SET_COMPARE(&htim4, TIM_CHANNEL_2, Steps_Second[index]); //Orange - 2
  __HAL_TIM_SET_COMPARE(&htim4, TIM_CHANNEL_3, steps_first[index]);  //Red - 1
  __HAL_TIM_SET_COMPARE(&htim4, TIM_CHANNEL_4, Steps_Fourth[index]); //Blue - 4
		
	}
	else
	{
		
	__HAL_TIM_SET_COMPARE(&htim4, TIM_CHANNEL_1, Steps_Second[index]); //Green - 2
  __HAL_TIM_SET_COMPARE(&htim4, TIM_CHANNEL_2, Steps_Third[index]);  //Orange - 3
  __HAL_TIM_SET_COMPARE(&htim4, TIM_CHANNEL_3, Steps_Fourth[index]); //Red - 4
  __HAL_TIM_SET_COMPARE(&htim4, TIM_CHANNEL_4, steps_first[index]);  //Blue - 1
		
	}	
	
	index ++;
	if (index == 1000) index = 0;
}

/* USER CODE END 4 */

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
