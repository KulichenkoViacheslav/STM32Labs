#include "led.h"
#include "tim.h"
#include <string.h>
#include <stdio.h>


static led_config_s_t led_config = {0};



void led_init(void)
{
  HAL_TIM_Base_Start_IT(&htim4);
  HAL_TIM_PWM_Start(&htim4, TIM_CHANNEL_1);
	HAL_TIM_PWM_Start(&htim4, TIM_CHANNEL_2);
	HAL_TIM_PWM_Start(&htim4, TIM_CHANNEL_3);
	HAL_TIM_PWM_Start(&htim4, TIM_CHANNEL_4);
}

void led_set_power(led_config_s_t data )
{
  led_config.power = data.power;
  memcpy(led_config.color, data.color, sizeof (data.color)); 
}  

void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim)
{
  if(htim->Instance == htim4.Instance)
  {
    if (strcmp((char *)(led_config.color), "green") == 0)
    {
       __HAL_TIM_SET_COMPARE(&htim4, TIM_CHANNEL_1, led_config.power * 10);
      printf("\r\n>> Set TIM_CHANNEL_1");
    }
    else if (strcmp((char *)(led_config.color), "orange") == 0)
    {
      __HAL_TIM_SET_COMPARE(&htim4, TIM_CHANNEL_2, led_config.power * 10);
      printf("\r\n>> Set TIM_CHANNEL_2");
    }
    else if (strcmp((char *)(led_config.color), "red") == 0)
    {
      __HAL_TIM_SET_COMPARE(&htim4, TIM_CHANNEL_3, led_config.power * 10);
      printf("\r\n>> Set TIM_CHANNEL_3");
    }
    else if (strcmp((char *)(led_config.color), "blue") == 0)
    {
      __HAL_TIM_SET_COMPARE(&htim4, TIM_CHANNEL_4, led_config.power * 10);
      printf("\r\n>> Set TIM_CHANNEL_4");
    }
  }
}

