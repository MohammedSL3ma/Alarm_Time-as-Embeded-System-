#include "KEYPAD.h"

const unsigned char arr[4][4]={
	{'7' ,'8' ,'9' ,'/'},
	{'4' ,'5' ,'6' ,'x'},
	{'1' ,'2' ,'3' ,'-'},
	{'c', '0', '=' ,'+'}
};

void keypad_init(){
	/*Set pins column as input*/
	CLR_BIT(DDRD,3);
	CLR_BIT(DDRD,5);
	CLR_BIT(DDRD,6);
	CLR_BIT(DDRD,7);
	
	
	/*set pins of rows as output*/
	SET_BIT(DDRC,2);
	SET_BIT(DDRC,3);
	SET_BIT(DDRC,4);
	SET_BIT(DDRC,5);
	
	/*Set col pull up*/
	SET_BIT(PORTD,3);
	SET_BIT(PORTD,5);
	SET_BIT(PORTD,6);
	SET_BIT(PORTD,7);
}

unsigned char keypad_get_value(){
	
	unsigned char row,col, ans = INVALID_KETPAD_PRESS;
	
	start:
	
	for (row = 5; row >= 2; row-- )
	{
		PORTC |= 0b00111100;	//write high on all rows
		CLR_BIT(PORTC,row);		//write low on one raw
		for (col=7;col>=4;col--)
		{
			if(col==4)
				col--;
			if(GET_BIT(PIND,col) == 0){
				_delay_ms(120);
				if(GET_BIT(PIND,col) == 0){
					if(col == 3){
						ans = arr[5-row][7-col-1];
						break;
						
					}
					else{
						
						ans = arr[5-row][7-col];
						break;
					}
					
				}
			}
		}

	}
	if (ans == INVALID_KETPAD_PRESS)
		goto start;
	else{
		BUZZER_on();
		_delay_ms(30);
		BUZZER_off();
		_delay_ms(200); //delay before next check keypad
		return ans;
		
		}
}
