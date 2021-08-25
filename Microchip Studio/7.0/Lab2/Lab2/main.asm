;
; Lab2.asm
;
; Created: 25-Feb-21 10:21:46 AM
; Author : HP
;


; Replace with your application code

LDI R16, 10 
LDI R18, 0xFF
LDI R20, 0
LDI R21, 3
OUT DDRB, R18 
AGAIN: 
ADD R20, R21 
OUT PORTB, R20
