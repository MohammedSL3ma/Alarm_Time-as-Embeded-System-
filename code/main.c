//___________________________________Team IC_________________________________________//

#define F_CPU 16000000UL
#include <avr/io.h>
#include "ATmega32_Rrgiosters.h"
#include "Clock.h"
#include "BIT_MATH.h"
#include "Buzzer_Led.h"
#include "lcd.h"
#include "KEYPAD.h"
#include "timer.h"


int main(void)
{
	LCD_inti();
	keypad_init();
	timer0_init();
	BUZZER_LED_init();
    unsigned char key = 0;
	unsigned short Two_click = 0;
	timer0_setCallback(Update_clock);
	
	lcd_gotoxy(5,0);
	LCD_writeArray("SET Time!!");
	Set_Time();
    while (1) 
    {
		key = keypad_get_value();
		if (key == 'x')
		{
			Set_Time();
			key = 0;
		}
		else if(key == '-' && (Two_click == 0 && Alarm_Mode == 0)){
			Alarm_Mode = 1;
			Set_Alarm_Time();
			key = 0;
			Two_click = 1;
		}
		
		else if (key == '-' && (Two_click == 1 || Alarm_Mode == 1)){ 
			Alarm_Mode = 0;
			key = 0;
			Two_click = 0;
		}
		
		else if(key == '+'){
			
			BUZZER_off();
			LED_off();
			key = 0;
		}
		
		else if(key == '='){
			Alarm_Mode = 1;
			displayTime(alarm_hour_10,alarm_hour_1,alarm_minute_10,alarm_minute_1,alarm_second_10,alarm_second_1,alarm_am_pm);
			
			key = 0;
		}
    }
}

