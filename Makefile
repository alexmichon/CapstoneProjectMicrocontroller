ARDUINO := arduino

TARGET := my_service
SKETCH := $(TARGET)/$(TARGET).ino

PACKAGE := adafruit
ARCH := nrf52
BOARD := feather52

PORT := /dev/ttyUSB0

FULLBOARD = $(PACKAGE):$(ARCH):$(BOARD)

CURRENT_DIR = $(shell pwd)
SKETCH_PATH = $(CURRENT_DIR)/$(SKETCH)
BUILD_DIR = $(CURRENT_DIR)/build

AFLAGS  = --pref build.path=$(BUILD_DIR)
AFLAGS += --preserve-temp-files
#AFLAGS += -v

build:
	$(ARDUINO) --verify $(AFLAGS) $(SKETCH_PATH) --board $(FULLBOARD) --port $(PORT)

upload:
	$(ARDUINO) --upload $(AFLAGS) $(SKETCH_PATH) --board $(FULLBOARD) --port $(PORT)
	if [ -n "$(MONITOR)" ]; then screen $(PORT) $(MONITOR); fi

clean:
	rm -rf $(BUILD_DIR)

rebuild: clean build
