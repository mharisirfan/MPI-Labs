/*
 * MiniProject1Task1.c
 *
 * Created: 09-Mar-21 11:42:11 PM
 * Author : HP
 */ 

#include <avr/io.h>
#define F_CPU 1000000UL
#include<util/delay.h>
int main(void)
{
	
	DDRB=00000001;
	DDRD=10010000;

	int lookUpTable[10][8]={
		{0,0,0,0,0,0,1,1}, //0
		{1,0,0,1,1,1,1,1}, //1           a b c d e f g dp
		{0,0,1,0,0,1,0,1}, //2
		{0,0,0,0,1,1,0,1}, //3
		{1,0,0,1,1,0,0,1}, //4
		{0,1,0,0,1,0,0,1}, //5
		{0,1,0,0,0,0,0,1}, //6
		{0,0,0,1,1,1,1,1}, //7             ///0 is for on 1 is for 0ff left to right a-g then dp
		{0,0,0,0,0,0,0,1}, //8
		{0,0,0,0,1,0,0,1}, //9
		
	};
	/* Replace with your application code */
	while (1)
	{
		//PD7 latch
		//PB0 clock
		
		
		for (int i = 0; i < 10; i++)
		
		{
			for(int j=7;j>=0;j--)
			{
				_delay_ms(4000);         //2 secs
				PORTD &= ~(1<<PD7);                        //latch low
				
				
				if(lookUpTable[i][j]==0)
				{
					
					PORTB &= ~(1<<PB0);                       // clock low
					
					PORTD &= ~(1<<PD4);                      //pin4 low (anode high)
				}
				else if(lookUpTable[i][j]==1)
				{
					
					PORTB &= ~(1<<PB0);                     //clock low
					PORTD |= (1<<PD4);                      // pin4 high(anodelow)
					
					
				}
				_delay_ms(100);
				PORTB |= (1<<PB0);                           //clock high
				
			}
			
			PORTD|= (1<<PD7);                                  // latch high
		}
	}
}


