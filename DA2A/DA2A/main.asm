;
; DA2A.asm
;
; Created: 3/2/2019 12:15:47 AM
; Author : David Flores
;


; Replace with your application code

.CSEG
.org	0x0000
	
 LDI R16,0b0001_00		;representing PB5
 OUT DDRB, R16			;enable PB5 as output
 LDI R17,0				;used to set or reset PB5
 LDI R20,5				;set clock prescaler to 1024
 STS TCCR1B,R20			;store value of R20 into TCCR1B

begin:
 LDI R20,0x00			;resets the counter to 0
 STS TCNT1H,R20			;stores value of R20 into TCNT1H
 STS TCNT1L,R20			;stores value of R20 into TCNT1L
 RCALL delay1			;calls timer to wait for 0.435 sec
 EOR R17,R16			;XOR Registers to toggle LED
 OUT PORTB,R17			;Sends value of R17 into PORTB
 LDI R20,0x00			;resets the counter to 0
 STS TCNT1H,R20			;stores the higher bits of value in R20 into TCNT1H
 STS TCNT1L,R20			;stores the lower bits of value of R20 into TCNT1L
 RCALL delay2			;calls timer to wait for 0.29 sec
 EOR R17,R16			;XOR registers to toggle led
 OUT PORTB,R17			;Sends value of R17 into PORTB
 RJMP begin				;repeat main loop

delay1:
 LDS R29, TCNT1H		;loading upper bit of counter to R29
 LDS R28, TCNT1L		;loading lower bit of counter to R28
 CPI R28,0x8C			;comparing if lower 8 bits of timer is 0x08
 BRSH body1				;if lower bits of timer have reached desired amount, check the upper bits
 RJMP delay1			;otherwise, keep checking lower bits

body:
 CPI R29,0x1A			;check to see if upper timer bits have reached the desired value
 BRLT delay1			;if not, recheck the lower bits
 RET					;once the timer reached the desired value, toggle the LED


delay2:
 LDS R29, TCNT1H		;loading upper bit of counter to R29
 LDS R28, TCNT1L		;loading lower bit of counter to R28
 CPI R28,0b10110010		;comparing if lower 8 bits of timer
 BRSH body1				;if lower bits of timer have reached desired amount, check the upper bits
 RJMP delay2			;otherwise, keep checking lower bits

body1:
 CPI R29,0b01000110		;check to see if upper bits of the timer has reached the desired value
 BRLT delay2			;if not, recheck the lower bits
 RET					;once the timer reached the desired value, toggle the LED
