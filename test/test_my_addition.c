#include <stdio.h>
#include <pico/stdlib.h>
#include <stdint.h>
#include <unity.h>
#include "unity_config.h"
#include "../include/my_addition.h"
void setUp(void) {}

void tearDown(void) {}

void test_run_blink()
{
  int count = 0;
  bool led_state = false;
  int max_iterations = 1;
  run_blink_task(&count, &led_state, &max_iterations);
  TEST_ASSERT_TRUE(led_state);
}

int main (void)
{
    UNITY_BEGIN();
    RUN_TEST(test_run_blink);
    return UNITY_END();

}
