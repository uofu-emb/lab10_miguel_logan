/**
 * Copyright (c) 2022 Raspberry Pi (Trading) Ltd.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#ifndef MY_ADDITION
#include <stdbool.h>          // For `true` and `false`
#include <stdio.h>            // Standard I/O
#include "pico/stdlib.h"      // For stdlib functions like GPIO handling
#include "pico/cyw43_arch.h"  // For CYW43 Wi-Fi/BT support
#include "FreeRTOS.h"         // For FreeRTOS functions
#include "task.h"             // For task management
#endif

#include "my_addition.h"

int count = 0;
int led_state = 0;
const uint LED_PIN = 0;



#define MAIN_TASK_PRIORITY      ( tskIDLE_PRIORITY + 1UL )
#define BLINK_TASK_PRIORITY     ( tskIDLE_PRIORITY + 2UL )
#define MAIN_TASK_STACK_SIZE configMINIMAL_STACK_SIZE
#define BLINK_TASK_STACK_SIZE configMINIMAL_STACK_SIZE



void blink_task_sleep(__unused void *params) {
  while (1) {
    led_state = !led_state;
    gpio_put(LED_PIN, led_state);
    sleep_ms(500);
  }
}

void blink_task_thread(__unused void *params) {
  while (1) {
    led_state = !led_state;
    gpio_put(LED_PIN, led_state);
    vTaskDelay(500);
  }
}

void main_task(__unused void *params) {
    xTaskCreate(blink_task_thread, "BlinkThread",
                BLINK_TASK_STACK_SIZE, NULL, BLINK_TASK_PRIORITY, NULL);
}

int main( void )
{
    gpio_init(LED_PIN);
    gpio_set_dir(LED_PIN, GPIO_OUT);
    stdio_init_all();
    const char *rtos_name;
    rtos_name = "FreeRTOS";
    TaskHandle_t task;
    xTaskCreate(main_task, "MainThread",
                MAIN_TASK_STACK_SIZE, NULL, MAIN_TASK_PRIORITY, &task);
    vTaskStartScheduler();
    return 0;
}
