/*
 * Miniproject2Try.c
 *
 * Created: 28-Apr-21 5:16:40 AM
 * Author : HP
 */ 
#define F_CPU 8000000UL
#include <avr/io.h>
#include <util/delay.h>


int main(void)
{
    /* Replace with your application code */
   DDRC=0xFF;
   
    while (1) 
    {
		PORTC=0x01;
		_delay_us(10);
		PORTC=0x00;
    }
}

