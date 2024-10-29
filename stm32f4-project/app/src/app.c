#include "core/system.h"
#include "core/timer.h"
#include <libopencm3/cm3/scb.h>
#include <libopencm3/stm32/gpio.h>

#define LED_PORT GPIOA
#define LED_PIN GPIO5

int main(void) {
  rcc_setup();
  system_setup();

  gpio_mode_setup(LED_PORT, GPIO_MODE_AF, GPIO_PUPD_NONE, LED_PIN);
  gpio_set_af(LED_PORT, GPIO_AF1, LED_PIN);
  timer_setup();

  uint64_t start_time = get_ticks();
  float duty_cycle = 0.0f;

  timer_pwm_set_duty_cycle(duty_cycle);

  while (1) {
    if (get_ticks() - start_time >= 10) {
      duty_cycle += 1.0f;
      if (duty_cycle > 100.0f)
        duty_cycle = 0.0f;
      timer_pwm_set_duty_cycle(duty_cycle);
      start_time = get_ticks();
    }
  }

  return 0;
}
