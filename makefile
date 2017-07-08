#
# Program Name
#
PROG=robot
.DEFAULT_GOAL := $(PROG)

#
# Compile time serial configuration
#
SERIAL_BAUD_RATE=9600

#
# Board set up
#
FREQ=16000000UL
BOARD=ATMEGA328P
BOARD_LOWER_CASE=atmega328p

#
# Serial Connection info for uploader
#
DEVICE=/dev/ttyACM0
BAUD_RATE_UPLOAD=115200

#
# Compiler
#
CXX = avr-g++
CXXFLAGS = -Ilibs -std=gnu++11 -Os -DF_CPU=$(FREQ) -mmcu=$(BOARD_LOWER_CASE) -DBAUD=$(SERIAL_BAUD_RATE)

#
# Linker
#
LINK = avr-gcc
LINK_FLAGS = -mmcu=$(BOARD_LOWER_CASE)

#
# bin utils
#
OBJCPY=avr-objcopy
OBJCPY_FLAGS = -O ihex -R .eeprom

#
# Programmer/uploader
#
UPLOADER=avrdude
UPLOADER_FLAGS= -F -V -c arduino -p $(BOARD) -P $(DEVICE) -b $(BAUD_RATE_UPLOAD) -U 

#
# Header files
#
HDRS =$(wildcard ./*.h) 
HDRS += $(wildcard ./libs/*.h)

#
# Source files
#
SRCS=$(wildcard ./*.cpp)

#
# Print some info
#
$(info $$SRCS is ${SRCS})
$(info $$HDRS is ${HDRS})
$(info                  )

#
# Object Files
#
OBJS=$(subst .cpp,.o,$(SRCS))
%.o: %.c $(HDRS)
	$(CXX) -c -o $@ $< $(CXXFLAGS)

#
# Program Linking
#
$(PROG).elf : $(OBJS)
	$(LINK) $(OBJS) -o $(PROG).elf $(LINK_FLAGS)

#
# Verify - do not convert to hex and upload.
#
verify: $(PROG).elf

#
# Hex conversion
#
$(PROG).hex: verify
	$(OBJCPY) $(OBJCPY_FLAGS) $(PROG).elf $(PROG).hex

#
# Upload
#
$(PROG): $(PROG).hex
	$(UPLOADER) $(UPLOADER_FLAGS) flash:w:$(PROG).hex
	echo "clear && stty -F $(DEVICE) $(SERIAL_BAUD_RATE) && jpnevulator --ascii --tty=$(DEVICE) --read" > serial_monitor.sh
	chmod 0775 serial_monitor.sh

clean:
	- rm *.o *.hex *.elf serial_monitor.sh