
#include "lcd.h"
#include "delay.h"

void LCD_Command(unsigned char cmd )
{
	//dsipdata = (dsipdata & 0x0f) |(0xF0 & cmd);  /*Send higher nibble of command first to PORT*/ 
    D4 = (unsigned short)((cmd>>4)&0b1);
    D5 = (unsigned short)((cmd>>5)&0b1);
    D6 = (unsigned short)((cmd>>6)&0b1);
    D7 = (unsigned short)((cmd>>7)&0b1);
	RS = 0;  /*Command Register is selected i.e.RS=0*/ 
	EN = 1;  /*High-to-low pulse on Enable pin to latch data*/ 
	NOP();
	EN = 0;
	delay_ms(1);
    //dsipdata = (dsipdata & 0x0f) | (cmd<<4);  /*Send lower nibble of command to PORT */
    D4 =(unsigned short)((cmd)&0b1);
    D5 = (unsigned short)((cmd>>1)&0b1);
    D6 = (unsigned short)((cmd>>2)&0b1);
    D7 = (unsigned short)((cmd>>3)&0b1);   
	EN = 1;
	NOP();
	EN = 0;
	delay_ms(3);
}

void LCD_Init()
{
    RSTRIS = 0;       /*PORT as Output Port*/
    ENTRIS = 0;       /*PORT as Output Port*/
    D4TRIS = 0;       /*PORT as Output Port*/
    D5TRIS = 0;       /*PORT as Output Port*/
    D6TRIS = 0;       /*PORT as Output Port*/
    D7TRIS = 0;       /*PORT as Output Port*/
    
    delay_ms(40);        /*15ms,16x2 LCD Power on delay*/
    LCD_Command(0x02);  /*send for initialization of LCD 
                          for nibble (4-bit) mode */
    LCD_Command(0x28);  /*use 2 line and 
                          initialize 5*8 matrix in (4-bit mode)*/
	LCD_Command(0x01);  /*clear display screen*/
    LCD_Command(0x0c);  /*display on cursor off*/
	LCD_Command(0x06);  /*increment cursor (shift cursor to right)*/	   
}

void LCD_Char( char dat)
{


	//dsipdata = (dsipdata & 0x0f) |(0xF0 & cmd);  /*Send higher nibble of command first to PORT*/ 
    D4 = (unsigned short)((dat>>4)&0b1);
    D5 = (unsigned short)((dat>>5)&0b1);
    D6 = (unsigned short)((dat>>6)&0b1);
    D7 = (unsigned short)((dat>>7)&0b1);
    
	RS = 1;  /*Data Register is selected*/
	EN = 1;  /*High-to-low pulse on Enable pin to latch data*/
	NOP();
	EN = 0;
	delay_ms(1);

    D4 =(unsigned short)((dat)&0b1);
    D5 = (unsigned short)((dat>>1)&0b1);
    D6 = (unsigned short)((dat>>2)&0b1);
    D7 = (unsigned short)((dat>>3)&0b1);       
	EN = 1;  /*High-to-low pulse on Enable pin to latch data*/
	NOP();
	EN = 0;
	delay_ms(3);
}


void LCD_Char_xy(char row,char pos, char dat)
{
   unsigned char location=0;       

    switch (row){
        case 0:
           location=(unsigned char)((0x80) + (pos) );  
           LCD_Command(location);   
           break;
        case 1:
           location=(unsigned char)((0xC0) + (pos));  
           LCD_Command(location);   
           break;
        case 2:
           location=(unsigned char)((0x94) + (pos));  
           LCD_Command(location);   
           break;
        case 3:
           location=(unsigned char)((0xD4) + (pos));  
           LCD_Command(location);   
           break;
    }
    LCD_Char(dat);
}

void LCD_String(const char *msg)
{
	while((*msg)!=0)
	{		
	  LCD_Char(*msg);
	  msg++;	
    }
}

void LCD_String_xy(char row,char pos,const char *msg)
{
   unsigned  char location=0;
    switch (row){
        case 0:
           location=(unsigned char)((0x80) + (pos));  
           LCD_Command(location);   
           break;
        case 1:
           location=(unsigned char)((0xC0) + (pos));  
           LCD_Command(location);   
           break;
        case 2:
           location=(unsigned char)((0x94) + (pos)); 
           LCD_Command(location);   
           break;
        case 3:
           location=(unsigned char)((0xD4) + (pos));  
           LCD_Command(location);   
           break;
           
    }

    LCD_String(msg);

}

void LCD_Clear()
{
   	LCD_Command(0x01);  /*clear display screen*/
    delay_ms(3);
}