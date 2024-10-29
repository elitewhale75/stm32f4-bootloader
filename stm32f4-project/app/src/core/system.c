#include "core/system.h"

volatile uint64_t ticks = 0;

uint64_t get_ticks(void) { return ticks; }

void sys_tick_handler(void) { ticks++; }

void rcc_setup(void) {
  rcc_clock_setup_pll(&rcc_hsi_configs[RCC_CLOCK_3V3_180MHZ]);
  rcc_periph_clock_enable(RCC_GPIOA);
}
void system_setup(void) {
  systick_set_frequency(TARGET_FREQ, AHB_BUS_FREQ);
  systick_counter_enable();
  systick_interrupt_enable();
}
