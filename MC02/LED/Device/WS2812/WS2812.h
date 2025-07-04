#ifndef __WS2812_H__
#define __WS2812_H__

#include "main.h"

#define WS2812_SPI_UNIT hspi6
#define WS2812_LowLevel    0xC0     // 0Ты
#define WS2812_HighLevel   0xF0     // 1Ты

extern SPI_HandleTypeDef WS2812_SPI_UNIT;

void WS2812_Ctrl(uint8_t r, uint8_t g, uint8_t b);

#endif
