/*
 * MiniProject1Task1Newmethod.c
 *
 * Created: 19-Mar-21 10:30:31 PM
 * Author : HP
 */ 
#define F_CPU 1000000UL
#include <avr/io.h>
#include <util/delay.h>

int main(void)
{
	DDRC=0b00000011;
	DDRD=0b11111111;
	//DDRC=0b00000001;
	
    /* Replace with your application code */
    while (1) 
    {
		
	  
	//	_delay_ms(4000);
		 //1 g f e d c b a
		//PORTD=0b11000000; 
	        //0
    	PORTD=0b11000000;       // 0
        PORTC=0x00;  
		
		_delay_ms(100);         
	    
		
		PORTC=0x01; 
		PORTD=0b11111001;             //1


	_delay_ms(100);
	 
	 
		PORTC=0x02;
	  PORTD=0b10100100;            //2

     _delay_ms(100);	
		  
	    PORTD=0b10110000;  //3
		PORTC=0x03;
            //3
		
	_delay_ms(200);
	
    }
}

