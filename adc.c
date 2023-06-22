#include <pic18f4550.h>

#include "adc.h"

void ADC_Init(unsigned short channel){
    ADCON1bits.PCFG0 = 0;
    ADCON1bits.PCFG1 = 0;
    ADCON1bits.PCFG  = (0b1111 - (channel + 1));
    ADCON2bits.ADFM  = 1;
    ADCON2bits.ACQT  = 0b010;
    ADCON2bits.ADCS  = 0b101;
}


unsigned int ADC_Read(unsigned short channel){
    ADCON0bits.CHS = channel;
    ADCON0bits.ADON = 1;
    ADCON0bits.GODONE = 1;
    
    while(ADCON0bits.GODONE);
    return (ADRES);
}