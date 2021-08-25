;
; PrelabLab4task1.asm
;
; Created: 10-Mar-21 9:38:21 PM
; Author : HP
;


; Replace with your application code


sendcommand:
IN R16,PORTC
LDI R17,0xFE
AND R16,R17
OUT PORTC,R16    //4 CLOCK CYCLES
 
OUT PORTD,R18 ;COMMAND BYTE IS IN R18

pulse_en:
sbi PORTC,1
rcall 1_ms
cbi PORTC,1
ret


LDI R16 ,0xFF  //portd
OUT DDRD, R16 //CONFIG PORT D FOR OUTPUT



LDI R19, 0x03
OUT DDRC, R19          ;PC0 FOR OUTPUT RS

LDI R22, 0x01    //RS
OUT PORTC, R22 
           
LDI R20, 0x00
OUT PORTD, R20


LDI R19, 0x02
OUT PORTC, R19 // enable high



LDI R19, 0x00
OUT PORTC, R19 // enable low

