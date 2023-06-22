#ifndef __LCD
    #define __LCD

    #include <xc.h> 

    #define RS LATDbits.LATD2  
    #define EN LATDbits.LATD3   
    #define D4 LATDbits.LATD4
    #define D5 LATDbits.LATD5
    #define D6 LATDbits.LATD6
    #define D7 LATDbits.LATD7
    #define RSTRIS TRISDbits.RD2
    #define ENTRIS TRISDbits.RD3  
    #define D4TRIS TRISDbits.RD4 
    #define D5TRIS TRISDbits.RD5  
    #define D6TRIS TRISDbits.RD6  
    #define D7TRIS TRISDbits.RD7 

    void LCD_Init();                   /*Initialize LCD*/
    void LCD_Command(unsigned char );  /*Send command to LCD*/
    void LCD_Char( char x);    /*Send data to LCD*/
    void LCD_String(const char *);     /*Display data string on LCD*/
    void LCD_String_xy(char, char , const char *);
    void LCD_Char_xy(char row,char pos, char dat);
    void LCD_Clear();                  /*Clear LCD Screen*/


#endif