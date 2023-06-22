#ifndef __UART
    #define __UART
    #include <xc.h>
    #include "mcu.h"
    #include <string.h>

    #define UARTBUFFLENGTH  17
    char UARTBUFF[UARTBUFFLENGTH] = {' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ',
                                     ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', '\0'};
    
    void UART_Init(long int baudrate);
    void UART_Write(const char data);
    void UART_Write_ln(const char data);
    void UART_Write_Text(char txt[]);
    void UART_Write_Text_ln(char txt[]);
    char UART_Read();
    void UART_Read_Text(char *output, unsigned int length);
    void UART_Interrupt();
    bit UART_Locate_Pattern(const char compare[], unsigned int *addr);
    bit UART_Read_Cmd(const char compare[], const char EOC[], unsigned int *addr);
    void UART_Clear_Buffer(const char compare[], unsigned int addr);
    
#endif