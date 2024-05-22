#ifndef KEYPAD_H_
#define KEYPAD_H_

#define F_CPU (16000000UL)
#include "BIT_MATH.h"
#include "ATmega32_Rrgiosters.h"
#include <util/delay.h>

#define INVALID_KETPAD_PRESS (0xFF)

void keypad_init();
//unsigned char keypad_get_value();
#endif /* KEYPAD_H_ */