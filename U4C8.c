#include <stdio.h>
#include "pico/stdlib.h"
#include "pico/stdlib.h"
#include "hardware/gpio.h"
#include "hardware/i2c.h"
#include "src/init.h"

ssd1306_t ssd;


int main()
{
    stdio_init_all();

    init_i2c(&ssd);
    ssd1306_fill(&ssd, false);
    ssd1306_send_data(&ssd);

   for (size_t i = 0; i < 10; i++)
   {
    if(i>0) ssd1306_square(&ssd, i - 1, i - 1, 8, false, false);
    ssd1306_square(&ssd, i, i, 8, true, true);
    sleep_ms(300);
    ssd1306_send_data(&ssd);
   }
    
    
    while (1) {
        printf("Hello, world!\n");
        sleep_ms(1000);
    } 
}
