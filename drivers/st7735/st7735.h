#pragma once

#include "pico/stdlib.h"
#include "hardware/spi.h"
#include "hardware/gpio.h"

// 默认引脚定义 (可在board文件中重新定义)
#ifndef TFT_CS_PIN
#define TFT_CS_PIN 9
#endif

#ifndef TFT_SCLK_PIN
#define TFT_SCLK_PIN 10
#endif

#ifndef TFT_MOSI_PIN
#define TFT_MOSI_PIN 11
#endif

#ifndef TFT_RST_PIN
#define TFT_RST_PIN 12
#endif

#ifndef TFT_DC_PIN
#define TFT_DC_PIN 13
#endif

// 屏幕规格
#define ST7735_WIDTH 128
#define ST7735_HEIGHT 96

// ST7735命令定义
#define ST7735_SWRESET 0x01
#define ST7735_SLPOUT 0x11
#define ST7735_NORON 0x13
#define ST7735_INVOFF 0x20
#define ST7735_DISPON 0x29
#define ST7735_CASET 0x2A
#define ST7735_RASET 0x2B
#define ST7735_RAMWR 0x2C
#define ST7735_COLMOD 0x3A
#define ST7735_MADCTL 0x36
#define ST7735_FRMCTR1 0xB1
#define ST7735_FRMCTR2 0xB2
#define ST7735_FRMCTR3 0xB3
#define ST7735_INVCTR 0xB4
#define ST7735_PWCTR1 0xC0
#define ST7735_PWCTR2 0xC1
#define ST7735_PWCTR3 0xC2
#define ST7735_PWCTR4 0xC3
#define ST7735_PWCTR5 0xC4
#define ST7735_VMCTR1 0xC5
#define ST7735_GMCTRP1 0xE0
#define ST7735_GMCTRN1 0xE1

// 颜色定义
#define ST7735_BLACK 0x0000
#define ST7735_BLUE 0x001F
#define ST7735_RED 0xF800
#define ST7735_GREEN 0x07E0
#define ST7735_CYAN 0x07FF
#define ST7735_MAGENTA 0xF81F
#define ST7735_YELLOW 0xFFE0
#define ST7735_WHITE 0xFFFF

// 函数声明
void st7735_init(void);
void st7735_write_cmd(uint8_t cmd);
void st7735_write_data(uint8_t data);
void st7735_set_addr_window(uint8_t x0, uint8_t y0, uint8_t x1, uint8_t y1);
void st7735_fill_screen(uint16_t color);
void st7735_draw_pixel(uint8_t x, uint8_t y, uint16_t color);
void st7735_draw_bitmap(uint8_t x, uint8_t y, uint8_t w, uint8_t h, const uint16_t *bitmap);
