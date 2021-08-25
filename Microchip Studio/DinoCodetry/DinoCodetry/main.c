
#include <avr/io.h>
#include <stdio.h>
#include <util/delay.h>
void adc_init();
uint16_t adc_read(uint8_t ch);

int main(void)
{
	DDRB= 0xff;          ///Port B as output
	adc_init();          ///calling adc initialize
//	Serial.begin(9600);  /// starting serial monitor to test LDR values on serial monitor of Arduino ide.
	/* 1. Set Fast PWM mode 14: set WGM11, WGM12, WGM13 to 1 */
	/* 3. Set pre-scaler of 64 */
	/* 4. Set Fast PWM non-inverting mode */
	TCCR1A |= (1 << WGM11) | (1 << COM1A1);
	TCCR1B |= (1 << WGM12) | (1 << WGM13) | (1 << CS11) | (1<<CS10);    /// WGM11, WGM12, WGM13 set to 1

	/* 2. Set ICR1 register: PWM period */
	ICR1 = 4999;             /// for 50 hz clk we require 4999 value. f=fclk/(64(prescaler)*(ICR1+1))
	
	/* Local Variables */
	uint16_t ADC_RawData = 0x0000;                   /// for reading one ldr
	uint16_t ADC_RawData1 = 0x0000;
	uint16_t ADC_RawData2 = 0x0000;
	

	while (1)
	{
		//  OCR1A = 0;
		
		ADC_RawData =  adc_read(0); ///Obstacle 1 /// Read ADC Value at Pin PC0 (A0/ADC0)
		ADC_RawData1 = adc_read(1); ///Obstacle 2
		ADC_RawData2 = adc_read(2); ///Background
//		Serial.println(ADC_RawData,DEC);                        /// prints values on serial monitor ide/
		
		
		///CASE 1: when Background is dark and obstacles are light///
		
		//  if(ADC_RawData2  < 460)
		//  {
		if (ADC_RawData <460  )            ///when LDR reads a value less then 460 means a black portion is detected
		{
			//Serial.println("jump");                 ///prints jump on serial monitor
			
			
			//  ADC_RawData =  adc_read(0); ///Obstacle 1
			// Serial.println(ADC_RawData,DEC);
			PORTB |= (1<<PB0);                          ///test led that we used
			OCR1A =295             ;                    ///  106.2 degree movement to press the button according to our requirement.
			_delay_ms(190);
			
			
			
			
		}
		OCR1A = 355      ;; ///120.6 degree movement to release the button acc to our requirement.
		_delay_ms(90);
		//  }
		
		///CASE 2: when Background is light and obstacles are dark///
		
		//  if(ADC_RawData2 > 400)
		//   {
		
	}
}
//}

void adc_init()
{
	// AREF = AVcc
	ADMUX = (1<<REFS0);
	
	// ADC Enable and prescaler of 128
	// 16000000/128 = 125000
	ADCSRA = (1<<ADEN)|(1<<ADPS2)|(1<<ADPS1)|(1<<ADPS0);
}

// read adc value
uint16_t adc_read(uint8_t ch)
{
	// select the corresponding channel 0~7
	// ANDing with '7' will always keep the value
	// of 'ch' between 0 and 7
	ch &= 0b00000111;  // AND operation with 7
	ADMUX = (ADMUX & 0xF8)|ch;     // clears the bottom 3 bits before ORing
	
	// start single conversion
	// write '1' to ADSC
	ADCSRA |= (1<<ADSC);
	
	// wait for conversion to complete
	// ADSC becomes '0' again
	// till then, run loop continuously
	while(ADCSRA & (1<<ADSC));
	
	return (ADC);
}