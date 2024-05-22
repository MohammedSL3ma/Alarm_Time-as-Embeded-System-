#include "lcd.h"
#include "Buzzer_Led.h"
#include <util/delay.h>

#ifndef CLOCK_H_
#define CLOCK_H_

// Alarm time variables
volatile unsigned short alarm_hour_1 = 0;
volatile unsigned short alarm_hour_10 = 0;
volatile unsigned short alarm_minute_1 = 0;
volatile unsigned short alarm_minute_10 = 0;
volatile unsigned short alarm_second_1 = 0;
volatile unsigned short alarm_second_10 = 0;
volatile unsigned short alarm_am_pm = 0; // 0 for AM, 1 for PM

// Clock time variables
volatile unsigned short hour_ones = 0;
volatile unsigned short hour_tens = 0;
volatile unsigned short minute_ones = 0;
volatile unsigned short minute_tens = 0;
volatile unsigned short second_ones = 0;
volatile unsigned short second_tens = 0;
volatile unsigned short am_pm = 0; // 0 for AM, 1 for PM

// Flag to indicate alarm activation
volatile unsigned short alarm_active = 0;
short Alarm_Mode = 0; //to display alarm or current time

void Update_clock(){
	
	second_ones++;
	if (second_ones > '9')
	{
		second_ones = '0';
		second_tens++;
		if (second_tens > '5')
		{
			second_tens='0';
			minute_ones++;
			if (minute_ones > '9')
			{
				minute_ones = '0';
				minute_tens++;
				if(minute_tens>'5'){
					minute_tens='0';
					hour_ones++;
					if (hour_ones > '9' && hour_tens == '0'){
						hour_ones = '0';
						hour_tens = '1';
						}
					else if (hour_tens == '1' && hour_ones == '2')
					{
						if (am_pm == '0')
						{
							am_pm = '1';
						}
						else am_pm = '0';
					}
					else if (hour_ones > '2' && hour_tens == '1')
					{
						hour_ones = '1';
						hour_tens = '0';
					}
					
				}
			}
		}
	}
	Time(Alarm_Mode);
	
	// Check if alarm time is reached//
	if (alarm_active && hour_ones == alarm_hour_1 && minute_ones == alarm_minute_1 && second_ones == alarm_second_1)
	{	
		if (hour_tens == alarm_hour_10 && minute_tens == alarm_minute_10 && second_tens == alarm_second_10 && am_pm == alarm_am_pm)
		{
			BUZZER_on();
			LED_on();
		}
		
	}
}

void Set_Time(){
	//    reset time    //
		am_pm = 0;
		hour_ones = 0;
		hour_tens = 0;
		
		minute_ones = 0;
		minute_tens = 0;
		
		second_ones = 0;
		second_tens = 0;
	//___________________//
	
	unsigned char key = 0;
	
	//                      Set hour                              //
		H_tens:
		LCD_cmd(0x01);
		
	key = keypad_get_value();
	if (key>='0' && key<='1'){// hour == ..0:00:00
		hour_tens = (short)key;
		LCD_write(hour_tens);
		
		key = 0; //reset key
		
			H_ones:
			LCD_cmd(0x01);
			
			displayTime(hour_tens, hour_ones, minute_tens, minute_ones, second_tens, second_ones, am_pm);
			
		key = keypad_get_value();
		if (key>='1' && key<='9' && hour_tens=='0'){// hour == 0..:00:00
			hour_ones=(short)key;

			}
			
		else if (key>='0' && key<='2' && hour_tens=='1'){// hour == 1..:00:00
			hour_ones=(short)key;

			}
			
		else {// if user set char instead of number
			LCD_cmd(0x01);
			LCD_writeArray("Please Enter correct number to set hour!!");
			goto H_ones;
		}
		
		key = 0;// reset key
	}
	else{//if user enter invalid number in hour's tens 
		LCD_cmd(0x01);
		LCD_writeArray("Please Enter 0 or 1  to set hour's tens!!");
		_delay_ms(600);
		goto H_tens;
	}
	
	//___________________________________________________________________//
	
	
	//                      Set minute                                  //
		M_tens:
		LCD_cmd(0x01);
		
	displayTime(hour_tens, hour_ones, minute_tens, minute_ones, second_tens, second_ones, am_pm);
	key = keypad_get_value();
	if (key>='0' && key<='5'){// minute == ..0:00:00
		minute_tens =(short) key;
		
			//reset key
		key = 0; 
	
		
		M_ones:
		LCD_cmd(0x01);
		
		displayTime(hour_tens, hour_ones, minute_tens, minute_ones, second_tens, second_ones, am_pm);
		
		key = keypad_get_value();
		if (key>='0' && key<='9'){// minute == 00:0..:00
			minute_ones=(short)key;
		}
		
		else {// if user set char instead of number
			LCD_cmd(0x01);
			LCD_writeArray("Please Enter correct number to set minute!!");
			_delay_ms(600);
			goto M_ones;
		}
		//_delay_ms(200);
		key = 0;// reset key
	}
	else{//if user enter invalid number in minute's tens
		LCD_cmd(0x01);
		LCD_writeArray("Please Enter 0 to 5  to set minute's tens!!");
		_delay_ms(600);
		goto M_tens;
	}
	
	
	//____________________________________________________________________//
	//                        set second                                 //
	S_tens:
	LCD_cmd(0x01);
	
	displayTime(hour_tens, hour_ones, minute_tens, minute_ones, second_tens, second_ones, am_pm);
	key = keypad_get_value();
	if (key>='0' && key<='5'){// second == 00:00:..0
		second_tens =(short) key;

		//reset key
		key = 0;
		
		
		S_ones:
		LCD_cmd(0x01);
		
		displayTime(hour_tens, hour_ones, minute_tens, minute_ones, second_tens, second_ones, am_pm);	
		key = keypad_get_value();
		if (key>='0' && key<='9'){// second == 0..:00:00
			second_ones=(short)key;
		}
			
		else {// if user set char instead of number
			LCD_cmd(0x01);
			LCD_writeArray("Please Enter correct number to set second!!");
			goto S_ones;
		}
		//_delay_ms(200);
		key = 0;// reset key
	}
	else{//if user enter invalid number in second's tens
		LCD_cmd(0x01);
		LCD_writeArray("Please Enter 0 to 5  to set second's tens!!");
		goto S_tens;
	}
	
	//_______________________________________________________________________//
	//                     Set AM or PM                                     //
	AM:
	LCD_cmd(0x01);
	
	displayTime(hour_tens, hour_ones, minute_tens, minute_ones, second_tens, second_ones, am_pm);
	key = keypad_get_value();
	if (key >= '0' && key <= '1')
	{
		if(key == '0')
			am_pm = key; //AM
		else
			am_pm = key; //PM
	}
	else{
		LCD_cmd(0x01);
		lcd_gotoxy(0,0);
		LCD_writeArray("Please press '0' to AM or '1' to PM");
		_delay_ms(600);
		goto AM;
	}
	displayTime(hour_tens, hour_ones, minute_tens, minute_ones, second_tens, second_ones, am_pm);
	//SET_BIT(TIMSK, TOIE0);
	//SET_BIT(SREG, 7);
}

void Set_Alarm_Time(){
	alarm_active = 1;
		//    reset time    //
		alarm_am_pm = '0';
		alarm_hour_1 = '0';
		alarm_hour_10 = '0';
		
		alarm_minute_1 = '0';
		alarm_minute_10 = '0';
		
		alarm_second_1 = '0';
		alarm_second_10 = '0';
		//___________________//

		unsigned char key = 0;
		//_____________________________________________________________//
		//                      Set hour                              //
		H_tens:
		LCD_cmd(0x01);
		
		
		key = keypad_get_value();
		if (key>='0' && key<='1')
		{
			alarm_hour_10 = key;
			
			key = 0; //reset key
			
			H_ones:
			LCD_cmd(0x01); //Clear Screen
			

			displayTime(alarm_hour_10, alarm_hour_1, alarm_minute_10, alarm_minute_1, alarm_second_10, alarm_second_1, alarm_am_pm);
			
			key = keypad_get_value();
			if (key>='1' && key<='9' && alarm_hour_10=='0'){// hour == 0..:00:00
				alarm_hour_1=key;
			}
			
			else if (key>='0' && key<='2' && alarm_hour_10=='1'){// hour == 1..:00:00
				alarm_hour_1=key;
			}
			
			else {// if user set char instead of number
				LCD_cmd(0x01);
				LCD_writeArray("Please Enter correct number to set hour!!");
				goto H_ones;
			}

			key = 0;// reset key
		}
		else{//if user enter invalid number in hour's tens
			LCD_cmd(0x01);
			LCD_writeArray("Please Enter 0 or 1  to set hour's tens!!");
			goto H_tens;
		}
		//___________________________________________________________________//
		//                      Set minute                                  //
		M_tens:
		LCD_cmd(0x01);
		
		displayTime(alarm_hour_10, alarm_hour_1, alarm_minute_10, alarm_minute_1, alarm_second_10, alarm_second_1, alarm_am_pm);
		key = keypad_get_value();
		if (key>='0' && key<='5'){// minute == 00:..0:00
			alarm_minute_10 = key;
			
			//reset key
			key = 0;
			
			M_ones:
			LCD_cmd(0x01);
			

			displayTime(alarm_hour_10, alarm_hour_1, alarm_minute_10, alarm_minute_1, alarm_second_10, alarm_second_1, alarm_am_pm);
			
			key = keypad_get_value();
			if (key>='0' && key<='9'){// minute == 00:0..:00
				alarm_minute_1=key;
			}
			
			else {// if user set char instead of number
				LCD_cmd(0x01);
				LCD_writeArray("Please Enter correct number to set minute!!");
				goto M_ones;
			}
			
			key = 0;// reset key
		}
		else{//if user enter invalid number in minute's tens
			LCD_cmd(0x01);
			LCD_writeArray("Please Enter 0 to 5  to set minute's tens!!");
			goto M_tens;
		}
		
		//____________________________________________________________________//
		//                        set second                                 //
			S_tens:
			LCD_cmd(0x01);
			
			displayTime(alarm_hour_10, alarm_hour_1, alarm_minute_10, alarm_minute_1, alarm_second_10, alarm_second_1, alarm_am_pm);
		key = keypad_get_value();
		if (key>='0' && key<='5'){// second == 00:00:..0
			LCD_cmd(0x01);
			alarm_second_10 = key;

			//reset key
			key = 0;
			
			S_ones:
			LCD_cmd(0x01);
			

			displayTime(alarm_hour_10, alarm_hour_1, alarm_minute_10, alarm_minute_1, alarm_second_10, alarm_second_1, alarm_am_pm);
			
			key = keypad_get_value();
			if (key>='0' && key<='9'){// second == 00:00:0..
				alarm_second_1=key;
			}
			
			else {// if user set char instead of number
				LCD_cmd(0x01);
				LCD_writeArray("Please Enter correct number to set second!!");
				goto S_ones;
			}

			key = 0;// reset key
		}
		else{//if user enter invalid number in second's tens
			LCD_cmd(0x01);
			LCD_writeArray("Please Enter 0 to 5  to set second's tens!!");
			goto S_tens;
		}
		//_______________________________________________________________________//
		//                     Set AM or PM                                     //
		AM:
		LCD_cmd(0x01);
		
		
		displayTime(alarm_hour_10, alarm_hour_1, alarm_minute_10, alarm_minute_1, alarm_second_10, alarm_second_1, alarm_am_pm);
		
		key = keypad_get_value();
		if (key >= '0' && key <= '1')
		{
			if(key == '0')
			alarm_am_pm = key; //AM
			else
			alarm_am_pm = key; //PM
		}
		else{
			LCD_cmd(0x01);
			lcd_gotoxy(0,0);
			LCD_writeArray("Please press '0' to AM or '1' to PM");
			goto AM;
		}
		displayTime(alarm_hour_10, alarm_hour_1, alarm_minute_10, alarm_minute_1, alarm_second_10, alarm_second_1, alarm_am_pm);
	
}

void Time(short Alarm_Mode){
	if (Alarm_Mode == 1){
		displayTime(alarm_hour_10, alarm_hour_1, alarm_minute_10, alarm_minute_1, alarm_second_10, alarm_second_1, alarm_am_pm);
	}
	else{
		displayTime(hour_tens, hour_ones, minute_tens, minute_ones, second_tens, second_ones, am_pm);
	}
	
}

void displayTime(short hour_tens , short hour_ones , short minute_tens, short minute_ones, short second_tens, short second_ones, short am_pm)
{
	LCD_cmd(0x01);
	lcd_gotoxy(5,0);
	if (Alarm_Mode==0)
	{
		LCD_writeArray("Time");
	}
	else if (Alarm_Mode==1)
	{
		LCD_writeArray("Alarm Time");
	}
	
	lcd_gotoxy(0,1);

	LCD_write(hour_tens);
	LCD_write(hour_ones);
	LCD_write(':');
	LCD_write(minute_tens);
	LCD_write(minute_ones);
	LCD_write(':');
	LCD_write(second_tens);
	LCD_write(second_ones);

	if (am_pm == '1')
		LCD_write('P');
	else
		LCD_write('A');

	LCD_write('M');
}

//void Get_Alarm(){
	//if (alarm_active ==1)
	//{
		//LCD_cmd(0x01);
		//lcd_gotoxy(7,0);
		//LCD_writeArray("Alarm: ");
		//lcd_gotoxy(0,1);
		//LCD_write(alarm_hour_10);
		//LCD_write(alarm_hour_1);
		//LCD_write(':');
		//LCD_write(alarm_minute_1);
		//LCD_write(alarm_minute_10);
		//LCD_write(':');
		//LCD_write(alarm_second_10);
		//LCD_write(alarm_second_1);
		//if (alarm_am_pm == '1')
		//LCD_write('P');
		//else
		//LCD_write('A');
//
		//LCD_write('M');
	//}
	//
//}

#endif /* CLOCK_H_ */