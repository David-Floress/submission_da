;
; DA1A_MUL.asm
;
; Created: 2/16/2019 10:17:17 PM
; Author : David Flores


; Replace with your application code
.EQU multiplier = 0xFF      ;assign value to mulitplier
.EQU multiplicand = 0xFFFF  ;assign value to multiplicand

ldi r24, low(multiplicand)  ;load low bits of multiplicand to r24
ldi r25, high(multiplicand) ;load high bits of multiplicand to r25
ldi r22, multiplier         ;load multiplier bits in r22
ldi r21, 0                  ;load value 0 to r21
ldi r17, multiplier			;multiplier 2

loop:
add r18, r24                ;move value in r24 to r18
adc r19, r25				;add value in r25 into r19 and carry from r18 if necessary
adc r20, r21				;add value in r21 into r20 and carry from r19 if necessary
dec r22						;decrement r22
brne loop					;branch if not equal to 0

mul r24, r17				;multiplies value in r17 with value in r24 and stores in r0 and r1
add r26, r0					;move value in r0 to r26
add r27, r1					;move value in r1 to r27
mul r25, r17				;multiplies value in r17 with value in r28 and stores in r0 and r1
add r28, r1					;move value in r1 to r28
add r27, r0					;move value in r0 to r27


end: jmp end

