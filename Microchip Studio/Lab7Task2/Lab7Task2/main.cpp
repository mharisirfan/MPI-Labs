#include<avr/interrupt.h>
#include<avr/io.h>
#define F_CPU 16000000UL
#include <util/delay.h>
void delay();
unsigned char counter=0;
volatile unsigned int interrupt_flag = 0;
ISR(INT0_vect){
	// WRITE YOUR CODE HERE
	
	counter=PINB;
	 PORTC|=(1<<PC0);
	 PORTC|=(1<<PC1);
	 PORTC|=(1<<PC2);
	 PORTC&=~(1<<PC3);

	for(int i=16000000;i>=0;i--)
	{

	if(interrupt_flag==1)
	break;
	
    }
    
	
	   	 PORTC &=~(1<<PC0);
       	 PORTC &=~(1<<PC1);
       	 PORTC &=~(1<<PC2);
         PORTC|=(1<<PC3);

}
ISR(INT1_vect){
	// WRITE YOUR CODE HERE

 	 PORTC &=~(1<<PC0);
 	 PORTC &=~(1<<PC1);
 	 PORTC &=~(1<<PC2);
 	 PORTC|=(1<<PC3);

}
void delay()
{
	for(int j=0;j<160000;j--)
	{
		
	}
}


int main(){
	DDRB= 0X00;
	PORTB=0xFF;
	DDRC= 0xFF;
	counter=0;
	
	SREG |=(1<<7);
	EIMSK|=(1<<INT0);
	interrupt_flag = 1;
	EIMSK|=(1<<INT1);
	EICRA|= (1<<ISC01);
	EICRA|= (1<<ISC11);

	while(1)	
	{
		
	}
}