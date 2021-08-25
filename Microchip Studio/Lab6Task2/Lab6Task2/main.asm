;
; prelabTask6.asm
;
; Created: 10-Apr-21 11:10:41 PM
; Author : HP
;
; Replace with your application code


ldi r18,0xF0
OUT DDRB,r18

ldi r18, 0x0F  // input
OUT PORTB,r18 // pull up


start:

in r20,PINB
ANDI r20,0x0F


sbi PORTB, 6
rcall _delayFind
cbi PORTB,6
rcall _delayFind

jmp start




_delayFind:

ldi r21, 21
cpi r20, 15
breq loop


ldi r21, 22
cpi r20, 14
breq loop


ldi r21, 23
cpi r20, 13
breq loop


ldi r21, 26
cpi r20, 12
breq loop

////////////////////

ldi r21, 28
cpi r20, 11
breq loop


ldi r21, 30
cpi r20, 10
breq loop


ldi r21, 34
cpi r20, 9
breq loop


ldi r21, 37
cpi r20, 8
breq loop

///////////////////////////////////////



ldi r21, 42
cpi r20, 7
breq loop


ldi r21, 48
cpi r20, 6
breq loop


ldi r21, 56
cpi r20, 5
breq loop


ldi r21, 68
cpi r20, 4
breq loop

//////////////////////////////////////////


ldi r21, 84
cpi r20, 3
breq loop
///////////////////////////////

ldi r21, 114
cpi r20, 2
breq loop
///////////////////////////


ldi r21, 177
cpi r20, 1
breq loop
/////////////////////////////




ldi r21, 125
cpi r20, 0
breq forone
//////////////////////////////



loop:

rcall delay_1us
dec r21
brne loop
ret




delay_1us: 
	nop

ret

forone:
ldi r16, 18
rcall delay_1us


loopaa:


dec r16
brne loopaa
dec r21
brne forone

ret