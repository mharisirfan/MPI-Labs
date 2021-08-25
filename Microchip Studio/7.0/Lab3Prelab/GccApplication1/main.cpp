#include <avr/io.h> // Most basic include files
#define F_CPU 16000000UL
 #include<util/delay.h> 


int main(void){

	DDRB=0xFF;
	DDRD=0xFF;
	
	unsigned char lookUpTable[10]={0xC0,0xF9,0xA4,0xB0,0x99,0x92,0x82,0xF8,0x80,0x90};
	unsigned char counter= 0;
	
	while(1) { 	// Infinite loop; define here the

	
	PORTB=counter;
		PORTD= lookUpTable [counter];
		_delay_ms(50);
		 
		  counter++; 
		  if(counter==10)
		    counter=0;
	
	}
	return 0;
}
