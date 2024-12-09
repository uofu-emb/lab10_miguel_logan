#ifndef MY_ADDITION
#include <stdbool.h>          // For `true` and `false`
#include <stdio.h>            // Standard I/O
#include "pico/stdlib.h"      // For stdlib functions like GPIO handling
#include "pico/cyw43_arch.h"  // For CYW43 Wi-Fi/BT support
#include "FreeRTOS.h"         // For FreeRTOS functions
#include "task.h"             // For task management
#endif

void run_blink_task(int *count, bool *led_state, int *max_iterations){
    int iteration = 0;
    while (iteration < *max_iterations) {
        cyw43_arch_gpio_put(CYW43_WL_GPIO_LED_PIN, (*led_state));
        if ((*count)++ % 11) (*led_state) = !(*led_state);
        vTaskDelay(500);
        iteration++;  // Increment the loop counter
	printf("current iterations passed: %d\n", iteration);
	
    }
}
