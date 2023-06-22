#include <pic18f4550.h>

#include "eeprom.h"

unsigned short EEPROM_Write(unsigned char value, unsigned short addr){
    short intStatus = INTCONbits.GIE;
    
    while(EECON1bits.WR);
    EEADR = addr;
    EEDATA = value;
    
    EECON1bits.EEPGD = 0;
    EECON1bits.CFGS  = 0;
    EECON1bits.WREN  = 1;
    INTCONbits.GIE   = 0;
    
    EECON2 = 0x55;
    EECON2 = 0xAA;
    EECON1bits.WR = 1;
    
    INTCONbits.GIE = intStatus;
    
    return EECON1bits.WRERR;
}    

unsigned char EEPROM_Read(unsigned short addr){
    
    while(EECON1bits.WR);
    
    EEADR = addr;
    EECON1bits.EEPGD = 0;
    EECON1bits.CFGS  = 0;
    EECON1bits.RD  = 1;
    
    return (EEDATA);
}

unsigned short EEPROM_Int_Write(long value, unsigned short addr, unsigned short addr2){
    
    long MSB, LSB, status1, status2;
    
    MSB = value >> 8;
    LSB = value - (MSB << 8);
    status1 = EEPROM_Write(MSB, addr2);
    status2 = EEPROM_Write(LSB, addr);
    
    return (status1 || status2);
}

long EEPROM_Int_Read(unsigned short addr, unsigned short addr2){
    return ((EEPROM_Read(addr2) << 8) + EEPROM_Read(addr));
}