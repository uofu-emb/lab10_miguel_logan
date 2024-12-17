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


#pragma GCC optimize ("O0")


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


void spammy_loop(__unused void *params) {
  while(1) {
    uint32_t k;
    for (int i = 0; i < 30; i = i + 1) {
      uint32_t j = 0;
      j = ((~j >> i) + 1) * 27644437;
      k = j;
    }
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
    //blink_task_sleep(1);
    spammy_loop(1);
    /* stdio_init_all(); */
    /* const char *rtos_name; */
    /* rtos_name = "FreeRTOS"; */
    /* TaskHandle_t task; */
    /* xTaskCreate(blink_task_thread, "MainThread", */
    /*             MAIN_TASK_STACK_SIZE, NULL, MAIN_TASK_PRIORITY, &task); */
    /* vTaskStartScheduler(); */
    /* return 0; */
}
