#include <pic18f4550.h>

#include "uart.h"

void UART_Init(long int baudrate) {
    
    unsigned int x;
    x = (_XTAL_FREQ - baudrate * 64)/(baudrate * 64);
    
    if(x > 255) {
        x = (_XTAL_FREQ - baudrate * 16)/(baudrate * 16);
        BRGH = 1;
    }
    
    if(x < 256) {
        TRISCbits.TRISC6 = 1;   // Configura o pino RC6 como saída (TX)
        TRISCbits.TRISC7 = 1;   // Configura o pino RC7 como entrada (RX)
        
        SPBRG = x;
        
        TXSTAbits.SYNC = 0;     // Configura a UART para modo assíncrono
        RCSTAbits.SPEN = 1;     // Habilita a UART
        TXSTAbits.TXEN = 1;     // Habilita a transmissão
        RCSTAbits.CREN = 1;     // Habilita a recepção contínua
    }
    
}

// Função de envio de dados pela UART
void UART_Write(const char data) {
    while (!TXSTAbits.TRMT);    // Espera até que o registrador de transmissão esteja vazio
    TXREG = data;               // Envia o byte    
}

void UART_Write_ln(const char data) {
    UART_Write(data);
    UART_Write('\r');
    UART_Write('\n');
}

void UART_Write_Text(char txt[]) {
    int i;
    
    for(i = 0; txt[i] != '\0'; i++) UART_Write(txt[i]);
}

void UART_Write_Text_ln(char txt[]) {
    UART_Write_Text(txt);
    UART_Write('\r');
    UART_Write('\n');
}

char UART_Read() {
    while(!RCIF);
    return RCREG;
}

void UART_Read_Text(char *output, unsigned int length) {
    for(unsigned int i = 0; i < length; i++) {
        output[i] = UART_Read();
    }
    output[length] = '\0';
}

void UART_Interrupt() {
    if(RCIF){
        char temp = RCREG;
        
        for(unsigned int i = 0; i < UARTBUFFLENGTH - 1; i++) {
            UARTBUFF[i] = UARTBUFF[i + 1];
        }
        UARTBUFF[UARTBUFFLENGTH - 2] = temp;
        UARTBUFF[UARTBUFFLENGTH - 1] = '\0';
        RCIF = 0;
    } 
}

bit UART_Locate_Pattern(const char compare[], unsigned int *addr){
    
    unsigned int i, z, dataSize;    
    short located = 0;
    
    dataSize = strlen(compare);
    
    for(i = 0; i < (UARTBUFFLENGTH - dataSize); i++){
        located = 1;
        
        for(z = 0; z < dataSize; z++){
            if(UARTBUFF[z + i] != compare[z]){
                located = 0;
                break;
            }
        }
        if(located == 1){
            *addr = i;
            break;
        }
    }
    if(located == 1){
        return 1;
    } else {
        return 0;
    }
}

bit UART_Read_Cmd(const char compare[], const char EOC[], unsigned int *addr){
    
    unsigned int i, z, dataSize;    
    short located = 0;
    
    dataSize = strlen(compare);
    
    for(i = 0; i < (UARTBUFFLENGTH - dataSize); i++){
        located = 1;
        
        for(z = 0; z < dataSize; z++){
            if(UARTBUFF[z + i] != compare[z]){
                located = 0;
                break;
            }
        }
        if(located == 1){
            *addr = i;
            break;
        }
    }
    if(located == 1){
        dataSize = strlen(EOC);
    
        for(i = 0; i < (UARTBUFFLENGTH - dataSize); i++){
            located = 1;

            for(z = 0; z < dataSize; z++){
                if(UARTBUFF[z + i] != EOC[z]){
                    located = 0;
                    break;
                }
            }
        }
    }
    
    if(located == 1){
        return 1;
    } else {
        return 0;
    }
}

void UART_Clear_Buffer(const char compare[], unsigned int addr){
    
    unsigned int finalAddr = addr + strlen(compare);
    
    for(unsigned int i = addr; i < finalAddr; i++){
        UARTBUFF[i] = ' ';
    }
}


