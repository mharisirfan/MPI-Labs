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
	//char name[16]={'H','A','R','I','S', 'I','R', 'F', 'A', 'N',' ',' ',' ',' ',' ',' '};
	//char rnum[16]={'F','A','1','8','-','B','C','E','-','0','9','0',' ',' ',' ',' '}	;
	while(1)
	{
		
		DDRD = 0xFF;
		DDRC = 0x03;
	      
	PORTD = 0x0C;
	PORTC &= ~(1<<RS);
	
	
	
	
	
	
	
	
	
		return 0;
	}
}

void lcd_comm(char x){
	PORTD = x;
	PORTC &= ~(1<<RS);
	
}

void lcd_data(char x){
	PORTD = x;
	PORTC |= (1<<RS);
	
}

