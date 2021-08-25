/*
 * Lab05_Task01.c
 *
 * Created: 3/15/2021 11:39:17 AM
 * Author : Omar
 */ 

#include <avr/io.h>
#define F_CPU 8000000UL
#include <util/delay.h>

#define RS PB4
#define En PB5

#define DISPLAY_ON 0x0F
#define CLEAR_DISPLAY 0x01
#define HOME 0x02
#define MODE_8BIT 0x38
#define MODE_4BIT 0x28
#define	GOLINE1 0x80
#define	GOLINE2 0xC0
#define	GOLINE3 0x90
#define	GOLINE4 0xD0

void LCD_sendCommand(unsigned char command);
void LCD_sendData(unsigned char data);
void LCD_initiallize(void);
void LCD_printString(char * sptr);
void LCD_printFloat(float number);
void LCD_printInteger(int num);
void LCD_printHex(uint8_t num);

int8_t read_keypad(void);
unsigned char keypad_lookup_proteus[16] = {'7', '8', '9', '/', '4', '5', '6', 'X', '1', '2', '3', '-', 'C', '0', '=', '+'};
   int main(void)
{
    /* Replace with your application code */
    LCD_initiallize();
	LCD_printString("LCD Initialized!");
	//_delay_ms(500);
	
	LCD_sendCommand(CLEAR_DISPLAY);
	LCD_sendCommand(HOME);
		int num1=0;
		int op=0;
		int num2=0;
		int eq=0;
	    int r=0;
	
	DDRD = 0x00;	// set PortC to input
	PORTD = 0xFF;	// Activate the pull up resistors
	
	while (1) 
    {
		
		num1 = read_keypad();
	    if(num1!=-1)
		LCD_sendData(keypad_lookup_proteus[num1]);
		_delay_ms(50);

		op = read_keypad();
		if(op!=-1)
		LCD_sendData(keypad_lookup_proteus[op]);
		_delay_ms(50);
		
		num2 = read_keypad();
		if(num2!=-1)
		LCD_sendData(keypad_lookup_proteus[num2]);
		_delay_ms(50);

		eq = read_keypad();
        if(eq!=-1)
		
		if(eq==10)
	{	LCD_sendData(keypad_lookup_proteus[eq]);
		r=num1/num2;
		LCD_printInteger(r);	
		_delay_ms(50);
		
		
		switch (op)
		{
			case 12:
		   {
		     	
		        if(r!=-1)
		        {
					LCD_sendCommand(CLEAR_DISPLAY);
					
					_delay_ms(500);
				}			   
			   
			   break;
		   }
			
			case 13:
			{
				
				
				break;
			}
			
			case 14:
			{
				
				
				break;
			}
			
			case 15:
			{
				
				
				break;
			}
			
			
			
		}
	
		}
			
		
    }
}

void LCD_sendCommand(unsigned char command)
{
	PORTB &= ~(1<<RS);	// Clear RS for command
	PORTB &= 0xF0;		// Clear the 4 LSBs
	PORTB |= ((command & 0xF0) >> 4);	// write the 4 MSBs of command
	
	/* send a pulse on the En pin */
	PORTB |= (1<<En);
	_delay_ms(1);
	PORTB &= ~(1<<En);
	
	_delay_ms(1);
	
	PORTB &= 0xF0;		// Clear the 4 LSBs
	PORTB |= (command & 0x0F);	// write the 4 LSBs of command
	
	/* send a pulse on the En pin */
	PORTB |= (1<<En);
	_delay_ms(1);
	PORTB &= ~(1<<En);
}

void LCD_sendData(unsigned char data)
{
	PORTB |= (1<<RS);	// Set RS for data
	PORTB &= 0xF0;		// Clear the 4 LSBs
	PORTB |= ((data & 0xF0) >> 4);	// write the 4 MSBs of data
	
	/* send a pulse on the En pin */
	PORTB |= (1<<En);
	_delay_ms(1);
	PORTB &= ~(1<<En);
	
	_delay_ms(1);
	
	PORTB &= 0xF0;		// Clear the 4 LSBs
	PORTB |= (data & 0x0F);	// write the 4 LSBs of data
	
	/* send a pulse on the En pin */
	PORTB |= (1<<En);
	_delay_ms(1);
	PORTB &= ~(1<<En);
	
}

void LCD_initiallize(void)
{
	DDRB = 0xFF;	// Set port to output
	_delay_ms(45);	// wait more than 40 ms
	LCD_sendCommand(0x30);
	
	_delay_ms(5);	// wait for more than 4.1 ms
	LCD_sendCommand(0x30);
	
	_delay_ms(1);
	LCD_sendCommand(0x02);	//  initializes LCD 16x2 in 4-bit mode.
	
	_delay_ms(1);	// wait for more than 100 us
	LCD_sendCommand(MODE_4BIT); // send command 0x28 (4-bit mode, 2 lines, 5x7 size)
	
	LCD_sendCommand(CLEAR_DISPLAY);
	LCD_sendCommand(DISPLAY_ON);
	
}

void LCD_printString(char * sptr)
{
	int i=0;
	while(sptr[i] != '\0')	// while end of string not reached
	{
		LCD_sendData((unsigned char) sptr[i]);
		i++;
	}
}

void LCD_printFloat(float number)
{
	
}

void LCD_printInteger(int num)
{
	unsigned char num_rep_arr[5];	// A 5 digit number can be held
	if(num < 0)
		LCD_sendData('-');
	int x=0;
	do
	{
		unsigned char temp = (unsigned char) num%10;
		num = num/10;
		//LCD_sendData(temp + '0');
		num_rep_arr[x] = temp + '0';
		x ++ ;
	}while((num != 0) && (x != 5));
	
	for(x--; x >= 0; x--)
	{
		LCD_sendData(num_rep_arr[x]);	
	}
}

void LCD_printHex(uint8_t num)	// "uint8_t" is the same as "unsigned char"
{
	// num = 0xCF = 0B1100 1111	
	unsigned char lookup_array[16] = {'0', '1', '2', '3', '4', '5', '6', '7', '8', '9', 'A', 'B', 'C', 'D', 'E', 'F'};
	
	/* Print a 0X on the LCD */
	LCD_sendData('0');
	LCD_sendData('x');
	
	unsigned char temp = num >> 4;
	LCD_sendData(lookup_array[temp]);
	temp = num & 0x0F;	// Mask the upper four bits to zeros
	LCD_sendData(lookup_array[temp]);
}
/*	This function reads the keypad in a non-blocking manner.
	It returns -1 if none of the keys is pressed, or the 
	index, if the key is pressed.
*/
int8_t read_keypad(void)
{
	PORTD = 0xFF;
	DDRD = 0xF0;	// Columns are inputs and pulled up. 
	PORTD = 0x0F;	// Rows are output and 0
	
	if((~PIND & 0x0F) == 0x00)	// if none of the cols show any key pressed
		return(-1);
	else
	{
		uint8_t col = (~PIND & 0x0F);
		uint8_t col_idx = 0;
		while(col != 1)	// A potential blocking statement here
		{
			col = col>>1;
			col_idx ++;
		}
		PORTD = 0xFF;
		DDRD = 0x0F;	// Rows are inputs and pulled up. Cols are output and 0
		PORTD = 0xF0;
		uint8_t row = ((~PIND & 0xF0) >> 4);
		uint8_t row_idx = 0;
		while(row != 1) // A potential blocking statement here
		{
			row = row >> 1;
			row_idx ++;
		}
		
		uint8_t key_idx = (4 * row_idx) + col_idx;
		return(key_idx);
	}
	
}