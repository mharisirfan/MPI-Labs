/* In this code the students will configure the USART of the
* ATMega328P Micro controller for Asynchronous Communication.
* The students will choose appropriate values for UBRRH and
* UBRRL registers for the desired Baud Rate. Then the Trans-
* -emitter and the receiver of the USART will be Enabled. The
* students will verify the correctness of their design on the
* Virtual Terminal in Proteus Simulation. The
* students will also test their design Hardware
*/
/*************************************************************/
#define F_CPU 8000000UL // a System clock of 16 MHz
#include <avr\io.h> // Most basic include files
#include <avr\interrupt.h> // Add the necessary ones
#include <util\delay.h>
#include <string.h>

// ************** Definistion for USART **********************
#define BAUD 9600.00 // Baud Rate Declared as a float
#define UBRR_VAL (F_CPU/(8*BAUD))-1 // Corresponding UBRR Value
// ***********************************************************
void USART_Init(unsigned int ubrr); // function to Initialize the USART
void USART_Transmit(unsigned char data);// Transmit Data via USART
unsigned char USART_Receive(void); // Receive Data via USART
void USART_send_str(char * string1); // Transmit a string
void USART_read_str(char * ); // Read the USART buffer
void soft_UART_send(unsigned char data);
// ***********************************************************
unsigned int data_available = 0;
// A flag to indicate that data is available in the receive buffer
// Main program
int main(void){
	DDRB=0xFF;
	USART_Init((unsigned int)UBRR_VAL);
	unsigned char data;
	while(1){
		// Infinite loop; define here the
		data = USART_Receive();
		_delay_ms(20); // 20 ms Delay between rx & tx of data
		USART_Transmit(data);
		soft_UART_send(data);
	}
}
void USART_Init(unsigned int ubrr){
	/* Set baud rate */
	UBRR0H = (unsigned char)(ubrr>>8);
	UBRR0L = (unsigned char)ubrr;
	/*Complete this code*/
	/* set double speed operation to reduce Baudrate Error*/
	   UCSR0A|=(1<<1);// UCSR0A
	/* Enable receiver and transmitter */
	   UCSR0B|=(1<<3)|(1<<4);//UCSR0B
	/* Set frame format: 8 data, 1 stop bit, odd parity */
	    UCSR0C|=(1<<4)|(1<<5);//UCSR0C
}
void USART_Transmit(unsigned char data){
	/* Wait for empty transmit buffer */
	while ( !( UCSR0A & (1<<UDRE0)) );
	/* Put data into buffer, sends the data */
	UDR0 = data;
}
unsigned char USART_Receive(void){
	/* Wait for data to be received */
	while ( !(UCSR0A & (1<<RXC0)) );
	/* Get and return received data from buffer */
	return UDR0;
}
void USART_send_str(char * str){
	char i=0;
	for(i=0; i<strlen(str); i++){
		USART_Transmit(str[i]);
	}
}
void USART_read_str(char * str){
	char ch; unsigned int i=0;
	do{
		ch = USART_Receive();
		str[i] = ch;
		i++;
	}while(ch != '\0');
}

void soft_UART_send(unsigned char data)
{
	PORTB &=~(1<<PB1);
	
	_delay_us(UBRR_VAL);
	uint8_t  val_comp=00000001;

	while (val_comp!=0x00)
	{
		if(data & val_comp)
		{
			PORTB |=(1<<PB1);
		     val_comp=(val_comp<<1);
		}
		else
		{
	        PORTB &=~(1<<PB1);
	        val_comp=(val_comp<<1);
		}
		_delay_us(UBRR_VAL);
		
	}
	_delay_us(UBRR_VAL);
	_delay_us(UBRR_VAL);
			PORTB |=(1<<PB1);			
}