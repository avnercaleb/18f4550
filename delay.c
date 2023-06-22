#include "delay.h"
#include "mcu.h"

void delay_ms(unsigned int milliseconds) {
    unsigned int i;
    unsigned int j;
    
    for(i = 0; i < milliseconds; i++) {
        for(j = 0; j < _XTAL_FREQ / CONST_TIME_MS; j++);
    }
}

void delay_s(int seconds) {
    
    unsigned int i = seconds * 1000;
    delay_ms(i);
}

