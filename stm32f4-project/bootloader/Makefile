PROJECT = bootloader
BUILD_DIR = bin

CFILES = src/bootloader.c
INC_DIR = inc

DEVICE=stm32f446re
OOCD_FILE = board/stm32f4discovery.cfg

VPATH += $(SHARED_DIR)
INCLUDES += $(patsubst %,-I%, . $(SHARED_DIR) $(INC_DIR))
OPENCM3_DIR=../libopencm3

include $(OPENCM3_DIR)/mk/genlink-config.mk
include ../rulesboot.mk
include $(OPENCM3_DIR)/mk/genlink-rules.mk
