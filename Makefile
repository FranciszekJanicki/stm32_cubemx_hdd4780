PROJECT_DIR := $(shell pwd)
BUILD_DIR := ${PROJECT_DIR}/build
APP_DIR := ${PROJECT_DIR}/app
DRIVERS_DIR := ${PROJECT_DIR}/Drivers
REQUIREMENTS_DIR := ${PROJECT_DIR}/requirements
STM32CUBEMX_DIR := ${PROJECT_DIR}/cmake/stm32cubemx
UTILITY_DIR := ${APP_DIR}/utility

.PHONY: build
build: 
	cd ${BUILD_DIR} && make

.PHONY: clean
clean: 
	rm -rf ${BUILD_DIR}

.PHONY: cmake
cmake:
	cd ${PROJECT_DIR} && make clean && mkdir build && cmake -S . -B build

.PHONY: flash
flash: 
	STM32_Programmer_CLI -c port=swd -d ${BUILD_DIR}/app/main/app.elf -rst

.PHONY: serial
serial:
	minicom -D /dev/ttyACM0 -b 115200

.PHONY: clang-format
clang-format:
	for ext in h c cpp hpp; do \
		find $(SOURCE_DIR) -iname "*.$$ext" -print0 | xargs -0 -r clang-format -i; \
	done

.PHONY: add-utility
add-utility:
	git submodule add -f https://github.com/franciszekjanicki/stm32-utility.git ${UTILITY_DIR}

.PHONY: update-utility
update-utility:
	git submodule update --init --recursive

.PHONY: remove-utility
remove-utility:
	git submodule deinit -f ${UTILITY_DIR}
	git rm -rf ${UTILITY_DIR}
	rm -rf ${UTILITY_DIR}
	rm -rf .git/modules/app/utility

.PHONY: all
all:
	make clang-format && make build && make flash && make serial
