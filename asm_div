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

;temporary registers
.def tmp_reg0 = r16
.def tmp_reg1 = r17
.def tmp_reg2 = r18


;******************************************************************************;
;   CONSTANTS
;******************************************************************************;
.equ INT_TO_DIV = 255


;******************************************************************************;
;    MAIN PROGRAM
;******************************************************************************;
main:
    ;init stack pointer
    ldi tmp_reg0, HIGH(RAMEND)
    out SPH, tmp_reg0
    ldi tmp_reg0, LOW(RAMEND)
    out SPL,  tmp_reg0

    ;load parameter
    ldi tmp_reg0, INT_TO_DIV
    rcall div_by_10

end:
    rjmp end


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
