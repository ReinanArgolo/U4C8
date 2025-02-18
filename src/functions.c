#include "functions.h"

void joystick_define_intensity(float *led_intensity, uint16_t ex_y) {
    if(*led_intensity < 0) *led_intensity = 0;
    if(*led_intensity > 4095) *led_intensity = 4095.0;
    if(*led_intensity >= 0) {
        if(ex_y > 2047 && *led_intensity < 4095) {
            float diff = ex_y - 2047;
            *led_intensity += diff * 0.05;  // smooth addition
            printf("LED Intensity: %f\n", *led_intensity);
        }
        if(ex_y < 2047 && *led_intensity > 0) {
            float diff = 2047 - ex_y;
            *led_intensity -= diff * 0.05;  // smooth subtraction
            printf("LED Intensity: %f\n", *led_intensity);
        }
    }

}

// Updated update_position with an increased threshold to prevent phantom movement
void update_position(uint16_t x_value, uint16_t y_value, int* x_pos, int* y_pos) {
    // Calibrated center values from your log
    const int center_x = 1800;
    const int center_y = 1918;
    const int threshold = 30;  // increased threshold to ignore fluctuations

    int error_x = x_value - center_x;
    int error_y = y_value - center_y;

    // Update square position only if error exceeds threshold
    if (error_x > threshold) { // joystick to right
        if (*x_pos < 127) { (*x_pos)++; }
    } else if (error_x < -threshold) { // joystick to left
        if (*x_pos > 0) { (*x_pos)--; }
    }
    
    if (error_y > threshold) { // joystick pushed down
        if (*y_pos < 63) { (*y_pos)++; }
    } else if (error_y < -threshold) { // joystick pushed up
        if (*y_pos > 0) { (*y_pos)--; }
    }
}
