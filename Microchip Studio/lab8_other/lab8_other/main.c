
//********************************************************************
// Module description:
/*
In this lab the students will learn to use the Analog to Digital
Converter present as a peripheral device in Atmega328p MCU. The ADC has
a 10- bit resolution and offers 8 channels for single ended conversions.
The students will explore two modes of operation of the ADC for single
ended conversions:
1. Single Conversion Mode
2. Auto Trigger Mode (Free running sub-mode)
Task1:
Interface a temperature sensor (LM35) using the ADC of Atmega328P MCU
Task2:
Record an analog signal using the ADC and output to a DAC after
processing
*/
//********************************************************************
#include <inttypes.h>
#include <stdlib.h>
#include <avr/io.h>
#include <avr/interrupt.h>
#define F_CPU 8000000UL
#include <util/delay.h>
#include <string.h>
#include <math.h>
/*
This part allows you to choose which section of the code to compile
*/
//Comment out this line to activate task 2 compilation
#define TASK1 // Activate Task1 code compilation /*???*/
// If Task 1 not activated then activate Task 2 code compilation
#ifndef TASK1 /*???*/
#define TASK2
#endif
#ifdef TASK1
#define SERIAL_DEBUG // Using UART for Task 1
#define ADC_MODE 1 // ADC will be initialized in Single
//Conversion Mode
#endif
#ifdef TASK2
#define USE_DAC // Using DAC for Task 2
#define ADC_MODE 2 // ADC will be initialized in Free Running
//Mode
#endif
/****************** Definitions for UART *********************/

#ifdef SERIAL_DEBUG /*???*/
#include "debug_prints.h"
#include "debug_prints.c"
#define BAUD0 9600 // Baud Rate for UART
#define MYUBRR (F_CPU/8/BAUD0-1)
#endif
// U2X = 1
/********************************************************************/
#define ADC_CHANNEL0 0
#define ADC_CHANNEL1 1
#define ADC_CHANNEL2 2
#define ADC_VREF 5 // Ref voltage for ADC is 5 Volts
#define ADC_RES 10 // Resolution of ADC in bits
#define ADC_QLEVELS 1024 // Quantization levels for the ADC
/*???*/
unsigned char ADC_Initialize(unsigned char mode);
// Initialize ADC. Mode 1 = Single Conversion, Mode 2 = Free Running
unsigned int ADC_Read(unsigned char channel);
// Reads the result of a single conversion from the ADC
/*???*/
float ADC_Convert(unsigned int);
unsigned char VinToTemp(float Vin);
unsigned char read_temp_sensor(unsigned char ADC_channel);
#ifdef TASK2
#define DAC_DDR DDRD
#define DAC_PORT PORTD
ISR(ADC_vect)
{
	DAC_PORT = ADCH; // output the digital value on DAC Port
}
#endif
#define TEMP_SENSOR_CHANNEL ADC_CHANNEL0

/*****************************************************************/
int main(void)
{
	ADC_Initialize(ADC_MODE);
	DIDR0=0xFF;
	/*???*/
	#ifdef TASK1
	UART0_init(MYUBRR); //(F_CPU/8/BAUD0-1)
	printSerialStrln("Lab 8: ");
	unsigned char temperature;
	DDRD = 0xFF;
	while(1)
	{
		/*???*/
		printSerialStr("Temperature is: ");
		temperature = read_temp_sensor(TEMP_SENSOR_CHANNEL);
		printSerialInt(temperature);
		printSerialStr("\r \n");
		PORTD = temperature;
	}
	#endif
	/*???*/
	#ifdef TASK2
	DAC_DDR = 0xFF; // Configure port for output
	ADMUX &= ~(0x07); // clear previous selection of channel
	ADMUX |= ADC_CHANNEL1; // Select the new channel
	//write command for this // Enable interrupts globally
	//write command for this // Trigger the free running ADC
	while(1);
	#endif
	
}
/*
Function Initializes the ADC for 10-Bit Single Conversion
(mode == 1) Or Free Running (mode == 2) modes.
The function returns 0 if initialization successful.
If mode argument is other than 1 or 2,
the function returns an error code 0x02
*/
/*???*/
unsigned char ADC_Initialize(unsigned char mode)
{
	if(mode == 1)// Single Conversion Mode
	{
		/*???*/
		/*** Write Code for this ***/
	    ADMUX |= (1<<REFS0);
	    //set prescaller to 128 and enable ADC
	    ADCSRA |= (1<<ADPS2)|(1<<ADPS1)|(1<<ADPS0)|(1<<ADEN);
		 
		/*
	     	Left adjust result. Vref = AVCC = 5V
		Select the pre-scaler for 16 MHz System Clock
		Pre-scaler = 64
		Clock for ADC = 125 KHz (should be between 50K to 200K)
		*/
		return(0);
	}
	if(mode == 2) // Free Running Mode
	{
		/*???*/
		/*** Write Code for this ***/
		  ADMUX |= (1<<ADLAR);
		  ADMUX |= (1<<REFS0);
		  ADMUX &= ~(1<<REFS1);
		  
		  ADCSRA |= (1<<ADPS1) |(1<<ADPS2)| (1<<ADEN);
		  ADCSRA &= ~(1<<ADPS0);
		/*
		Left adjust result. Vref = AVCC = 5V
		Select the pre-scaler for 16 MHz System Clock
		Pre-scaler = 128
		Clock for ADC = 125 KHz (should be between 50K to 200K)
		*/
		return(0);
	}
	else
	return (0x02);// return error code: Wrong Mode Selection
}
/*
Function reads the result of a single conversion
from the ADC channel given as an argument
*/
unsigned int ADC_Read(unsigned char channel)
{
	/*???*/
	unsigned char ADC_lo;
	unsigned char ADC_hi;
	unsigned int result;
	ADMUX = (ADMUX & 0xF0) | (channel & 0x0F);
	ADCSRA |= (1 << ADSC);//start conversation
	//Wait until ADC converstain complete. ADSC will be ZERO after completion.
	while(ADCSRA & (1<<ADSC));
	return ADC;
}
/*
This function takes an uint16 as input from the ADC.
This uint16 is an unsigned integer result of the ADC
encoded result. The function then converts this result
to floating point Voltage using the ADC_RES (resolution)
and ADC_REF (reference voltage) defined earlier
*/
float ADC_Convert(unsigned int ADC_value)
{
	float Vin;
	/*???*/
	Vin = ADC_VREF * ((float)ADC_value/ADC_QLEVELS);
	return Vin;
}
/*
This function takes the floating-point Voltage value
as input and converts it to corresponding Temperature
in Celsius for an LM35 in Basic Configuration. The
function returns an 8-Bit integer value of the
Temperature
*/
unsigned char VinToTemp(float Vin)
{
	unsigned char temperature=0;
	// 10 mv per centigrade
	float VoltsPerCentigrade = 0.01;
	/*???*/
	temperature = (unsigned char) floor(Vin/VoltsPerCentigrade);
	// Temperature value returned
	return temperature;
}
/*
This function reads the Value of Temperature Sensor
(LM35) from pre-defined ADC Channel and returns the
result in Degree Celsius as an 8-Bit unsigned int
*/
unsigned char read_temp_sensor(unsigned char ADC_channel)
{
	// Read the sensor Connected at ADC_channel
	unsigned int ADC_value = ADC_Read(ADC_channel);
	// Get the value in floating point
	float Vin = ADC_Convert(ADC_value);
	unsigned char temp_celsius = VinToTemp (Vin);
	// Convert to temprature and return
	return temp_celsius;
}


