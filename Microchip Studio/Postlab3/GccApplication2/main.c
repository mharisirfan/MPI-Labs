#include <avr/io.h> // Most basic include files
#define F_CPU 16000000UL
#include<util/delay.h>


int main(void){

	DDRB=0xFF;
	DDRD=0xFF;
	
	unsigned char lookUpTable[10]={0xC0,0xF9,0xA4,0xB0,0x99,0x92,0x82,0xF8,0x80,0x90};

	while(1) { 	// Infinite loop; define here the

		for(int i=0; i<10;i++)
		{
			PORTD=lookUpTable[i];
		for(int j=0;j<10;j++)
		{
			PORTB= lookUpTable [j];
		_delay_ms(400);
		
		}
		}
	}
	return 0;
}
