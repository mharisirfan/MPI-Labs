/*
 * LAb2Task2.c
 *
 * Created: 25-Feb-21 10:47:27 AM
 * Author : HP
 */ 

#include <avr/io.h>
#define F_CPU 16000000UL 
#include <util/delay.h>

int main(void)
{
 DDRB = 0xFF; 
 while(1)
 { 
	 PORTB |= (1<<PB3);
	  _delay_ms (1000);
	   PORTB &= ~(1<<PB3);
	    _delay_ms (1000);
		
 } 
 
  return 0;
}

