/*
 * Lab12.c
 *
 * Created: 03-Jun-21 8:48:52 AM
 * Author : HP
 */ 

#include <avr\io.h>              // Most basic include files
#include <avr\interrupt.h>       // Add the necessary ones
#include <avr\signal.h>          // here
#define F_CPU 8000000
#define MOSI 3
#define SCK 5 
#define SS 2 
void SPI_byte_send(char ebyte); 
void write_SPI_DAC(unsigned int val); 
void SPI_Init(void); 

int main(void)
{     unsigned int val = 0;
	DDRC=0xFF;  	SPI_Init();
	while (1)    
	 {
		for(int i=0;i<4096;i++)
			write_SPI_DAC(i);
			
		// write code to generate a sawtooth waveform on DAC
			}
} 

 void SPI_byte_send(char ebyte)
{

	//This function send one byte through AVR SPI module
	//This function should ensure that existing communication is complete
	//PORTC = SPSR;
	
	SPDR = ebyte;  
	while(!(SPSR & (1<<SPIF)));
}  void write_SPI_DAC(unsigned int val)
{
	//clear SS
	PORTB &= ~(1<<SS);
	
	//Send upper byte (0b0000xxxx) where xxxx is upper four bits of Digital data
	//Upper nible zero suggest GA'=0 SHDN'=0
	SPI_byte_send(0b00110000 | ( (val>>8) & 0x0F )); //send upper byte
	
	//Send lower 8 bits of digital data
	SPI_byte_send( val & 0xFF ); //send lower byte
	
	//Set SS
	PORTB |= (1<<SS);
	
	//_delay_us(50);
	
}  void SPI_Init()
{
	DDRB |= (1<<SS) | (1<<MOSI) | (1<<SCK);

	SPCR |= (1<<SPE) | (1<<MSTR);
	
} 	// Write code to initialize SPI
