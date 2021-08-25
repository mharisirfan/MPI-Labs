#include<avr/interrupt.h>
#include<avr/io.h>
#define F_CPU 16000000UL
unsigned char counter=0;
ISR(INT0_vect){
	// WRITE YOUR CODE HERE
	counter++;
	PORTB = counter;

}
ISR(INT1_vect){
	// WRITE YOUR CODE HERE
counter= 0x00;
PORTB = counter;

}
int main(){
   DDRB= 0XFF;
   counter=0;
  SREG |=(1<<7);
 EIMSK|=(1<<INT0);
 EIMSK|=(1<<INT1);
 EICRA|= (1<<ISC01);
 EICRA|= (1<<ISC11);

	while(1) 
	
	{
		
	}
}