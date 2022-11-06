#ifndef LED_H 
#define LED_H

#include <stdint.h>

typedef struct
{
  uint8_t color[10];
  uint8_t power;
}led_config_s_t;

void led_init(void);
void led_set_power(led_config_s_t data);


#endif /*LED_H*/ 

