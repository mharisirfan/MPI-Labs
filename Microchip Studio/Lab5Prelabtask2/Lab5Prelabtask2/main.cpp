#include <avr/io.h>
#define F_CPU 1000000UL
#include <util/delay.h>

int LCD_Send_Array(char * ptr);
void LCD_Send_Data( unsigned char data );
void LCD_Send_Command( unsigned char comm );
void LCD_init ();

int main()
{
	LCD_init();
	while (1)
	{	
		LCD_Send_Data(PINB);
		_delay_ms(5000); //delay to wait before next read
	}

}
void LCD_init ()
{
	DDRD = 0xFF;
	DDRC = 0xFF;
	DDRB = 0x00; // 
	PORTB = 0xFF; // For pull up
	_delay_ms(100);


	LCD_Send_Command(0x02);
	_delay_ms(2);
	LCD_Send_Command(0x28);
	_delay_ms(2);
	LCD_Send_Command(0x0C);
	_delay_ms(2);
	LCD_Send_Command(0x06);
	_delay_ms(2);
	LCD_Send_Command(0x01);
	_delay_ms(2);
}
void LCD_Send_Command( unsigned char comm )
{
	
	PORTC &=~(1<<PC0);
	PORTD = (PORTD & 0x0F);  
	PORTD = (comm>>4); 
	PORTC |= (1<<PC1);
	_delay_ms(2);
	PORTC &=~(1<<PC1);
	
	_delay_ms(100);
	PORTD = (comm & 0x0F);
	PORTC |= (1<<PC1);
	_delay_ms(2);
	PORTC &=~(1<<PC1);
}

void LCD_Send_Data( unsigned char data )
{
	
	PORTC |=(1<<PC0);
	PORTD = (PORTD & 0x0F); 
	PORTD = (data>>4); 
	PORTC |= (1<<PC1);
	_delay_ms(2);
	PORTC &=~(1<<PC1);
	
	_delay_ms(100);

	PORTD = (PORTD & 0xF0);
	PORTD = (data & 0x0F);
	PORTC |= (1<<PC1);
	_delay_ms(2);
	PORTC &=~(1<<PC1);
}


