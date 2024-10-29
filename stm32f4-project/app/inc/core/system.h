#ifndef INC_SYSTEM_H
#define INC_SYSTEM_H

#include <libopencm3/cm3/systick.h>
#include <libopencm3/cm3/vector.h>
#include <libopencm3/stm32/rcc.h>

#define TARGET_FREQ (1000)
#define AHB_BUS_FREQ (180000000)

extern volatile uint64_t ticks;
uint64_t get_ticks(void);
void rcc_setup(void);
void system_setup(void);

#endif // !INC_SYSTEM_H
