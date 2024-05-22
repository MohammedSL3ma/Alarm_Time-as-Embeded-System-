/*
 * LCD.h
 *
 * Created: 4/10/2023 1:23:04 PM
 *  Author: Ahmed Mohamed Omar
 */ 


#ifndef LCD_H_
#define LCD_H_

#define F_CPU 16000000UL
#include "ATmega32_Rrgiosters.h"
#include "BIT_MATH.h"
#include <util/delay.h>

void LCD_inti(void);
void LCD_cmd(unsigned char cmd);
void LCD_write(unsigned char chr);
void LCD_writeArray(const char* chr);
void lcd_gotoxy(uint8_t x, uint8_t y);

#endif /* LCD_H_ */