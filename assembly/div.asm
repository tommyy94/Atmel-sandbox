;******************************************************************************;
;   HEADER FILES
;******************************************************************************;
.nolist
.include "m328pdef.inc"
.list


.CSEG
.ORG $0000


;******************************************************************************;
;   REGISTER DEFINITIONS
;******************************************************************************;
;math registers
.def mul_reg0 = r0
.def mul_reg1 = r1

;div16u registers
.def drem16uL = r14
.def drem16uH = r15
.def dd16uL	= r16
.def dd16uH	= r17
.def dv16uL	= r18
.def dv16uH	= r19
.def dcnt16u = r20

;temporary registers
.def tmp_reg0 = r21
.def tmp_reg1 = r22


;******************************************************************************;
;   CONSTANTS
;******************************************************************************;


;******************************************************************************;
;    MAIN PROGRAM
;******************************************************************************;
main:
    ;init stack pointer
    ldi YH, HIGH(RAMEND)
    ldi YL, LOW(RAMEND)
    out SPH, YH
    out SPL, YL

    ;divisor
    ldi dv16uH, $04
    ldi dv16uL, $00 ;1024

    ;dividend
    ldi dd16uH, $05
    ldi dd16uL, $F0 ;1520

    rcall div16u

    ldi tmp_reg0, 255
    rcall div_by_10

end:
    rjmp end

    
;******************************************************************************;
; SUBROUTINE: div16u
; Description: Divides the two 16-bit unsigned numbers "dd8uH:dd8uL" (dividend),
; "dv16uH:dv16uL" (divisor). 
; Result: "dres16uH:dres16uL"
; Remainder: "drem16uH:drem16uL"
; High registers: 5 (dres16uL/dd16uL, dres16uH/dd16uH, dv16uL, dv16uH, dcnt16u)
; Low registers: 2 (drem16uL, drem16uH)
;******************************************************************************;
div16u:
	clr	drem16uL ;clear remainder low byte
	sub	drem16uH, drem16uH ;clear remainder high byte and carry
	ldi	dcnt16u, 17 ;init loop counter

div16u_1:
    ;shift left dividend
	rol	dd16uL
	rol	dd16uH
	dec	dcnt16u ;counter--
    ;return if done
	brne div16u_2
	ret

div16u_2:
    ;shift dividend into remainder
	rol	drem16uL
	rol	drem16uH
	sub	drem16uL, dv16uL ;remainder -= divisor
	sbc	drem16uH, dv16uH
    ;restore remainder if result negative
	brcc div16u_3
	add	drem16uL, dv16uL
	adc	drem16uH, dv16uH
	clc ;clear carry to be shifted into result
	rjmp div16u_1 ;else

div16u_3:
	sec ;set carry to be shifted into result
	rjmp div16u_1

    
;******************************************************************************;
; SUBROUTINE: div_by_10
; Registers used: tmp_reg0, tmp_reg1, mul_reg0, mul_reg1
; Description: Divides given value by 10 and places it in higher byte(mul_reg1.)
; The lower byte (mul_reg0) is ignored. Value must be inserted to tmp_reg0 as a
; parameter in the main program.
;******************************************************************************
div_by_10:
; Smallest dividable value of 255 is 5: 255 / 5 = 51
    ldi tmp_reg1, 51
    mul tmp_reg0, tmp_reg1
    inc mul_reg1
    lsr mul_reg1 ;mul_reg1 = (tmp_reg1 / 5) / 2 = tmp_reg1 / 10
    ret


.exit
