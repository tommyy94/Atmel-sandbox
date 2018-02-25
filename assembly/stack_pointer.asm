.nolist
.include "m328pdef.inc"
.list

.cseg
.org $0000

rjmp reset


;******************************************************************************;
; INITIALIZE
;******************************************************************************;
reset:
    ;init stack pointer
    ldi YH, high(RAMEND)
    ldi YL, low(RAMEND)
    out SPH, YH
    out SPL, YL

    ;load some random values
	ldi r20, $03
	ldi r21, $02
	ldi r22, $01

    ;push them on stack
    push r20
    push r21
    push r22

	rcall calc_sum
    
    ;only result needed, stored in r16
    pop r0  ;Y+3
    pop r0  ;Y+4
    pop r16 ;Y+5

end:
    rjmp end

    
;******************************************************************************;
; SUBROUTINE: calc_sum
;******************************************************************************;
calc_sum:
    ;store stack pointer
    in YH, SPH
    in YL, SPL

    ;load parameters from the stack
    ldd r16, Y+5 ;$03
    ldd r17, Y+4 ;$02
    ldd r18, Y+3 ;$01

    ;calculations
    add r18, r16
    add r18, r17

    ;store result on stack
	std Y+5, r18

    ;restore stack pointer
    out SPH, YH
    out SPL, YL
	ret


.exit
