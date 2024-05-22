#include "ATmega32_Rrgiosters.h"
#include "BIT_MATH.h"

#ifndef BUZZER_LED_H_
#define BUZZER_LED_H_

#define BUZZER_PIN 6
#define LED_PIN 7

void BUZZER_LED_init();

void BUZZER_on();

void BUZZER_off();

void LED_on();

void LED_off();

#endif /* BUZZER_LED_H_ */