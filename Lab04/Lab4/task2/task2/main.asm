;
; prelabTask6.asm
;
; Created: 10-Apr-21 11:10:41 PM
; Author : HP
;
; Replace with your application code


ldi r16, 0xf0  ;i/o 1100 0011
out DDRB, r16
ldi r16, 0x0f
out PORTB, r16 ;pull ups 0011 1100

start:

in  r17, PINB
ANDI r17, 0x0f
sbi PORTB, 6
call _delayFind
cbi PORTB,6
call _delayFind

jmp start

_delayFind:

ldi R20,63
cpi r17, 15
breq delay


ldi R20,67
cpi r17, 14
breq delay


ldi R20,71
cpi r17, 13
breq delay

ldi R20,77
cpi r17, 12
breq delay


ldi R20,83
cpi r17, 11
breq delay


ldi R20,91
cpi r17, 10
breq delay


ldi R20,100
cpi r17, 9
breq delay


ldi R20,111
cpi r17, 8
breq delay


ldi R20,125
cpi r17, 7
breq delay


ldi R20,142
cpi r17, 6
breq delay


ldi R20,166	
cpi r17, 5
breq delay


ldi R20,200
cpi r17, 4
breq delay


ldi R20,250
cpi r17, 3
breq delay

ldi R19,2
cpi r17, 2
breq delayy

ldi R19,3
cpi r17, 1
breq delayy


ldi R19,6
cpi r17, 0
breq delayy

l2:
ret

delay:
    L11:
		nop
		dec R20
		brne L11
  rjmp l2
delayy:
    L3:
	ldi R20,166
    L13:
		nop
		dec R20
		brne L13

		dec R19
		brne L3
  rjmp l2

