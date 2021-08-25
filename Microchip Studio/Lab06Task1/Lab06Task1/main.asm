;
; prelabTask6.asm
;
; Created: 10-Apr-21 11:10:41 PM
; Author : HP
;
; Replace with your application code


ldi R18,0xFF
OUT DDRB, R18

start:

sbi PORTB, 3
rcall find_delay:


cbi PORTB,3

rcall delay_us_600

jmp start



find delay:

ldi r16, 0x00
cp r16, PORTB
breq 




delay_us_400:

ldi r23, 5
a:
ldi r22,200

loop2:
nop
dec r22
brne loop2

dec r23 
brne a

ret

delay_us_600:
ldi r23,6
b: 
ldi r22,200

loop1:
nop 
dec r22
brne loop1

dec r23
brne b
ret
