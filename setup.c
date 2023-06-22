#pragma orgall 0x1000

#include <xc.h>
#include "setup.h"
#include "uart.h"
#include "configs.h"
#include "delay.h"
#include "mcu.h"
#include "adc.h"
#include "lcd.h"
#include "spi.h"

void setup() {    
    TRISDbits.RD0 = 0;
    UART_Init(9600);
    ADC_Init(0);
    LCD_Init();
    
    LCD_String_xy(1, 5, "Bem Vindo!");
    LCD_String_xy(2, 5, "PIC18F4550");
    
    INTCONbits.GIE = 1;
    INTCONbits.PEIE = 1;
    PIE1bits.RCIE = 1;
}