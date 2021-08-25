#include <avr/io.h>
#define F_CPU 1000000
#include <util/delay.h>
#define RS PC0
#define EN PC1

void lcd_comm (char);
void lcd_data(char);
void lcd_init (void);


int main(void)
{
	char name[16]={'H','A','R','I','S', 'I','R', 'F', 'A', 'N',' ',' ',' ',' ',' ',' '};
	char rnum[16]={'F','A','1','8','-','B','C','E','-','0','9','0',' ',' ',' ',' '}	;
	while(1)
	{
	
		DDRD = 0xFF;
		DDRC = 0x03;
		lcd_comm(0x38);  //2 lines
		lcd_comm(0x0C);  //cursor off
		//lcd_comm(0x01);   clear screen
		lcd_comm(0xD80);   //force to first line
	
		for(int i=0; i<16;i++)
		{
			_delay_ms(500);
			
			lcd_data(name[i]);
			lcd_comm(0x06);
			if(i==4)
			lcd_comm(20);
			
			          //increametn cur
		}
		lcd_comm(192);
		for(int j=0; j<16;j++)
		{
			_delay_ms(50);
			
			lcd_data(rnum[j]);
			lcd_comm(0x06);
			
			//increametn cur
		}
		return 0;
	}
}

void lcd_comm(char x){
	PORTD = x;
	PORTC &= ~(1<<RS);
	PORTC |= (1<<EN);
	_delay_ms(5);
	PORTC &= ~(1<<EN);
}

void lcd_data(char x){
	PORTD = x;
	PORTC |= (1<<RS);
	PORTC |= (1<<EN);
	_delay_ms(50);
	PORTC &= ~(1<<EN);
}

