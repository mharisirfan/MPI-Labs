;
; LCD_Assembly.asm
;
; Created: 3/11/2021 9:09:02 AM
; Author : ABDUL AHAD
;


; Replace with your application code
.equ RS = 0
.equ En = 1

.org 0x0000

	rjmp start

.org 0x0034

start:
	ldi R16, 0xFF	; Set PortB to output
    out DDRB, R16
	out DDRD, R16	; Set PortD to output

	rcall LCD_Init	; Initiallize the LCD
	
	rcall DisplayNums	; Display Numbers 0-9 on the LCD

forever:
	nop
rjmp forever	; Do nothing in a never ending loop


delay_1ms:	; This function will generate a delay of approximately 1 ms on an 8-MHz Atmega328p 
	push R16
	push R17
	ldi R17, 8
	L1: 
	ldi R16, 250
    L11:
		nop
		dec R16
		brne L11
		
		dec R17
		brne L1
	pop R17
	pop R16
ret 

delay_50ms:
	push R16
	ldi R16, 50
	L2:
	rcall delay_1ms
	dec R16
	brne L2
	pop R16
ret

LCD_Send_Command:	; This function assumes that command byte is in R18.
	
	cbi PORTB, RS	; Clear RS for command
	out PORTD, R18	; Output the command byte on PORTD
	rcall LCD_Pulse_En	; Send a 1 ms pulse on En (PB1)
ret


LCD_Send_Data:	; This function assumes that data byte is in R18.

	sbi PORTB, RS	; Set RS for data
	out PORTD, R18	; Output the data byte on PORTD
	rcall LCD_Pulse_En	; Send a 1 ms pulse on En (PB1)
ret

LCD_Pulse_En:
	sbi PORTB, En	; Set En high
	rcall delay_1ms	; wait for 1ms
	cbi PORTB, En
ret


LCD_Init:
	rcall delay_50ms	; wait for more than 40ms
	
	ldi R18, 0x30	; send command 0x30
	rcall LCD_Send_Command

	rcall delay_1ms	; delay of more than 4.1 ms
	rcall delay_1ms
	rcall delay_1ms
	rcall delay_1ms

	ldi R18, 0x30	; send command 0x30
	rcall LCD_Send_Command

	rcall delay_1ms	; wait more than 100 us

	ldi R18, 0x38	; send command 0x38 (2 lines, 5x7 size)
	rcall LCD_Send_Command


	ldi R18, 0x0E	; send command 0x08 (Display off)
	rcall LCD_Send_Command


	ldi R18, 0x01	; send command 0x01 (Clear display)
	rcall LCD_Send_Command


	ldi R18, 0x0F	; send command 0x0F (Entry mode set)
	rcall LCD_Send_Command

ret

DisplayNums:

	push R18	; save R18 to the stack
	push R17	; save R17 to the stack
	
	ldi R18, '0'		; R18 holds ASCII value for 0
	ldi R17, ('9'+1)	; Loop has to run till digit 9 has been displayed

	L3:
		rcall LCD_Send_data
		inc R18
		cp R18, R17
		BRNE L3
	
	pop R17		; restore R17
	pop R18		; restore R18
ret


