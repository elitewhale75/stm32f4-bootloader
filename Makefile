# Makefile for STM32 Firmware Projects

# Docker image name
DOCKER_IMAGE = stm32-dev-env
DOCKER_CONTAINER = stm32-dev-debian

# OpenOCD configuration
OPENOCD_CONFIG = openocd.cfg
PROJECT_DIR = stm32f4-project/app
BINARY_NAME = app.bin
BINARY_FILE = $(PROJECT_DIR)/$(BINARY_NAME)
FLASH_ADDRESS = 0x08000000

# Targets

build:
	docker build --platform=linux/amd64 -t $(DOCKER_IMAGE) .

run:
	docker run --platform=linux/amd64 -it --rm --privileged --name $(DOCKER_CONTAINER) -v $(shell pwd):/workspace $(DOCKER_IMAGE)

flash:
	openocd -f $(OPENOCD_CONFIG) -c "program $(BINARY_FILE) $(FLASH_ADDRESS) verify reset exit"

compile:
	make -C $(PROJECT_DIR) -j$(shell nproc) TARGETS='stm32/f4'

.PHONY: all build run flash compile
