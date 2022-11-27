#include "timer.h"
#include "tim.h"
#include <stdbool.h>

#define timer htim6

void timer_delay_us(uint16_t time)
{
#if defined(timer)
  __HAL_TIM_SET_AUTORELOAD(&timer, time);
  __HAL_TIM_SET_COUNTER(&timer, 0);
  __HAL_TIM_CLEAR_FLAG(&timer, TIM_FLAG_UPDATE);
  __HAL_TIM_ENABLE(&timer);
  while (__HAL_TIM_GET_FLAG(&timer, TIM_FLAG_UPDATE) == false){};
#else /* timer */
  The timer not defined!
#endif /* timer */
}
