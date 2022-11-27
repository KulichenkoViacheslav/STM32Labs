/**
  ******************************************************************************
  * @file    command_line.h
  * @brief   This file contains all the function prototypes for
  *          the clock modules
  ******************************************************************************
  */

#ifndef COMMAND_LINE_H
#define COMMAND_LINE_H

#include <stdio.h>
#include "usart.h"

#define USE_PRINTF
//#define USE_SCANF

#ifdef __GNUC__
/* With GCC/RAISONANCE, small printf (option LD Linker->Libraries->Small printf
   set to 'Yes') calls __io_putchar() */
#ifdef USE_PRINTF
#define PUTCHAR_PROTOTYPE int __io_putchar(int ch)
#endif /* USE_PRINTF */
#ifdef USE_SCANF
#define GETCHAR_PROTOTYPE int __io_getchar(void)
#endif /* USE_SCANF*/

#else
#ifdef USE_PRINTF
#define PUTCHAR_PROTOTYPE int fputc(int ch, FILE *f)
#endif /* USE_PRINTF */
#ifdef USE_SCANF
#define GETCHAR_PROTOTYPE int fgetc(FILE *f)
#endif /* USE_SCANF*/
#endif /* __GNUC__ */

#ifdef USE_PRINTF
PUTCHAR_PROTOTYPE
{
  /* Place your implementation of fputc here */
  /* e.g. write a character to the EVAL_COM2 and Loop until the end of transmission */
  HAL_UART_Transmit(&huart2, (uint8_t *)&ch, 1, 0x00FF); 

  return ch;
}
#endif /* USE_PRINTF */

#ifdef USE_SCANF
GETCHAR_PROTOTYPE
{
  uint8_t ch = 0;

  /* Clear the Overrun flag just before receiving the first character */
  __HAL_UART_CLEAR_OREFLAG(&huart2);

  /* Wait for reception of a character on the USART RX line and echo this
   * character on console */
  HAL_UART_Receive(&huart2, (uint8_t *)&ch, 1, HAL_MAX_DELAY);
  HAL_UART_Transmit(&huart2, (uint8_t *)&ch, 1, HAL_MAX_DELAY);
  return ch;
}
#endif /* USE_SCANF*/
#endif /* COMMAND_LINE_H */