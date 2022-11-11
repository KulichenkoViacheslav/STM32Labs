#ifndef LED_H 
#define LED_H

#include <stdint.h>

typedef enum
{
	wait_new_config = 0,
	execution_config = 1,
	completed_config = 2
}led_config_state_e_t;

typedef struct
{
  uint8_t color[10];
  uint8_t power;
	led_config_state_e_t state;
}led_config_s_t; 


void led_init(void);
void led_set_power(led_config_s_t data);
led_config_state_e_t led_get_state(void);
void led_set_state(led_config_state_e_t state);
#endif /*LED_H*/ 

