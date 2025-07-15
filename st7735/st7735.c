#include "st7735.h"

void st7735_write_cmd(uint8_t cmd)
{
    gpio_put(TFT_CS_PIN, 0);
    gpio_put(TFT_DC_PIN, 0);
    spi_write_blocking(spi1, &cmd, 1);
    gpio_put(TFT_CS_PIN, 1);
}

void st7735_write_data(uint8_t data)
{
    gpio_put(TFT_CS_PIN, 0);
    gpio_put(TFT_DC_PIN, 1);
    spi_write_blocking(spi1, &data, 1);
    gpio_put(TFT_CS_PIN, 1);
}

void st7735_init(void)
{
    // 初始化GPIO
    gpio_init(TFT_CS_PIN);
    gpio_set_dir(TFT_CS_PIN, GPIO_OUT);
    gpio_put(TFT_CS_PIN, 1);

    gpio_init(TFT_DC_PIN);
    gpio_set_dir(TFT_DC_PIN, GPIO_OUT);
    gpio_put(TFT_DC_PIN, 0);

    gpio_init(TFT_RST_PIN);
    gpio_set_dir(TFT_RST_PIN, GPIO_OUT);
    gpio_put(TFT_RST_PIN, 0);

    // 初始化SPI
    spi_init(spi1, 4000000);
    gpio_set_function(TFT_SCLK_PIN, GPIO_FUNC_SPI);
    gpio_set_function(TFT_MOSI_PIN, GPIO_FUNC_SPI);

    // 硬件复位
    gpio_put(TFT_RST_PIN, 0);
    sleep_ms(50);
    gpio_put(TFT_RST_PIN, 1);
    sleep_ms(120);

    // 软件复位
    st7735_write_cmd(ST7735_SWRESET);
    sleep_ms(150);
    st7735_write_cmd(ST7735_SLPOUT);
    sleep_ms(500);

    // 帧率控制
    st7735_write_cmd(ST7735_FRMCTR1);
    st7735_write_data(0x01);
    st7735_write_data(0x2C);
    st7735_write_data(0x2D);

    st7735_write_cmd(ST7735_FRMCTR2);
    st7735_write_data(0x01);
    st7735_write_data(0x2C);
    st7735_write_data(0x2D);

    st7735_write_cmd(ST7735_FRMCTR3);
    st7735_write_data(0x01);
    st7735_write_data(0x2C);
    st7735_write_data(0x2D);
    st7735_write_data(0x01);
    st7735_write_data(0x2C);
    st7735_write_data(0x2D);

    // 显示反转控制
    st7735_write_cmd(ST7735_INVCTR);
    st7735_write_data(0x07);

    // 电源控制
    st7735_write_cmd(ST7735_PWCTR1);
    st7735_write_data(0xA2);
    st7735_write_data(0x02);
    st7735_write_data(0x84);

    st7735_write_cmd(ST7735_PWCTR2);
    st7735_write_data(0xC5);

    st7735_write_cmd(ST7735_PWCTR3);
    st7735_write_data(0x0A);
    st7735_write_data(0x00);

    st7735_write_cmd(ST7735_PWCTR4);
    st7735_write_data(0x8A);
    st7735_write_data(0x2A);

    st7735_write_cmd(ST7735_PWCTR5);
    st7735_write_data(0x8A);
    st7735_write_data(0xEE);

    // VCOM控制
    st7735_write_cmd(ST7735_VMCTR1);
    st7735_write_data(0x0E);

    st7735_write_cmd(ST7735_INVOFF);

    // 内存访问控制
    st7735_write_cmd(ST7735_MADCTL);
    st7735_write_data(0xC8);

    // 颜色模式 - 16位RGB565
    st7735_write_cmd(ST7735_COLMOD);
    st7735_write_data(0x05);

    // Gamma校正
    st7735_write_cmd(ST7735_GMCTRP1);
    st7735_write_data(0x02);
    st7735_write_data(0x1c);
    st7735_write_data(0x07);
    st7735_write_data(0x12);
    st7735_write_data(0x37);
    st7735_write_data(0x32);
    st7735_write_data(0x29);
    st7735_write_data(0x2d);
    st7735_write_data(0x29);
    st7735_write_data(0x25);
    st7735_write_data(0x2B);
    st7735_write_data(0x39);
    st7735_write_data(0x00);
    st7735_write_data(0x01);
    st7735_write_data(0x03);
    st7735_write_data(0x10);

    st7735_write_cmd(ST7735_GMCTRN1);
    st7735_write_data(0x03);
    st7735_write_data(0x1d);
    st7735_write_data(0x07);
    st7735_write_data(0x06);
    st7735_write_data(0x2E);
    st7735_write_data(0x2C);
    st7735_write_data(0x29);
    st7735_write_data(0x2D);
    st7735_write_data(0x2E);
    st7735_write_data(0x2E);
    st7735_write_data(0x37);
    st7735_write_data(0x3F);
    st7735_write_data(0x00);
    st7735_write_data(0x00);
    st7735_write_data(0x02);
    st7735_write_data(0x10);

    // 正常显示模式
    st7735_write_cmd(ST7735_NORON);
    sleep_ms(10);

    // 开启显示
    st7735_write_cmd(ST7735_DISPON);
    sleep_ms(100);
}

void st7735_set_addr_window(uint8_t x0, uint8_t y0, uint8_t x1, uint8_t y1)
{
    st7735_write_cmd(ST7735_CASET);
    st7735_write_data(0x00);
    st7735_write_data(x0);
    st7735_write_data(0x00);
    st7735_write_data(x1);

    st7735_write_cmd(ST7735_RASET);
    st7735_write_data(0x00);
    st7735_write_data(y0);
    st7735_write_data(0x00);
    st7735_write_data(y1);

    st7735_write_cmd(ST7735_RAMWR);
}

void st7735_fill_screen(uint16_t color)
{
    st7735_set_addr_window(0, 0, ST7735_WIDTH - 1, ST7735_HEIGHT - 1);

    gpio_put(TFT_CS_PIN, 0);
    gpio_put(TFT_DC_PIN, 1);

    for (int i = 0; i < ST7735_WIDTH * ST7735_HEIGHT; i++)
    {
        uint8_t data[2] = {(uint8_t)(color >> 8), (uint8_t)(color & 0xFF)};
        spi_write_blocking(spi1, data, 2);
    }

    gpio_put(TFT_CS_PIN, 1);
}

void st7735_draw_pixel(uint8_t x, uint8_t y, uint16_t color)
{
    if (x >= ST7735_WIDTH || y >= ST7735_HEIGHT)
        return;

    st7735_set_addr_window(x, y, x, y);

    gpio_put(TFT_CS_PIN, 0);
    gpio_put(TFT_DC_PIN, 1);

    uint8_t data[2] = {(uint8_t)(color >> 8), (uint8_t)(color & 0xFF)};
    spi_write_blocking(spi1, data, 2);

    gpio_put(TFT_CS_PIN, 1);
}

void st7735_draw_bitmap(uint8_t x, uint8_t y, uint8_t w, uint8_t h, const uint16_t *bitmap)
{
    if (x >= ST7735_WIDTH || y >= ST7735_HEIGHT)
        return;
    if (x + w > ST7735_WIDTH)
        w = ST7735_WIDTH - x;
    if (y + h > ST7735_HEIGHT)
        h = ST7735_HEIGHT - y;

    st7735_set_addr_window(x, y, x + w - 1, y + h - 1);

    gpio_put(TFT_CS_PIN, 0);
    gpio_put(TFT_DC_PIN, 1);

    for (int i = 0; i < w * h; i++)
    {
        uint16_t color = bitmap[i];
        uint8_t data[2] = {(uint8_t)(color >> 8), (uint8_t)(color & 0xFF)};
        spi_write_blocking(spi1, data, 2);
    }

    gpio_put(TFT_CS_PIN, 1);
}