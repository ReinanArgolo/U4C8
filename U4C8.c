#include <stdio.h>
#include "pico/stdlib.h"
#include "hardware/gpio.h"
#include "hardware/i2c.h"
#include "src/init.h" 
#include "src/functions.h"

ssd1306_t ssd;


int main()
{
    stdio_init_all();

    // Inicializa o LCD
    init_i2c(&ssd);
    ssd1306_fill(&ssd, false);
    ssd1306_send_data(&ssd);

    // Inicializa o ADC
    adc_start();

    pwm_init_gpio(LED_BLUE_PIN, 4096);
    pwm_init_gpio(LED_RED_PIN, 4096);  // added: initialize red LED PWM

   for (size_t i = 0; i < 10; i++)
   {
    if(i>0) ssd1306_square(&ssd, i - 1, i - 1, 8, false, false);
    ssd1306_square(&ssd, i, i, 8, true, true);
    ssd1306_send_data(&ssd);
   }
    
   uint32_t last_print_time = 0;

   float led_intensity_y = 0;
   float led_intensity_x = 0;
   int ledToggle = 0; // persistent toggle state for LED_RED

   
    while (1) {
        adc_select_input(0);
        uint16_t ex_y = adc_read();
        printf("Y: %d\n", ex_y);
        joystick_define_intensity(&led_intensity_y, ex_y);
        pwm_set_gpio_level(LED_BLUE_PIN, led_intensity_y);

        adc_select_input(1);
        uint16_t ex_x = adc_read();
        printf("X: %d\n", ex_x);
        joystick_define_intensity(&led_intensity_x, ex_x);
        pwm_set_gpio_level(LED_RED_PIN, led_intensity_x); 

        float duty_cycle = ((float)led_intensity_x / 4095)*100;

        uint32_t current_time = to_ms_since_boot(get_absolute_time());

        if (current_time - last_print_time > 1000)
        {
            printf("Duty Cycle: %.2f\n", duty_cycle);
            last_print_time = current_time;
           
        }

        gpio_init(B1_PIN);
        gpio_pull_up(B1_PIN);

        if(gpio_get(B1_PIN) == 0) {
            sleep_ms(10);
            if (gpio_get(B1_PIN) == 0) {
            ledToggle = !ledToggle;
            sleep_ms(250); // evita múltiplas trocas rápidas

            // Aplica o estado do toggle para o LED vermelho
            pwm_set_gpio_level(LED_RED_PIN, ledToggle ? 4095 : 0);
            }
        }



        printf("end\n");
        sleep_ms(100);
    } 

    return 0;
}
