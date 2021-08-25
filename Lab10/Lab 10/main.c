// ***********************************************************
// Project: 	Input Capture
// Author:     Omar Ahmad
// Module description:
//
// This program configures the 16-bit
//	Timer1 of AtMega16 for Input Capture. The expected input
// signal is a periodic pulse train. The task is to find the
// frequency/time period and duty cycle of this signal. The
// frequency of this signal is expected to be less than 4 KHz.
// ***********************************************************

#include <avr/io.h>              // Most basic include files
#include <avr/interrupt.h>       // Add the necessary ones
#include <stdlib.h>
#include <string.h>
#define F_CPU 16000000UL
#include <util/delay.h>
#include <math.h>

/****************** Global Variables ************************/
unsigned int input_capt_counter=0;
unsigned int rising1 = 0;
unsigned int rising2 = 0;
unsigned int falling1 = 0;
unsigned char capture_complete=0;
float sig_freq = 0;
float sig_dc = 0;
/************************************************************/

/****************** Definitions for UART *********************/
#define SERIAL_DEBUG
#ifdef SERIAL_DEBUG
	#include "debug_prints.h"
	#include "debug_prints.c"
#endif

#define BAUD0 57600	// Baud Rate for UART
#define MYUBRR (F_CPU/8/BAUD0-1)	//	U2X = 1
#define GLB_INTR_EN		asm("sei");
#define GLB_INTR_DIS	asm("cli");

#define TRUE 1
#define FALSE 0

/*************** Function Prototypes here ********************/
void timer_init(void);			// Function to initialize Timer1 for Input Capture
void display_counter_values(void);
void display_signal_parameters(void);
void calculate_signal_param(void);
// ***********************************************************

// ***********************************************************
// Main program
//
int main(void)
{
	DDRB &= (1<<PB0); // Set PB0 (ICP1) for input
	PORTB|= (1<<PB0); // Activate internal pull-up
	
	
	UART0_init(MYUBRR);
	printSerialInt(MYUBRR);
	printSerialStrln("");
	printSerialStr("F_CPU = ");
	printSerialInt((int)(F_CPU/1000000));
	printSerialStrln("MHz");
	printSerialStrln("Lab 10: Input Capture");
	timer_init();
	
	//******* Write Code For This ********//
		// Set interrupt sense control bits to falling edge for INT0
		// Enable INT0 locally
		// Set Input Capture Interrupt here

	GLB_INTR_EN;	// Enable interrupts globally
	int i=0;
	
	while(1)
   {
    	if(capture_complete == TRUE)
    	{
    	 	
    	 	display_signal_parameters();	// display frequency and duty cycle on LCD
    	 	capture_complete = FALSE;
			
    	 	for(i=0; i<8; i++)	// wait for 2 seconds
    	 	_delay_ms(250);
    	 	
			printSerialStrln("Press the button ..");
    	}

   }

}


/* This function will setup Timer1 for Input Capture Mode.
if Fclk = 1MHz, and prescaler = 1, then 1 count = 1us. 1000
counts will fit a Time period of 1ms (f = 1 KHz). 250 Counts
will fit a Time period of 0.25 ms (f = 4 KHz).
*/
void timer_init(void)	// Write code for this function
{
	// Normal Mode, OC1A and OC1B disconnected.
	// Capture rising edge. Prescaler = 1
	// Do not enable interrupt of Timer 1 input capture here
}


/* Interrupt Service Routine for INT0. When the user presses 
the button, the ISR clears TCNT1, capture_complete, rising1,
rising2 and falling1 global variables. Then it turns on the 
interrupts for Timer1 Input Capture. It also clears the LCD so
that the next capture can be displayed */
ISR(INT0_vect)
{
  	rising1 = 0;
	rising2 = 0;
	falling1 = 0;
	capture_complete = FALSE;
	TCNT1 = 0;	// clear the free running counter of Timer 1
	input_capt_counter = 0;
	sig_freq = 0;
	sig_dc = 0;
	TCCR1B |= (1<<ICES1);	// for rising edge on ICP1
	TIMSK1 |= (1<<ICIE1);	// Enable interrupt of Timer 1 input capture
}


/* 	ISR for Input Capture of Timer1. You need to write 
	code and complete this function*/
ISR(TIMER1_CAPT_vect)
{

	input_capt_counter ++;
	if(input_capt_counter == 2) //write and complete the code
	{
			// Record the counter value on first rising edge in 'rising1'
	}
	if(input_capt_counter == 3)	//write and complete the code
	{
			// Record the counter value on second rising edge in 'rising2'
			// Change the polarity of sensing
	}
	if(input_capt_counter == 4) //write and complete the code
	{
			// Record the counter value on next falling edge in 'falling1'
			// disable further interrupts of Timer 1 input capture
		capture_complete = TRUE;	// capture is complete at this point
		calculate_signal_param();  // calculate the Frequency and Duty Cycle of the Input Signal
	}
	
}
/** This function displays the values of the
	captured edges  'rising1', 'rising2', and
	'falling1' on LCD. This function requires the
	LCD cursor to be at home location
*/
void display_counter_values()
{
	printSerialStr("Rising 1: ");
	printSerialLong((long int) rising1);
	printSerialStrln("");
   
	printSerialStr("Rising 2: ");
    printSerialLong((long int) rising2);
	printSerialStrln("");

	printSerialStr("Falling 1:	");
	printSerialLong((long int) falling1);
	printSerialStrln("");
}

/** Function to display the Frequency and Duty Cycle
of the Captured signal. This function requires the
LCD cursor to be at home location*/
void display_signal_parameters(void)
{
 	printSerialStr("Frequency = ");
 	printSerialFloat(sig_freq);
 	printSerialStrln(" Hz");

 	printSerialStr("Duty Cycle = ");
 	printSerialFloat(sig_dc);
 	printSerialStrln(" %");
}

/** This function is called after all the required edges
are captured and saved in global variables 'rising1',
'rising2', and 'falling1'. It calculates the input signal
frequency and its duty cycle and saves them in corresponding
variables.*/
void calculate_signal_param(void)
{
	if((rising2-rising1) != 0) // if denominator is non-zero
	{
		sig_freq = F_CPU/((float)(rising2-rising1)); 	// Here Prescalar = 1 so Ftimer == F_CPU
		sig_dc = 100.0 * ((float)(falling1 - rising2))/((float)(rising2-rising1)); // ON-Time/ Total Time * 100 %
	}
	else
	{
	 	sig_freq = 0;
	 	sig_dc = 0;	
	}
}



