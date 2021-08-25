/*
 * MiniProject1_task1.c
 *
 * Created: 3/7/2021 3:57:05 PM
 * Author : Basim
 */ 

#define F_CPU 16000000UL 
#include <avr/io.h>
#include <util/delay.h>
int main()
{
	DDRB = 0b00000111;
	unsigned char lookUpTable[10]={
		/* fill out the 10 hex codes for the 10 digits*/
        0xC0,0xF9,0xA4,0xB0,0x99,
        0x92,0x82,0xF8,0x80,0x90
    };
	unsigned char counter = 0;
	while(1){	// Infinite loop; define here the
		int serial = lookUpTable[counter];
		
		for(int i=0;i<8;i++){
			if(serial & 0b10000000)
				PORTB |= (1<<PB0);
			else
				PORTB &=~ (1<<PB0);
			PORTB |= (1<<PB1); // Giving pulse to SHIFT CLOCK SH_CP
			PORTB &=~ (1<<PB1); // To store from DS to LSB of register
			serial=serial<<1;
		}
		PORTB|=(1<<PB2); // Giving pulse to STORE CLOCK ST_CP 
		PORTB&=~(1<<PB2); // To parallel push data from register to output pins
		_delay_ms(2000);
		
		counter++;
		if(counter == 10)
			counter = 0;
	}
}