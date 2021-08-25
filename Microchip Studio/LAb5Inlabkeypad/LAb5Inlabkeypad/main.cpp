#define F_CPU 8000000UL					/* Define CPU Frequency e.g. here its 8MHz */
#include <avr/io.h>						/* Include AVR std. library file */
#include <util/delay.h>					/* Include inbuilt defined Delay header file */

#define LCD_Dir DDRB					/* Define LCD data port direction */
#define LCD_Port PORTB					/* Define LCD data port */
#define RS PB0							/* Define Register Select (data reg./command reg.) signal pin */
#define EN PB1 							/* Define Enable signal pin */
void LCD_Init (void);
void LCD_String (char *str);
void LCD_Command( unsigned char cmnd );
void LCD_Char( unsigned char data );
int8_t Keypad(void);
int main()
{
	DDRD=00000000;
	int8_t dataaa;
	PORTC=0xFF;
	while(1)
	{
		
		//pull up
		
		
		LCD_Init();
		
	 dataaa=Keypad();
	if (dataaa==1)
	{
		_delay_ms(200);
		LCD_Char('D');
	}
	}
	
	//	LCD_Init();							/* Initialization of LCD*/
	//LCD_Char('a');
	//LCD_String("Haris ");		/* Write string on 1st line of LCD*/
	//	LCD_Command(0xc0);					/* Go to 2nd line*/
	//LCD_String("Irfan");			/* Write string on 2nd line*/
	
}


int8_t Keypad(void)
{
	DDRD = 0x0F; // Setting upper half pins to input
	PORTD = 0xF0; // Activating pull resistors for upper half pins
	
	if((PIND & 0b10000000) == 0){ //COL 4
		_delay_ms(100);
		DDRD = 0xF0;
		PORTD = 0x0F;
		if((PIND & 0b00001000) == 0){ //ROW A
			return 15;
		}
		else if((PIND & 0b00000100) == 0){ //ROW B
			return 14;
		}
		else if((PIND & 0b00000010) == 0){ //ROW C
			return 13;
		}
		else if((PIND & 0b00000001) == 0){ //COL 4
			return 12;
		}
		else return -1;
	}
	else if((PIND & 0b01000000) == 0){ //COL 3
		DDRD = 0xF0;
		PORTD = 0x0F;
		if((PIND & 0b00010000) == 0){ //ROW A
			return 11;
		}
		else if((PIND & 0b00100000) == 0){ //ROW B
			return 10;
		}
		else if((PIND & 0b01000000) == 0){ //ROW C
			return 9;
		}
		else if((PIND & 0b10000000) == 0){ //ROW D
			return 8;
		}
		else return -1;
	}
	else if((PIND & 0b00100000) == 0){ // COL 2
		DDRD = 0xF0;
		PORTD = 0x0F;
		if((PIND & 0b00010000) == 0){ //ROW A
			return 7;
		}
		else if((PIND & 0b00100000) == 0){ //ROW B
			return 6;
		}
		else if((PIND & 0b01000000) == 0){ //ROW C
			return 5;
		}
		else if((PIND & 0b10000000) == 0){ //ROW D
			return 4;
		}
		else return -1;
	}
	else if((PIND & 0b00010000) == 0){ // COL 1
		DDRD = 0xF0;
		PORTD = 0x0F;
		if((PIND & 0b00010000) == 0){ //ROW A
			return 3;
		}
		else if((PIND & 0b00100000) == 0){ //ROW B
			return 2;
		}
		else if((PIND & 0b01000000) == 0){ //ROW C
			return 1;
		}
		else if((PIND & 0b10000000) == 0){ //ROW D
			return 0;
		}
		else return -1;
	}
	else
	return -1;
}

void LCD_Command( unsigned char cmnd )
{
	LCD_Port &= 0x0F ;
	LCD_Port |= (cmnd & 0xF0); /* sending upper nibble */
	LCD_Port &= ~ (1<<RS);				/* RS=0, command reg. */
	LCD_Port |= (1<<EN);				/* Enable pulse */
	_delay_us(1);
	LCD_Port &= ~ (1<<EN);

	_delay_us(200);           /// when left shift the cmmnd is to the right and vice versa.

	LCD_Port &= 0x0F;
	LCD_Port |= (cmnd << 4);  /* sending lower nibble *///1<<pb0               cmnd <<4             4>>>cmnd    cmnd 11110000
	LCD_Port |= (1<<EN);
	_delay_us(1);
	LCD_Port &= ~ (1<<EN);
	_delay_ms(2);
}


void LCD_Char( unsigned char data )
{
	LCD_Port = (LCD_Port & 0x0F) | (data & 0xF0); /* sending upper nibble */
	LCD_Port |= (1<<RS);				/* RS=1, data reg. */
	LCD_Port|= (1<<EN);
	_delay_us(1);
	LCD_Port &= ~ (1<<EN);

	_delay_us(200);

	LCD_Port = (LCD_Port & 0x0F) | (data << 4); /* sending lower nibble */
	LCD_Port |= (1<<EN);
	_delay_us(1);
	LCD_Port &= ~ (1<<EN);
	_delay_ms(2);
}

void LCD_Init (void)					/* LCD Initialize function */
{
	LCD_Dir = 0xFF;						/* Make LCD command port direction as o/p */
	_delay_ms(20);						/* LCD Power ON delay always >15ms */
	
	LCD_Command(0x33);
	LCD_Command(0x32);		    		/* send for 4 bit initialization of LCD  */
	LCD_Command(0x28);              	/* Use 2 line and initialize 5*7 matrix in (4-bit mode)*/
	LCD_Command(0x0c);              	/* Display on cursor off*/
	LCD_Command(0x06);              	/* Increment cursor (shift cursor to right)*/
	LCD_Command(0x01);              	/* Clear display screen*/
	_delay_ms(2);
	LCD_Command (0x80);					/* Cursor 1st row 0th position */
}


void LCD_String (char * str)			//	/ Send string to LCD function */
{
int i;
for(i=0;str[i]!=0;i++)				/* Send each char of string till the NULL */
{
LCD_Char (str[i]);
}
}