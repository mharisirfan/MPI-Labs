/*
 * Lab1Task1.cpp
 *
 * Created: 18-Feb-21 8:46:44 AM
 * Author : HP
 */ 


#include <avr/io.h>
 #define F_CPU 16000000UL 
 #include <util/delay.h>

int main()
{
    /* Replace with your application code */
   DDRD= 0x00;
 
    while (1) 
    {
		PORTD = 0x00;
		 _delay_ms(250); 
		 PORTD =0xFF;
		 _delay_ms(250);
    }
}

