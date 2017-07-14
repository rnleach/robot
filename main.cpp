#include <avr/io.h>
#include <util/delay.h>
#include <stdint.h>
#include <stdio.h>

#include "timers.h"
#include "compile_time.h"
#include "custom_serial.h"
#include "servo.h"

void init (void)
{
    serial_ascii_inout_init();
}

#define MAXT 5100
#define MINT 1480
#define RANGE_DEGREES 180
#define INCREMENT_DEGREES 30
#define STEPSIZE ((MAXT - MINT)/(RANGE_DEGREES / INCREMENT_DEGREES))
#define DELAY 500

int main (void)
{
    init();
    auto servo = ServoSG90_Pin09(MINT, MAXT);
    while(1){

        printf("start degrees up\n");
        for(int8_t angle = -90; angle <= 90; angle += 30) {
            servo.set_degrees(angle);
            _delay_ms(DELAY);
        }

        printf("start degrees down\n");
        for(int8_t angle = 90; angle >= -90; angle -= 30) {
            servo.set_degrees(angle);
            _delay_ms(DELAY);
        }
    }
}
