#ifndef __EEPROM
    #define __EEPROM
        
    unsigned short EEPROM_Write(unsigned char value, unsigned short addr);
    unsigned char EEPROM_Read(unsigned short addr);
    unsigned short EEPROM_Int_Write(long value, unsigned short addr, unsigned short addr2);
    long EEPROM_Int_Read(unsigned short addr, unsigned short addr2);
#endif