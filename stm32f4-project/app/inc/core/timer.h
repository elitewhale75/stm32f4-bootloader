#ifndef INC_TIMER_H
#define INC_TIMER_H

#include <libopencm3/stm32/rcc.h>
#include <libopencm3/stm32/timer.h>

#define PRESCALER (180)
#define ARR_VALUE (1000)

void timer_setup(void);
void timer_pwm_set_duty_cycle(float duty_cycle);

#endif // !INC_TIMER_H
