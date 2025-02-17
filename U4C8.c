#include <stdio.h>
#include "pico/stdlib.h"
#include "inc/init.h"



int main()
{
    stdio_init_all();

    initDisplay();


restart:
    ssd1306_draw_line(0, 0, 127, 63, 1, ssd);
    render_on_display(ssd, &frame_area);
    
    while (1) {
        printf("Hello, world!\n");
        sleep_ms(1000);
    } 
}
