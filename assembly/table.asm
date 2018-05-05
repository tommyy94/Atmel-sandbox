.cseg
.org $0000

.equ TABLE_SIZE = 14


reset:
    ;init stack pointer
    ldi r16, high(RAMEND)
    out SPH, r16
    ldi r16, low(RAMEND)
    out SPL, r16
    
    ;load address to Z register
    ldi ZH, high(2*data) ;program memory is stored in 16-bit words, so
    ldi ZL, low(2*data)  ;multiply by 2 to extract bytes

    ldi r17, TABLE_SIZE ;load counter
    
load:
    lpm r16, Z+ ;read byte and inc pointer
    dec r17
    brne load ;if r17 != 0, goto load

end:
    rjmp end


data: .db "Generic text", "XD"
