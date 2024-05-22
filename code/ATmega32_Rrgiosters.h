/*
 * ATmega32_Rrgiosters.h
 *
 * Created: 27/10/2020 13:55:54
 *  Author: 20114
 */ 


#ifndef ATMEGA32_RRGIOSTERS_H_
#define ATMEGA32_RRGIOSTERS_H_



#define DDRA *(volatile unsigned char*)(0x3A)
#define PINA *(volatile unsigned char*)(0x39)
#define PORTA *(volatile unsigned char*)(0x3B)


#define DDRB *(volatile unsigned char*)(0x37)
#define PINB *(volatile unsigned char*)(0x36)
#define PORTB *(volatile unsigned char*)(0x38)


#define DDRC *(volatile unsigned char*)(0x34)
#define PINC *(volatile unsigned char*)(0x33)
#define PORTC *(volatile unsigned char*)(0x35)


#define DDRD *(volatile unsigned char*)(0x31)
#define PIND *(volatile unsigned char*)(0x30)
#define PORTD *(volatile unsigned char*)(0x32)

#define SREG *(volatile unsigned char*)(0x5F)

#endif /* ATMEGA32_RRGIOSTERS_H_ */