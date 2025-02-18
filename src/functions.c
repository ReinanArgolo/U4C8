#include "functions.h"
#define JOYSTICK_SENSITIVITY 0.02  // lower value reduces sensitivity

void joystick_define_intensity(float *led_intensity, uint16_t ex_y) {
    if(*led_intensity < 0) *led_intensity = 0;
    if(*led_intensity > 4095) *led_intensity = 4095.0;
    if(*led_intensity >= 0) {
        if(ex_y > 2047 && *led_intensity < 4095) {
            float diff = ex_y - 2047;
            *led_intensity += diff * JOYSTICK_SENSITIVITY;  // smooth addition with sensitivity factor
            printf("LED Intensity: %f\n", *led_intensity);
        }
        if(ex_y < 2047 && *led_intensity > 0) {
            float diff = 2047 - ex_y;
            *led_intensity -= diff * JOYSTICK_SENSITIVITY;  // smooth subtraction with sensitivity factor
            printf("LED Intensity: %f\n", *led_intensity);
        }
    }

}

// New update_position using exponential smoothing to cancel noise when joystick is at rest
void update_position(uint16_t x_value, uint16_t y_value, int* x_pos, int* y_pos) {
    // Calibrated center values
    const int center_x = 1800;
    const int center_y = 1918;
    // Threshold: ignore small fluctuations
    const int threshold = 30;
    // Movement factor (tweak for desired speed)
    const float factor = 0.001;
    // Smoothing factor for exponential moving average
    const float alpha = 0.1;

    // Static variables for smoothing and subpixel accumulation
    static float avg_error_x = 0, avg_error_y = 0;
    static float fx = 0, fy = 0;
    static int initialized = 0;
    if (!initialized) {
        fx = *x_pos;
        fy = *y_pos;
        initialized = 1;
    }
    
    // Compute raw errors
    int err_x = x_value - center_x;
    int err_y = y_value - center_y;
    // Apply exponential smoothing
    avg_error_x = avg_error_x * (1 - alpha) + err_x * alpha;
    avg_error_y = avg_error_y * (1 - alpha) + err_y * alpha;
    
    // Discard noise if error is under threshold
    float effective_error_x = (abs((int)avg_error_x) < threshold) ? 0 : avg_error_x;
    float effective_error_y = (abs((int)avg_error_y) < threshold) ? 0 : avg_error_y;
    
    // Update the subpixel accumulators
    fx += effective_error_x * factor;
    fy += effective_error_y * factor;
    
    // Clamp to display bounds (0-127 for X, 0-63 for Y)
    if (fx < 0) fx = 0;
    if (fx > 127) fx = 127;
    if (fy < 0) fy = 0;
    if (fy > 63) fy = 63;
    
    *x_pos = (int)fx;
    *y_pos = (int)fy;
}
