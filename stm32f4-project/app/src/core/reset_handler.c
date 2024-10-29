#include <libopencm3/cm3/nvic.h>
#include <libopencm3/cm3/scb.h>
#include <libopencm3/cm3/vector.h>

#define BOOTLOADER_SIZE (0x8000)

int main(void);
typedef void (*funcp_t)(void);
extern funcp_t __preinit_array_start, __preinit_array_end;
extern funcp_t __init_array_start, __init_array_end;
extern funcp_t __fini_array_start, __fini_array_end;

void reset_handler(void) {

  volatile unsigned *src, *dest;
  funcp_t *fp;

  // Copy initialized data from flash to SRAM
  for (src = &_data_loadaddr, dest = &_data; dest < &_edata; src++, dest++) {
    *dest = *src;
  }

  // Zeroing uninitialized bss data
  while (dest < &_ebss) {
    *dest++ = 0;
  }

  // Ensure 8 byte alignment of stack pointer on interrupts
  SCB_CCR |= SCB_CCR_STKALIGN;

  // Enable access to Floating-Point coprocessor
  SCB_CPACR |= SCB_CPACR_FULL * (SCB_CPACR_CP10 | SCB_CPACR_CP11);

  // Set Vector Table Offset Register to start of application code
  SCB_VTOR = BOOTLOADER_SIZE;

  // C++ Functions for Static Global Variables
  for (fp = &__preinit_array_start; fp < &__preinit_array_end; fp++) {
    (*fp)();
  }
  for (fp = &__init_array_start; fp < &__init_array_end; fp++) {
    (*fp)();
  }

  // Call main application's entry point
  (void)main();

  // Destructors
  for (fp = &__fini_array_start; fp < &__fini_array_end; fp++) {
    (*fp)();
  }
}
