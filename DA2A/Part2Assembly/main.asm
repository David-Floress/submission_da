;
; Part2Assembly.asm
;
; Created: 3/4/2019 8:23:54 PM
; Author : David Flores
;


; Replace with your application code
//Part 2

.org	0x0000
 
 LDI R16, 0xFF			;representing PB5
 OUT DDRB, R16			;enable PB5 as output
 LDI R17,0				;used to set or reset PB5
 CBI DDRC, 2			;enable PC2 as input
 LDI R20,5				;set clock prescaler to 1024
 STS TCCR1B, R20		;send prescaler

LOOP1:
 LDI R18, 0b111100		;loads value into R18
 OUT PORTB, R18			;sends value of R18 into PORTB
 SBIC PINC, 2			;make pin C2 an input
 RJMP NOTPUSHED			;RJMP to NOTPUSHED

 LDI R18, 0b111000		;loads value into R18
 OUT PORTB, R18			;sends value of R18 into PORTB
 LDI R20, 0				;Loads 0 into R20
 STS TCNT1H, R20		;stores the higher bits of value in R20 into TCNT1H
 STS TCNT1L,R20			;stores the lower bits of value of R20 into TCNT1L
 RCALL DELAY1			;Calls the subroutine
 RJMP LOOP1				;RJMP to LOOP1

NOTPUSHED:
 SBI PORTB, 2			;set bit 2 to portB
 RJMP LOOP1				;RJMP LOOP1

DELAY1:
 LDS R29, TCNT1H		;loading upper bit of counter to R29
 LDS R28, TCNT1L		;loading lower bit of counter to R28
 CPI R28,0x4A			;comparing if lower 8 bits of timer is 0x08
 BRSH BODY1				;if lower bits of timer have reached desired amount, check the upper bits
 RJMP DELAY1				;otherwise, keep checking lower bits

BODY1:
 CPI R29,0x4C			;check to see if upper timer bits have reached the desired value
 BRLT DELAY1				;if not, recheck the lower bits
 RET					;once the timer reached the desired value, toggle the LED