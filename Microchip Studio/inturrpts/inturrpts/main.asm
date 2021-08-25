;
; inturrpts.asm
;
; Created: 26-Mar-21 9:01:56 AM
; Author : HP
;


; This is interrupt vector table
.org 0x0000
rjmp start
;main program starts here
.org 0x0002 ; jump to the ISR for ext interrup 0

rjmp ISR_INT0

start:
    sbi DDRB,0 ;configure pb0 for output;

	ldi r26, low(EICRA)
	ldi r27, high(EICRA)
	ldi r16, 0x03
	;ldi r16,11    ;configure external interrupt 0 int0 for risning edge
    ;out EICRA,r16
	sbi EIMSK,0   ; enable the external interruopt 0 locally using mask register
	sei           ; enable interuupts globally

;	ldi r16, 0x01  ;configure pb0 for output
;	out DDRB, r16

forever:
    nop
	nop
	rjmp forever

	delay:
	ldi r16, 250
	ldi r17,4

	label1:
	nop
	nop
	nop
	dec r16
	brne label1
	dec r17
	brne label1

ret


ISR_INT0: ;this is the inturret for external inturr 0

sbi PORTB, 0
rcall delay
cbi PORTB, 0
reti  ; return from interrupt