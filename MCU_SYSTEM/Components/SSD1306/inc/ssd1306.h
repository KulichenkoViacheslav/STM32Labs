 /**
  ******************************************************************************
  * @file    ssd1306.h
  * @brief   This file contains all the function prototypes for
  *          the oled modules
  ******************************************************************************
  */

#ifndef SSD1306_H
#define SSD1306_H

#include "fonts.h"
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "i2c.h" 

#define SSD1306_128X64 			1						            // OR #define SSD1306_128X32
#define SSD1306_ADDRESS			0x3C				            // I2C address display
#define SSD1306_I2C_PORT		hi2c2					          // Name I2C Module
#define SSD1306_I2C_ADDR    (SSD1306_ADDRESS << 1)  // 0x3C<<1 = 0x78

#ifdef SSD1306_128X64
#define SSD1306_GEOMETRY		GEOMETRY_128_64
// SSD1306 width in pixels
#define SSD1306_WIDTH           128
// SSD1306 LCD height in pixels
#define SSD1306_HEIGHT          64
#elif SSD1306_128X32
#define SSD1306_GEOMETRY		GEOMETRY_128_32
// SSD1306 width in pixels
#define SSD1306_WIDTH           128
// SSD1306 LCD height in pixels
#define SSD1306_HEIGHT          32
#endif

//  Enumeration for screen colors
typedef enum {
	Black = 0x00, // Black color, no pixel
	White = 0x01,  //Pixel is set. Color depends on LCD
} ssd1306_color_e_t;

typedef enum {
  GEOMETRY_128_64   = 0,
  GEOMETRY_128_32   = 1
}ssd1306_geometry_e_t;

//  Struct to store transformations

typedef struct {
	uint16_t currentX;
	uint16_t currentY;
	uint8_t inverted;
	ssd1306_color_e_t color;
	bool initialized;
} ssd1306_s_t;
/* CODE END Private typedefs */

/* CODE BEGIN External variables */
//	Definition of the i2c port in main
extern I2C_HandleTypeDef SSD1306_I2C_PORT;
/* CODE END External variables */

/* CODE BEGIN PFP */
/* Private function prototypes -----------------------------------------------*/
bool ssd1306_Init(void);
void ssd1306_Fill(ssd1306_color_e_t color);
void ssd1306_UpdateScreen(void);
void ssd1306_DrawPixel(uint8_t x, uint8_t y, ssd1306_color_e_t color);
void ssd1306_DrawBitmap(uint8_t X, uint8_t Y, uint8_t W, uint8_t H, const uint8_t* pBMP, ssd1306_color_e_t color);
void ssd1306_DrawLine(int16_t x0, int16_t y0, int16_t x1, int16_t y1, ssd1306_color_e_t color);
void ssd1306_DrawRectangle(int16_t x, int16_t y, int16_t width, int16_t height, ssd1306_color_e_t color);
void ssd1306_FillRectangle(int16_t x, int16_t y, int16_t width, int16_t height, ssd1306_color_e_t color);
void ssd1306_DrawTriangle(uint16_t x1, uint16_t y1, uint16_t x2, uint16_t y2, uint16_t x3, uint16_t y3, ssd1306_color_e_t color);
void ssd1306_FillTriangle(uint16_t x1, uint16_t y1, uint16_t x2, uint16_t y2, uint16_t x3, uint16_t y3, ssd1306_color_e_t color);
void ssd1306_DrawCircle(int16_t x0, int16_t y0, int16_t radius, ssd1306_color_e_t color);
void ssd1306_FillCircle(int16_t x0, int16_t y0, int16_t radius, ssd1306_color_e_t color);
void ssd1306_DrawCircleQuads(int16_t x0, int16_t y0, int16_t radius, uint8_t quads, ssd1306_color_e_t color);
void ssd1306_DrawProgressBar(uint16_t x, uint16_t y, uint16_t width, uint16_t height, uint8_t progress, ssd1306_color_e_t color);
char ssd1306_WriteChar(char ch, FontDef Font, ssd1306_color_e_t color);
char ssd1306_WriteString(char* str, FontDef Font, ssd1306_color_e_t color);
void ssd1306_SetCursor(uint8_t x, uint8_t y);
void ssd1306_DisplayOn(void);
void ssd1306_DisplayOff(void);
void ssd1306_InvertDisplay(void);
void ssd1306_NormalDisplay(void);
void ssd1306_ResetOrientation(void);
void ssd1306_FlipScreenVertically(void);
void ssd1306_MirrorScreen(void);
void ssd1306_Clear(void);
/* CODE END PFP */
#endif /* SSD1306_H */
