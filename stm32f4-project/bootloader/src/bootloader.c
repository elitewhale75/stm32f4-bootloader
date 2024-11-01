#include <libopencm3/cm3/vector.h>
#include <libopencm3/stm32/memorymap.h>
#include <stdint.h>

#define BOOTLOADER_SIZE (0x8000U)
#define MAIN_APP_START_ADDRESS (FLASH_BASE + BOOTLOADER_SIZE)

static void jump_to_main(void) {

  vector_table_t *app_vector_table = (vector_table_t *)(MAIN_APP_START_ADDRESS);
  app_vector_table->reset();
}

int main(void) {
  jump_to_main();

  // Never return
  return 0;
}
