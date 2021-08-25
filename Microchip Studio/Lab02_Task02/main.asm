;
; Task 2.asm
;
; Created: 2/25/2021 10:32:41 AM
; Author : Omar
;

	ldi r16, 0x08
	out sph, r16

	ldi r16, 0xff
	out spl, r16

; Replace with your application code
start:
    LDI R16, 10 
	LDI R18, 0xFF 
	LDI R20, 0 
	LDI R21, 3 
	
	OUT DDRB, R18 
AGAIN: 
	rcall delay_1sec
	ADD R20, R21 
	OUT PORTB, R20 
	DEC R16 
	BRNE AGAIN

	rjmp start

delay_ms:

	ldi r17, 250

loop:
	nop
	dec r17
	brne loop
ret

delay_1sec:

	ldi r22, 250
	ldi r23, 4
loop1:
	rcall delay_ms
	dec r22
    brne loop1
	dec r23
	brne loop1 
ret