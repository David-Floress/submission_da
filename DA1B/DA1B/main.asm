;
; DA1B.asm
;
; Created: 2/23/2019 1:27:54 PM
; Author : David Flores
;


; Replace with your application code
.equ startadds = 0x200		;gives startadds address of 0x200
.equ div = 0x400			;gives div address of 0x400
.equ not_div = 0x600		;gives not_div address of 0x600

ldi XL, low(startadds)		;loads the lower bits of startadds to XL
ldi XH, high(startadds)		;loads the highter bits of startadds to XH
ldi YL, low(div)			;loads the lower bits of div to YL
ldi YH, high(div)			;loads the highter bits of div to YH
ldi ZL, low(not_div)		;loads the lower bits of not_div to ZL
ldi ZH, high(not_div)		;loads the highter bits of not_div to ZH 
ldi R21, 11					;loads R21 with 11
ldi R22, 3					;loads R22 with 3
ldi R23, 99					;decrement timer to reach 99 numbers

adding:
mov R20, XL					;value XL into R20
add R20, XH					;adds value of XH into R20

greater_than_10:
cp R20, R21					;compares 11 with value in R20
brsh X_reg					;branch if same or higher to X_reg
inc R20						;increments R20
rjmp greater_than_10		;rjmp to greater_than_10

X_reg:
st X+, R20					;stores value of R20 into the address X is pointing at then increments X to next address
rjmp div_by_3				; Checks to see if divisible by 3

increment:
dec R23						;decrements R23
breq finish					;branch if equal to finish
inc R20						;add 1 to value in R20
mov R24, R20				;dummy register -- R24 copies R20
rjmp X_reg					;rjmp to X_reg

div_by_3:

sub R24, R22				;subtracts 3 from value in R24 and stores in R24
breq Y_reg					;brach if R24 and R22 are equal
brlo Z_reg					;branch if lower to Z_reg
rjmp div_by_3				;jump to div_by_3


Y_reg:
st Y+, R20					;stores value of R20 into the address Y is pointing at then increments Y to next address
add R16, R20				;adds value in R20 with value in R16 and stores in R16
adc R17, R0					;add carry incase of overflow
rjmp increment				;rjmp to increment

Z_reg:
st Z+, R20					;stores value of R20 into the address Z is pointing at then increments Z to next address
add R18, R20				;adds value in R20 to R18
adc R19, R0					;add carry incase of overflow
rjmp increment				;rjmp to increment

finish: rjmp finish			;debug mode