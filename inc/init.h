#include "pico/stdlib.h"
#include "inc/ssd1306.h"
#include "hardware/i2c.h"
#include <string.h>

const uint I2C_SDA = 14;
const uint I2C_SCL = 15;

struct render_area frame_area = {
    start_column : 0,
    end_column : ssd1306_width - 1,
    start_page : 0,
    end_page : ssd1306_n_pages - 1
};

uint8_t ssd[ssd1306_buffer_length];


void initDisplay() {
    i2c_init(i2c1, ssd1306_i2c_clock * 1000);
    gpio_set_function(I2C_SDA, GPIO_FUNC_I2C);
    gpio_set_function(I2C_SCL, GPIO_FUNC_I2C);
    gpio_pull_up(I2C_SDA);
    gpio_pull_up(I2C_SCL);

    ssd1306_init();

    calculate_render_area_buffer_length(&frame_area);

    // zera o display inteiro
    memset(ssd, 0, ssd1306_buffer_length);
    render_on_display(ssd, &frame_area);
}


