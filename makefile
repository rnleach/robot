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
ifeq ($(OS),Windows_NT)
    $(info OS is $(OS) and is not configured yet.)
	MY_OS = $(OS)
else
    UNAME_S := $(shell uname -s)
	MY_OS = $(UNAME_S)
    ifeq ($(UNAME_S),Linux)
        DEVICE=/dev/ttyACM0
    endif
    ifeq ($(UNAME_S),Darwin)
        DEVICE=/dev/tty.usbmodemfd1311
    endif
endif
$(info                      )
$(info OS is $(MY_OS)       )
$(info $$DEVICE is ${DEVICE})
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
# float support for printf
LINK_FLAGS += -Wl,-u,vfprintf -lprintf_flt -lm

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
HDRS = $(wildcard ./*.h) 
HDRS += $(wildcard ./libs/*.h)

#
# Source files
#
SRCS = $(wildcard ./*.cpp)
SRCS += $(wildcard ./libs/*.cpp)

#
# Print some info
#
$(info                  )
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
#	echo "clear && stty -F $(DEVICE) $(SERIAL_BAUD_RATE) && jpnevulator --ascii --tty=$(DEVICE) --read" > serial.sh
	echo "clear && screen $(DEVICE) $(SERIAL_BAUD_RATE)" > serial.sh
	chmod 0775 serial.sh

clean:
	- rm *.o *.hex *.elf ./libs/*.o serial.sh