#include "command_line.h"
#include "usart.h"
#include <string.h>
#include <stdio.h>
#include "led.h"

#define printf(...) sizebuf = sprintf( (char*)pbuf, __VA_ARGS__); command_line_output(pbuf, sizebuf)

static uint8_t mass_input_data[100] = {0};
static uint8_t mass_index = 0;
static uint8_t buffer = 0;
static uint32_t number = 0;
static uint8_t color[10] = {0};
static uint8_t color_index = 0;
static uint8_t pbuf[128] = {0};
static int sizebuf = 0;

void command_line_output(uint8_t *pbuffer, int sizebuffer);

void command_line_init(void)
{
  printf("**************\r\n");
  printf(">> Set color led and power pct...");
  HAL_UART_Receive_IT(&huart2, &buffer, 1);
}

void command_line_output(uint8_t *pbuffer, int sizebuffer)
{
  HAL_UART_Transmit(&huart2, pbuffer, sizebuffer, 1000 );
}

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
		if(((strcmp((char*)color, "green") == 0) || 
				(strcmp((char*)color, "red") == 0) ||
				(strcmp((char*)color, "blue") == 0) ||
				(strcmp((char*)color, "orange") == 0)) && 
				((number <= 100) && (number >= 0)))
		{
			printf("\r\n>> Set color %s = %i %%\r\n", color, number);
			led_config_s_t new_config;
			memcpy(new_config.color, color, sizeof(color));		
			new_config.power = number;
			led_set_power(new_config);
		}
		else
		{
			printf("\n\rtry again bidlo\n\r");
			led_set_state(completed_config);
		}
		//clear input buffer
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