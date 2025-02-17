#include <stdlib.h>
#include "pico/stdlib.h"
#include "hardware/gpio.h"
#include "hardware/i2c.h"
#include "inc/ssd1306.h"


// LEDS PINS
#define LED_BLUE_PIN 12
#define LED_RED_PIN 13
#define LED_GREEN_PIN 11

// BUTTONS PINS
#define B1_PIN 5

// I2C Pins TELA LCD
#define LCD_SDA_PIN 14
#define LCD_SCL_PIN 15
#define ENDR_LCD 0x3C
#define I2C_PORT i2c1


void init_leds() {
    gpio_init(LED_BLUE_PIN);
    gpio_init(LED_RED_PIN);
    gpio_init(LED_GREEN_PIN);
    gpio_set_dir(LED_BLUE_PIN, GPIO_OUT);
    gpio_set_dir(LED_RED_PIN, GPIO_OUT);
    gpio_set_dir(LED_GREEN_PIN, GPIO_OUT);

}

void init_buttons() {
    gpio_init(B1_PIN);
    gpio_set_dir(B1_PIN, GPIO_IN);    
    gpio_pull_up(B1_PIN);
    
}


void init_i2c(ssd1306_t *ssd) {
    i2c_init(I2C_PORT, 400 * 1000); // Ensure correct I2C port is used
    gpio_set_function(LCD_SDA_PIN, GPIO_FUNC_I2C);
    gpio_set_function(LCD_SCL_PIN, GPIO_FUNC_I2C);   
    gpio_pull_up(LCD_SCL_PIN);
    gpio_pull_up(LCD_SDA_PIN); 

    ssd1306_init(ssd, WIDTH, HEIGHT, 0, ENDR_LCD, I2C_PORT);
    ssd1306_config(ssd);
    ssd1306_send_data(ssd);
}