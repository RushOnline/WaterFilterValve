export ARDUINO_DIR		= $(CURDIR)/../Arduino
export ARDUINO_PORT		= /dev/ttyUSB0
export BOARD_TAG		= pro5v328
export ARDUINO_LIBS		= Timer Button
export BOARDS_TXT		= $(ARDUINO_DIR)/hardware/arduino/boards.txt

# Prerequisites:
# sudo apt-get install arduino-mk
# sudo ln -snf /usr/share/arduino/ard-parse-boards /usr/local/bin/ard-parse-boards

%:
	$(MAKE) -f $(CURDIR)/../Arduino-Makefile/Arduino.mk $@

default: all

reset:
	[ -c $(ARDUINO_PORT) ] && stty -F $(ARDUINO_PORT) hupcl || true

upload: reset raw_upload

.PHONY: reset upload default
