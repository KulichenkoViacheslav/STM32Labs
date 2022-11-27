#include "lcd.h"
#include "timer.h"
#include "gpio.h"

static void lcd_clock(void);
static void lcd_write_data(uint8_t data);
static void lcd_write_command(uint8_t data);
static void lcd_write_port(uint8_t data);

void lcd_init(void)
{
  /* Start init LCD controler */
  lcd_write_port(0x00);
  HAL_Delay(60);
  HAL_GPIO_WritePin(DISP_RS_GPIO_Port, DISP_RS_Pin, GPIO_PIN_RESET);
  HAL_GPIO_WritePin(DISP_RW_GPIO_Port, DISP_RW_Pin, GPIO_PIN_RESET);
  
  /* Function Set */
  /* Set 4-bit interface mode*/
  lcd_write_port(0x20);
  lcd_clock();
  lcd_write_port(0x20);
  lcd_clock();
  /* Set 2-line mode (7-bit) and Display on (6-bit)*/
  lcd_write_port(0x80);
  lcd_clock();
  timer_delay_us(40);
  
  /* Display On/OFF Control */
  lcd_write_port(0x00);
  lcd_clock();
  /* Display on (6-bit), Cursor on (5-bit) and Blink on (4-bit)*/
  lcd_write_port(0xF0);
  lcd_clock();  
  timer_delay_us(40);

  /* Display clear*/
  lcd_write_port(0x00);
  lcd_clock();
  /* Display clear (4-bit)*/
  lcd_write_port(0x10);
  lcd_clock();
  timer_delay_us(2000);

  /* Initialization End*/
  lcd_write_port(0x00);
  lcd_clock();
  /* Increment mode (5-bit) and Entire shift on (4-bit)*/
  lcd_write_port(0x60);
  lcd_clock();
}

void lcd_set_cursor(uint8_t line, uint8_t column)
{
  uint8_t address = column;
  /* line 0 and 1 */
  if (line == 1)
  {
    address |= 0x40;
  }
  
  lcd_write_command(0x80 | address);
}

void lcd_write_string(uint8_t * str, uint8_t size)
{
  uint8_t index = 0;
  for (index = 0; index < size; index ++)
  {
    lcd_write_data(str[index]);
  }
}

/* Privet definition */
static void lcd_write_command(uint8_t data)
{
  lcd_write_port(data);
  lcd_clock();
  lcd_write_port((data & 0x0F) << 4);
  lcd_clock();
}

static void lcd_write_data(uint8_t data)
{
  HAL_GPIO_WritePin(DISP_RS_GPIO_Port, DISP_RS_Pin, GPIO_PIN_SET);
  lcd_write_port(data);
  lcd_clock();
  lcd_write_port((data & 0x0F) << 4);
  lcd_clock();
  HAL_GPIO_WritePin(DISP_RS_GPIO_Port, DISP_RS_Pin, GPIO_PIN_RESET);
}

static void lcd_write_port(uint8_t data)
{
  HAL_GPIO_WritePin(DISP_DB7_GPIO_Port, DISP_DB7_Pin, GPIO_PIN_RESET);
  HAL_GPIO_WritePin(DISP_DB6_GPIO_Port, DISP_DB6_Pin, GPIO_PIN_RESET);
  HAL_GPIO_WritePin(DISP_DB5_GPIO_Port, DISP_DB5_Pin, GPIO_PIN_RESET);
  HAL_GPIO_WritePin(DISP_DB4_GPIO_Port, DISP_DB4_Pin, GPIO_PIN_RESET);
  
  if (data & 0x80)
  {
    HAL_GPIO_WritePin(DISP_DB7_GPIO_Port, DISP_DB7_Pin, GPIO_PIN_SET);
  }
  if (data & 0x40)
  {
    HAL_GPIO_WritePin(DISP_DB6_GPIO_Port, DISP_DB6_Pin, GPIO_PIN_SET);
  }
  if (data & 0x20)
  {
    HAL_GPIO_WritePin(DISP_DB5_GPIO_Port, DISP_DB5_Pin, GPIO_PIN_SET);
  }
  if (data & 0x10)
  {
    HAL_GPIO_WritePin(DISP_DB4_GPIO_Port, DISP_DB4_Pin, GPIO_PIN_SET);
  }
}

static void lcd_clock(void)
{
  HAL_GPIO_WritePin(DISP_ENA_GPIO_Port, DISP_ENA_Pin, GPIO_PIN_SET);
  timer_delay_us(20);
  HAL_GPIO_WritePin(DISP_ENA_GPIO_Port, DISP_ENA_Pin, GPIO_PIN_RESET);
  timer_delay_us(20);
}
