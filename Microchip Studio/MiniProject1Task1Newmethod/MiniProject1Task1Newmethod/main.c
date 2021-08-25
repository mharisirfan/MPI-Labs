/*
 * MiniProject1Task2Newmethod.c
 *
 * Created: 19-Mar-21 10:30:31 PM
 * Author : HP
 */ 
#define F_CPU 8000000UL
#include <avr/io.h>
#include <util/delay.h>

int main(void)
{
	DDRD=0b00000011; // using PD0 and PD1 as input on decoder (A and B)
	DDRB=0b11111111; // using complete PORTB as OUTPUT.
	
    while (1) 
    {
	    PORTD=0x00;                         //setting selection line to 00
    	PORTB=0b11000000;                 // 0  to be displayed on first 7 segment            
		_delay_ms(5);         
	    
		PORTD=0x01;                            //setting selection line to 01
		PORTB=0b11111001;                 //1   to be displayed on second 7 segment
       _delay_ms(5);
	 
	 
	   PORTD=0x02;                               //setting selection line to 02
	   PORTB=0b10100100;                   //2   to be displayed on second 7 segment
       _delay_ms(5);	


        PORTD=0x03;                                  //setting selection line to 03
    	PORTB=0b10110000;                  //3      to be displayed on second 7 segment
	   _delay_ms(5);
		
    }
}

