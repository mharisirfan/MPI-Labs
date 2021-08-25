// ***********************************************************
// Project: Delay and Waveform Generation for Different Modes of
//			Timers in Atmega328p AVR MCU
//
// Author:	Omar Ahmad
//
// Module description: This program configures the timing
// sub-system of Atmega328p for different modes of wave-form
// generation. Specifically Timer0 (an 8-bit timer) is configured
// for delay generation. Timer2 is used in the Fast PWM mode. 
// Its two output channels control two servo motors. The objective
// of the program is to demonstrate the capabilities of the
// Timers/Counters of the AVR MCU Atmega328p.
// ***********************************************************

//********************************************************************************/
#include <inttypes.h>
#include <stdlib.h>
#include <avr/io.h>

#define F_CPU 8000000UL
#include <util/delay.h>
#include <string.h>
#include <math.h>


/****************** Definitions for UART *********************/
#define SERIAL_DEBUG

#ifdef SERIAL_DEBUG
#include "debug_prints.h"
#include "debug_prints.c"
#endif

#define BAUD0 9600					// Baud Rate for UART
#define MYUBRR (F_CPU/8/BAUD0-1)	//  U2X = 1

/*********************************************************************************/


#define ADC_CHANNEL0    0
#define ADC_CHANNEL1    1
#define ADC_CHANNEL2    2

#define ADC_VREF    5          // Ref voltage for ADC is 5 Volts
#define ADC_RES     10         // Resolution of ADC in bits
#define ADC_QLEVELS 1024       // Quantization levels for the ADC

unsigned char ADC_Initialize(unsigned char mode);       // Initialize ADC. Mode 1 = Single Conversion, Mode 2 = Free Running
unsigned int ADC_Read(unsigned char channel);   // Reads the result of a single conversion from the ADC
float ADC_Convert(unsigned int);

/******************* Function Prototypes *********************/

void init_timer0(void);		// Initialize Timer0 for 1 ms Delay generation
void init_timer2(void);		// Initialize Timer2 for Fast PWM on two channels
void move_motor(int adc_value);	// value = 0 to 1023 for -90 to 90 degrees angle

// ***********************************************************
// Main program

int main(void)
{
    init_timer0(); // Timer0 configured for delay generation
    init_timer2();	// Timer2 configured for FAST PWM mode (Channel A: for motor 1, Channel B: for motor 2)
   
    ADC_Initialize(1);
    UART0_init(MYUBRR);
    printSerialStr("MYUBRR = ");
    printSerialInt(MYUBRR);
    
    printSerialStrln("");
    printSerialStr("F_CPU = ");
    printSerialInt((int)(F_CPU/1000000));
    
    printSerialStrln("Lab 9: ");
    int adc_value;
    while(1)
    {            
	    adc_value = ADC_Read(0);
	    _delay_ms(20);
	    // Set motor Position
	    move_motor(adc_value);
    }
}

/*	Initialize Timer0 so that it issues an interrupt after every 1 ms
	The ISR for Timer0 should increment a global variable 'unsigned long millis'
	every time the ISR is executed. The ISR should also toggle the output
	at PD6
*/
void init_timer0(void)
{
	DDRD |= (1<<PD6);	// Configure PD6 for output. 
	
}

/*ISR()
{
	
}*/
 

/*	Initialize Timer2 for Fast PWM mode
	System Clock = 8 MHz
	Prescaler = ??
	Required PWM Freq = 50 Hz
*/
void init_timer2(void)
{
	
	DDRB |= (1<<PB3);		// Configure OC2A for output
	DDRD |= (1<<PD3);		// Configure OC2B for output
	
	PRR |= (1<<PRTIM2);		// Enable Timer/Counter 2
	//OCR0A = ;
}

/* Function Initializes the ADC for 10-Bit Single Conversion (mode == 1) or 
Free Running (mode ==2) modes. The function returns 0 if initialization successful. 
 If mode argument is other than 1 or 2, the function returns an error code 0x02*/  
unsigned char ADC_Initialize(unsigned char mode)  
{  
  
   if(mode == 1)	// Single Conversion Mode
   {
      // Left adjust result. Vref = AVCC = 5V
      ADMUX = ((1<<REFS0)|(1<<ADLAR));	
      // Here select the prescaler for 16 MHz System Clock
      // Prescaler = 128
      // Clock for ADC = 125 KHz    (should be between 50K to 200K)
      ADCSRA = ((1<<ADEN)|(1<<ADPS2)|(1<<ADPS1)|(1<<ADPS0));
      return(0);
   }
   if(mode == 2)	// Free Running Mode
   {
       // Left adjust result. Vref = AVCC = 5V
      ADMUX = ((1<<REFS0)|(1<<ADLAR));	
      // Here select the prescaler for 16 MHz System Clock
      // Prescaler = 128
      // Clock for ADC = 125 KHz    (should be between 50K to 200K)
      ADCSRA = ((1<<ADEN)|(1<<ADPS2)|(1<<ADPS1)|(1<<ADPS0)|(1<<ADIE)|(1<<ADATE));
      return(0);
   }
   else
      return (0x02);	// return error code. Wrong Mode Selection
      

}  
/* Function reads the result of a single conversion from the ADC 
    channel given as an argument*/  
unsigned int ADC_Read(unsigned char channel)  
{  
    unsigned char ADC_lo;  
    unsigned char ADC_hi;  
    unsigned int result;  
    ADMUX &= ~(0x07);    // clear previous selection of channel  
    ADMUX |= channel;    // Select the new channel  
    // Delay needed for the stabilization of the ADC input voltage  
    _delay_us(10);  
    //wait for ADC to finish any ongoing operation  
    while((ADCSRA & (1<<ADSC)) != 0);  
    ADCSRA |= (1 << ADSC); //start conversion  
    while((ADCSRA & (1<<ADIF)) == 0);  
    ADCSRA |= (1<<ADIF);  // clear the flag by writing 1 to it  
    //result = (ADCH<<8)|(ADCL & 0xC0);   // Left adjust result  
    ADC_lo = ADCL;  
    ADC_hi = ADCH;  
    result = (ADC_hi<<2)|(ADC_lo >> 6); // Right adjust result  
    return result;  
}  
  
/* This function takes an uint16 as input from the ADC. 
    This uint16 is an unsgined integer result of the ADC 
    encoded result. The function then converts this result 
    to floating point Voltage using the ADC_RES (resolution) 
    and ADC_REF (reference voltage) defined earlier*/  
float ADC_Convert(unsigned int ADC_value)  
{  
   float Vin;  
      
   Vin = ADC_VREF * ((float)ADC_value/ADC_QLEVELS);     
   return Vin;  
}  


void move_motor(int adc_value)	// value = 0 to 1023 for -90 to 90 degrees angle
{
 	/** if we use 8-bit timer then -90 degree (1 ms) correspond to OCR value of approximately 13
 	*   and 90 degree (2ms) correspond to OCR value of approximately 26. So we must map the range
 	*	 of 0-1023 to 13-26*/
 	// Make changes here
}