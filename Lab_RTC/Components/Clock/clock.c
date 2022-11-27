/**
  ******************************************************************************
  * @file    clock.c
  * @brief   This file contains all the function prototypes for
  *          the clock modules
  ******************************************************************************
  */

#include "clock.h"
#include "rtc.h"

void clock_set_time(uint8_t hours, uint8_t minutes, uint8_t seconds);
/* 
  1. get current time
  2. set end time = current time + bomb time
  3. set alarm 1 s
  4. alarm event
  5. get current time
  6. ouput to CL
  7. check in current time == end time
  8. go to 3.
*/
