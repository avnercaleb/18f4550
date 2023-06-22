#include <xc.h>
#include <stdlib.h>
#include "setup.h"
#include "uart.h"
#include "delay.h"
#include "adc.h"
#include "eeprom.h"
#include "spi.h"

#define led PORTDbits.RD0
#define SPI_SS PORTAbits.RA5

const uint8_t modbusQuery[8] = {0x68,0x04,0x00,0x00,0x00,0x04,0xF8,0xF0};

void interrupt Interrupt() {
    UART_Interrupt();
}

void main(void) {
    char temp = 0;
    unsigned int localAddr = 0;
    short FNSTAT = 0;
            
    setup(); 
    
    while(1) {
     UART_Write_Text_ln("0x04");   
        
    }   
    
}


