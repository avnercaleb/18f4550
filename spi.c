#include "spi.h"

void Spi_Init(Spi_Type sType, Spi_Clock_Idle sClock, Spi_Data_Sample sData, Spi_Transmit_Edge sEdge){
    
    if(sType & 0x04) {
        SSPSTAT = sEdge;
        TRISBbits.RB1 = 1;
        TRISCbits.RC7 = 0;
        TRISAbits.RA5 = 1;        
    } else {
        SSPSTAT = sData | sEdge;
        TRISBbits.RB1 = 0;
        TRISCbits.RC7 = 0;
        TRISAbits.RA5 = 0;
    }
    
    SSPCON1 = sType | sClock;
}




void Spi_Write(uint8_t data){
    SSPBUF = data;
}

unsigned SpiDataReady(){
    if(SSPSTATbits.BF) {
        return 1;
    } else {
        return 0;
    }
}

SpiReceiveWait(){
    while(!SSPSTATbits.BF);
}

uint8_t Spi_Read() {
    SpiReceiveWait();
    return (SSPBUF);
}