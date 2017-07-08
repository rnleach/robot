# robot
AVR/Arduino based robot code for my kids. They think it is cooler because Dad made it.

## Introduction
I have a few Arduino boards, an [OSEPP Robot kit][1], and a [Starter Kit for Arduino][2]. I plan on
mixing and matching parts to make a robot and doing all the code in C/C++ without using the Arduino
library. I'll be writing all the code, but my kids will be helping with the robot and choosing the 
components that get put onto it.

## Code
Instead of using a bunch of libraries I plan to roll my own C/C++ code for the components so the 
kids can see how some pretty simple low level bit fiddling can make the robot work. It may not be 
as elegant, portable, or robust as some of the libraries, but it is meant to be simple and 
demonstrate programming principles like encapsulation.

# Tips and tricks
### How to find serial port on linux
- dmesg | grep tty
### How to monitor serial on linux
- cu
  - cu -l /dev/ttyUSB0 -s 9600  <- Baud Rate
  - Then in another terminal do ps -ef | grep ttyUSB0 and kill the two processes running cu.
  - This version is good for reading ASCII output as strings.
- jpnevulator
  - first set baud rate, $ stty -F /dev/ttyUSB0 9600
  - jpnevulator [--timing-print] [--ascii] --tty=/dev/ttyUSB0 --read
  - Has a read mode and a write mode.
  - Does not pretty print ASCII
  - Easy to stop with Ctrl-c
  - see "man" entry for more information.
  - The make file should generate a serial_monitor.sh script for you, just use that.

[1]:https://osepp.com/starter-kits/87-osepp-101-robotic-basics-starter
[2]:https://www.elegoo.com/product/elegoo-uno-project-super-starter-kit/
