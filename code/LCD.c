#include "LCD.h"
#include <stdio.h>

void LCD_inti(void){
	SET_BIT(DDRA,3);  //RS  
	SET_BIT(DDRA,2);  //EN
	
	SET_BIT(DDRB, 0);
	SET_BIT(DDRB, 1);
	SET_BIT(DDRB, 2);
	SET_BIT(DDRB, 4);
	
	_delay_ms(15);
	
	LCD_cmd(0x02);
	LCD_cmd(0x28);
	LCD_cmd(0x0c);
	LCD_cmd(0x01);
	LCD_cmd(0x80);
}

void LCD_cmd(unsigned char cmd){
	//cmd --> 1111 0000 -->  High(H)-->1111 Low(L)-->0000
	
	CLR_BIT(PORTA, 3); // RS = 0

	PORTB &= 0b11101000;
	//High
	unsigned char H = ((cmd&0xf0)>>4);      // H = 0000 1111
	unsigned char temp = ((H & 0b00001000) << 1) | ((H & 0b00000111)); // H = 0001 0111
	PORTB|=temp;

	//Latch
	CLR_BIT(PORTA, 2); //EN = 0
	SET_BIT(PORTA, 2); //EN = 1
	_delay_ms(1);
	CLR_BIT(PORTA, 2); //EN = 0

	PORTB &= 0b11101000;  // make PORTA 1.2.3.4 = 0
	//Low
	unsigned char L = (cmd&0x0f);      // L = 0000 1111
	unsigned char temp2 = ((L & 0b00001000) << 1) | ((L & 0b00000111)); // L = 0001 0111
	PORTB|=temp2;

	//Latch
	CLR_BIT(PORTA, 2); //EN = 0
	SET_BIT(PORTA, 2); //EN = 1
	_delay_ms(1);
	CLR_BIT(PORTA, 2); //EN = 0

	_delay_ms(5);	   //wait before next command
}

void LCD_write(unsigned char chr){
	SET_BIT(PORTA, 3); // RS = 1

	PORTB &= 0b11101000;
	//High
	unsigned char H = (chr&0xf0)>>4;      // H = 0000 1111
	unsigned char temp = ((H & 0b00001000) << 1) | ((H & 0b00000111)); // H = 0001 0111
	PORTB|=temp;

	//Latch
	CLR_BIT(PORTA, 2); //EN = 0
	SET_BIT(PORTA, 2); //EN = 1
	_delay_ms(1);
	CLR_BIT(PORTA, 2); //EN = 0

	PORTB &= 0b11101000;  // make PORTA 1.2.3.4 = 0
	//Low
	unsigned char L = (chr&0x0f);      // L = 0000 1111
	unsigned char temp2 = ((L & 0b00001000) << 1) | ((L & 0b00000111)); // L = 0001 0111
	PORTB|=temp2;

	//Latch
	CLR_BIT(PORTA, 2); //EN = 0
	SET_BIT(PORTA, 2); //EN = 1
	_delay_ms(1);
	CLR_BIT(PORTA, 2); //EN = 0

	_delay_ms(5);	   //wait before next write
}

void LCD_writeArray(const char* chr){
	while (*chr) {
		LCD_write(*chr++);
	}
}

void lcd_gotoxy(uint8_t x, uint8_t y) {
uint8_t address = 0;
if (y == 0) {
address = 0x00 + x; //start of line 1
}
else if (y == 1) {
address = 0x40 + x; // start of line 2
}
LCD_cmd(0x80 | address); // Set DDRAM address on LCD
}
