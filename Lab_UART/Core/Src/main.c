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
#include "usart.h"
#include "gpio.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include <string.h>
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

/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
/* USER CODE BEGIN PFP */
uint8_t msg[] = "Hello world\r\n";
uint8_t mass_input_data[100] = {0};
uint8_t mass_index = 0;
uint8_t buffer = 0;
uint32_t number = 0;
/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */
#include <stdio.h>
#ifdef __GNUC__
/* With GCC/RAISONANCE, small printf (option LD Linker->Libraries->Small printf
   set to 'Yes') calls __io_putchar() */
#define PUTCHAR_PROTOTYPE int __io_putchar(int ch)
//#define GETCHAR_PROTOTYPE int __io_getchar(void)
#else
#define PUTCHAR_PROTOTYPE int fputc(int ch, FILE *f)
//#define GETCHAR_PROTOTYPE int fgetc(FILE *f)
#endif /* __GNUC__ */

PUTCHAR_PROTOTYPE
{
  /* Place your implementation of fputc here */
  /* e.g. write a character to the EVAL_COM2 and Loop until the end of transmission */
  HAL_UART_Transmit(&huart2, (uint8_t *)&ch, 1, 0x00FF); 

  return ch;
}

//GETCHAR_PROTOTYPE
//{
//  uint8_t ch = 0;

//  /* Clear the Overrun flag just before receiving the first character */
//  __HAL_UART_CLEAR_OREFLAG(&huart2);

//  /* Wait for reception of a character on the USART RX line and echo this
//   * character on console */
//  HAL_UART_Receive(&huart2, (uint8_t *)&ch, 1, HAL_MAX_DELAY);
//  HAL_UART_Transmit(&huart2, (uint8_t *)&ch, 1, HAL_MAX_DELAY);
//  return ch;
//}
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
  MX_USART2_UART_Init();
  /* USER CODE BEGIN 2 */
  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
  uint8_t counter = 0;
  printf("**************\r\n");
  printf(">> Please enter number 0-99...");
  HAL_UART_Receive_IT(&huart2, &buffer, 1);
  while (1)
  {

/*    printf(">> Please enter number 0-99...\r");
    HAL_StatusTypeDef status = HAL_UART_Receive(&huart2, &mass_input_data[0], 2, 3000);
    if (status == HAL_OK)
    {
      printf("\r\n>>Counter = ");
      for (uint8_t i = 0; i < 10; i ++)
      {
        if (mass_input_data[i] != 0)
        printf("%i", mass_input_data[i] - 0x30);
      }
      printf("\r\n");
    }
    else if (status == HAL_TIMEOUT)
    {
      printf("\r\n>>Uart timeout\r\n");
    }
    else
    {
      printf("\r\n>>Uart error\r\n");
    }
*/    
    HAL_Delay(1000);
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
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV4;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV2;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_0) != HAL_OK)
  {
    Error_Handler();
  }
}

/* USER CODE BEGIN 4 */
// Green:100
void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart)
{
  uint8_t color[10] = {0};
  uint8_t color_index = 0;
  if (buffer == '\r')
  {    
    number = 0;
    for (uint8_t i = 0; i < sizeof(color); i ++)
    {
      color[i] = 0;
    }
    color_index = 0;
    for (uint8_t i = 0; i < sizeof(mass_input_data); i ++)
    {
      if ((mass_input_data[i] >= 'A') && (mass_input_data[i] <= 'z'))
      {
        color[color_index] = mass_input_data[i];
        color_index ++;
      }
      else if ((mass_input_data[i] >= '0') && (mass_input_data[i] <= '9'))
      {
        number = number * 10 + (mass_input_data[i] - 0x30);
      }
      else if (mass_input_data[i] == 0)
      {
        break;
      }
    }
    if (strcmp((char *)color, "green") == 0)
    {
      printf("\r\n>> Set TIM_CHANNEL_1");
    }
    else if (strcmp((char *)color, "orange") == 0)
    {
      printf("\r\n>> Set TIM_CHANNEL_2");
    }
    else if (strcmp((char *)color, "red") == 0)
    {
      printf("\r\n>> Set TIM_CHANNEL_3");
    }
    else if (strcmp((char *)color, "blue") == 0)
    {
      printf("\r\n>> Set TIM_CHANNEL_4");
    }
    printf("\r\n>> Set color %s = %i %%\r\n", color, number);
    for (uint8_t i = 0; i < sizeof(mass_input_data); i ++)
    {
      mass_input_data[i] = 0;
      mass_index = 0;
    }
  }
  else
  {
    mass_input_data[mass_index] = buffer;
    mass_index ++;
  }
  
  HAL_UART_Receive_IT(&huart2, &buffer, 1);
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
