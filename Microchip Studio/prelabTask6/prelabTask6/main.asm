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
rcall delay_ms_100

cbi PORTB,3
rcall delay_ms_100

jmp start



delay_ms:

ldi r20,8

a:
ldi r17,250
loop:
nop
dec r17
brne loop

dec r20
brne a
ret



delay_ms_100:
ldi r22,100

loop1:
rcall delay_ms
dec r22

brne loop1
ret
