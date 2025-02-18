#include <stdio.h>
#include "pico/stdlib.h"
#include "hardware/gpio.h"
#include "hardware/i2c.h"
#include "src/init.h" 
#include "src/functions.h"
#include <stdlib.h>  // for abs

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

    int ledToggle = 0; // persistent toggle state for LED_RED
    bool override = false;
    uint16_t last_joystick_x = 0;

    // New variables for LED_BLUE
    int ledToggleBlue = 0;
    bool overrideBlue = false;
    uint16_t last_joystick_y = 0;

    // Track if LED is controlled by joystick
    bool wasJoystickRed = true;
    bool wasJoystickBlue = true;

<<<<<<< HEAD
    // Inicializa o botão A apenas uma vez
    gpio_init(B1_PIN);
    gpio_set_dir(B1_PIN, GPIO_IN);
    gpio_pull_up(B1_PIN);

=======
    
>>>>>>> parent of 39f0f2a (refactor joystick control logic and update position thresholds for improved responsiveness)
   uint32_t last_print_time = 0;

   float led_intensity_y = 0;
   float led_intensity_x = 0;
<<<<<<< HEAD
=======

    int square_x = 0;
    int square_y = 0;
>>>>>>> parent of 39f0f2a (refactor joystick control logic and update position thresholds for improved responsiveness)

   int square_x = 0;
   int square_y = 0;
   
    while (1) {
        // Process joystick Y (for LED_BLUE)
        adc_select_input(0);
        uint16_t ex_y = adc_read();
        printf("Y: %d\n", ex_y);
        joystick_define_intensity(&led_intensity_y, ex_y);
<<<<<<< HEAD
                
=======
        
>>>>>>> parent of 39f0f2a (refactor joystick control logic and update position thresholds for improved responsiveness)
        // Cancel blue override if joystick Y changed significantly
        if (abs((int)ex_y - (int)last_joystick_y) > 50) {
            overrideBlue = false;
        }
        last_joystick_y = ex_y;
<<<<<<< HEAD

        // Atualiza LED azul via joystick se não estiver em override
        if (!overrideBlue) {
            pwm_set_gpio_level(LED_BLUE_PIN, led_intensity_y);
            wasJoystickBlue = true;
        }
=======
>>>>>>> parent of 39f0f2a (refactor joystick control logic and update position thresholds for improved responsiveness)

        // Atualiza LED azul via joystick se não estiver em override
        if (!overrideBlue) {
            pwm_set_gpio_level(LED_BLUE_PIN, led_intensity_y);
            wasJoystickBlue = true;
        }

        // Process joystick X (for LED_RED)
        adc_select_input(1);
        uint16_t ex_x = adc_read();
        printf("X: %d\n", ex_x);
        joystick_define_intensity(&led_intensity_x, ex_x);

        // Cancel override for red LED if joystick X changed significantly
        if (abs((int)ex_x - (int)last_joystick_x) > 50) {
            override = false;
        }
        last_joystick_x = ex_x;

        // Atualiza LED vermelho via joystick se não estiver em override
        if (!override) {
            pwm_set_gpio_level(LED_RED_PIN, led_intensity_x);
            wasJoystickRed = true;
        }

        // Limpa o quadrado anterior
        ssd1306_square(&ssd, square_x, square_y, 8, false, true);

        // Move o quadrado
        update_position(ex_x, ex_y, &square_x, &square_y);

        // chama a função para renderizar e enviar o quadrado
        ssd1306_square(&ssd, square_x, square_y, 8, true, true);
        ssd1306_send_data(&ssd);


        // Cancel override for red LED if joystick X changed significantly
        if (abs((int)ex_x - (int)last_joystick_x) > 50) {
            override = false;
        }
        last_joystick_x = ex_x;

        // Atualiza LED vermelho via joystick se não estiver em override
        if (!override) {
            pwm_set_gpio_level(LED_RED_PIN, led_intensity_x);
            wasJoystickRed = true;
        }

        wasJoystickRed = true;
    

    // Limpa o quadrado anterior
    ssd1306_square(&ssd, square_x, square_y, 8, false, true);

    // Move o quadrado
    update_position(ex_x, ex_y, &square_x, &square_y);

    // chama a função para renderizar e enviar o quadrado
    ssd1306_square(&ssd, square_x, square_y, 8, true, true);
    ssd1306_send_data(&ssd);


       // 

        float duty_cycle = ((float)led_intensity_x / 4095)*100;

        uint32_t current_time = to_ms_since_boot(get_absolute_time());

        if (current_time - last_print_time > 1000)
        {
            printf("Duty Cycle: %.2f\n", duty_cycle);
            last_print_time = current_time;
           
        }

        // Remova a re-inicialização do botão dentro do loop:
        // gpio_init(B1_PIN);
        // gpio_pull_up(B1_PIN);

<<<<<<< HEAD
        // Use apenas o check:
        if (gpio_get(B1_PIN) == 0) {
            sleep_ms(10);  // debounce inicial
=======
        // Button press toggles override for both LEDs,
        // forcing them OFF on the first click if initially controlled by joystick.
        if(gpio_get(B1_PIN) == 0) {
            sleep_ms(10);
>>>>>>> parent of 39f0f2a (refactor joystick control logic and update position thresholds for improved responsiveness)
            if (gpio_get(B1_PIN) == 0) {
                if (wasJoystickRed || wasJoystickBlue) {
                    ledToggle = 0;
                    ledToggleBlue = 0;
                    wasJoystickRed = false;
                    wasJoystickBlue = false;
                } else {
                    ledToggle = !ledToggle;
                    ledToggleBlue = !ledToggleBlue;
                }
                override = true;
                overrideBlue = true;
<<<<<<< HEAD
                sleep_ms(200); // debounce final
                // Aplica o estado do toggle para os LEDs
=======
                sleep_ms(250); // evita múltiplas trocas rápidas

                // Aplica o estado do toggle para ambos LEDs
>>>>>>> parent of 39f0f2a (refactor joystick control logic and update position thresholds for improved responsiveness)
                pwm_set_gpio_level(LED_RED_PIN, ledToggle ? 4095 : 0);
                pwm_set_gpio_level(LED_BLUE_PIN, ledToggleBlue ? 4095 : 0);
            }
        }

        printf("end\n");
        sleep_ms(100);
    } 

    return 0;
}
