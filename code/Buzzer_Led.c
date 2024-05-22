#include "Buzzer_Led.h"
#include "ATmega32_Rrgiosters.h"
#include "BIT_MATH.h"

void BUZZER_LED_init()
{
	SET_BIT(DDRC,BUZZER_PIN);
	SET_BIT(DDRB, LED_PIN);
	CLR_BIT(PORTC, BUZZER_PIN);
	CLR_BIT(PORTB, LED_PIN);
}

void BUZZER_on()
{
	SET_BIT(PORTC,BUZZER_PIN);
}

void BUZZER_off()
{
	CLR_BIT(PORTC,BUZZER_PIN);
}

void LED_on()
{
	SET_BIT(PORTB,LED_PIN);
}

void LED_off()
{
	CLR_BIT(PORTB,LED_PIN);
}