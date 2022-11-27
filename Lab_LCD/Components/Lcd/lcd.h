#ifndef LCD_H
#define LCD_H

#include <stdint.h>

void lcd_init(void);
void lcd_set_cursor(uint8_t line, uint8_t column);
void lcd_write_string(uint8_t * str, uint8_t size);

#endif /* LCD_H */
