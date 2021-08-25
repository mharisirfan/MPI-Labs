/*
 * mtry.c
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

	int lookUpTable[32]=
	{0,0,0,0,0,0,1,1 , 0,1,0,0,0,0,0,1 ,0,0,1,0,0,1,0,1, 0,0,0,0,1,1,0,1 };//0 1 2 3
	//9	
	
		
    /* Replace with your application code */
    while (1) 
    {
		//PD7 latch
		//PB0 clock
		
		
		for (int i = 0; i <1; i++) 
              
		{
			for(int j=31; j>=0 ;j--)
			{
				//_delay_ms(40);         //2 secs
				PORTD &= ~(1<<PD7);                        //latch low
				
				
				if(lookUpTable[j]==0)
				{
					
					PORTB &= ~(1<<PB0);                       // clock low
					
					PORTD &= ~(1<<PD4);                      //pin4 low (anode high)
				}
				else if(lookUpTable[j]==1)
				{
					
					PORTB &= ~(1<<PB0);                     //clock low
					PORTD |= (1<<PD4);                      // pin4 high(anodelow)
					
					
				}
				_delay_ms(1000);
					PORTB |= (1<<PB0);                           //clock high
		 	
			}
			
			PORTD|= (1<<PD7);                                  // latch high
		}
	}
	}
		
		
		
	
	
	
