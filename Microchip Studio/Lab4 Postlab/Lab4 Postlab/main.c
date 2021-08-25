#define F_CPU 8000000UL					/* Define CPU Frequency e.g. here its 8MHz */
#include <avr/io.h>						/* Include AVR std. library file */
#include <util/delay.h>					/* Include inbuilt defined Delay header file */

#define LCD_Dir  DDRD					/* Define LCD data port direction */
#define LCD_Port PORTD					/* Define LCD data port */
#define RS PD0							/* Define Register Select (data reg./command reg.) signal pin */
#define EN PD1 							/* Define Enable signal pin */
void LCD_Init (void);
void LCD_String (char *str);
void LCD_Command( unsigned char cmnd );
void LCD_data( unsigned char data );

int main()
{

	LCD_Init();							/* Initialization of LCD*/
	DDRC = 0x03;
	DDRB = 0x00;
	PORTB = 0xff;
	
	unsigned char a = 0xf0;
	unsigned char b = 0xff;

	
	
	
	if ((PINC & (1<<PC4)) == 0)
	{
		a |= (PINC & 0x0f);
	}
	
	while(1)
	{
		if((PINC & (1<<PC4)) != 0)
		{
			b |= (PINC & 0x0f);
			b |= (b<< 4); //b<<4;
			
			b &= 0xf0;
			a = a | b;
			
			LCD_data(a);
			_delay_ms(10000);
		}
		
	}
	
}



void LCD_Command( unsigned char cmnd )
{
	LCD_Port &= 0x0F ;
	LCD_Port |= (cmnd & 0xF0); /* sending upper nibble */
	LCD_Port &= ~ (1<<RS);				/* RS=0, command reg. */
	LCD_Port |= (1<<EN);				/* Enable pulse */
	_delay_us(1);
	LCD_Port &= ~ (1<<EN);

	_delay_us(200);

	LCD_Port &= 0x0F;
	LCD_Port |= (cmnd << 4);  /* sending lower nibble */
	LCD_Port |= (1<<EN);
	_delay_us(1);
	LCD_Port &= ~ (1<<EN);
	_delay_ms(2);
}


void LCD_data( unsigned char data )
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


void LCD_String (char *str)				/* Send string to LCD function */
{
	int i;
	for(i=0;str[i]!=0;i++)				/* Send each char of string till the NULL */
	{
		LCD_data (str[i]);
	}
}

