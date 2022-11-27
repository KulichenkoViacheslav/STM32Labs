/**
  ******************************************************************************
  * @file    clock.h
  * @brief   This file contains all the function prototypes for
  *          the clock modules
  ******************************************************************************
  */

#ifndef CLOCK_H
#define CLOCK_H

#include <stdint.h>

void clock_set_time(uint8_t hours, uint8_t minutes, uint8_t seconds);
//void clock_set_alarm(uint8_t hours, uint8_t minutes, uint8_t seconds);

#endif /* CLOCK_H */
