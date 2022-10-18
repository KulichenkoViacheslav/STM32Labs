#include "timer.h"
#include "tim.h"

void timer_init(void)
{
  HAL_TIM_Base_Start(&htim3);
}