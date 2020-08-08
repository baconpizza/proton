; -----------------------------------------------------------------------------
; Desc:     Executes a procedure in a fixed time period.
; Inputs:   procedure address, timer intervals, timer
; Outputs:
; Notes:
;   TIMED_JSR Subroutine, 20, TIM8T
;   TIMED_JSR Subroutine, 10, TIM64T
; -----------------------------------------------------------------------------
    MAC TIMED_JSR
.PROC   SET {1}
.TIME   SET {2}
.TIMER  SET {3}
        lda #.TIME
        sta .TIMER
        jsr .PROC
.Loop
        lda INTIM
        bne .Loop
    ENDM

; -----------------------------------------------------------------------------
; Desc:    Sleeps until the timer goes to zero.
; Inputs:
; Outputs:
; -----------------------------------------------------------------------------
    MAC TIMER_WAIT
.Loop
        lda INTIM
        bne .Loop
    ENDM

; -----------------------------------------------------------------------------
; Desc:     Sleeps until the timer goes negative.
; Inputs:
; Outputs:
; -----------------------------------------------------------------------------
    MAC TIMER_WAIT_NEGATIVE
.Loop
        lda INTIM
        bpl .Loop
    ENDM

; -----------------------------------------------------------------------------
; Desc:     Sleeps for a specified number of scan lines.
; Inputs:   number of scan lines
; Outputs:
; -----------------------------------------------------------------------------
    MAC SLEEP_LINES
.LINES   SET {1}
        ldy #.LINES
.Loop
        sty WSYNC
        dey
        bne .Loop
    ENDM

; -----------------------------------------------------------------------------
; Desc:     Sleeps for a specified number of cycles using a loop to minimize
;           code size.
; Inputs:
; Outputs:
; -----------------------------------------------------------------------------
    MAC SLEEP_14
        bit $1000                   ; +4 (4)
        bit $1000                   ; +4 (8)
        bit $1000                   ; +4 (12)
        nop                         ; +2 (14)
    ENDM
    MAC SLEEP_17
        ldy #1                      ; +2
.Sleep
        dey                         ; +2
        bpl .Sleep                  ; +3    2 * 5 - 1 = 9 cycles
        nop                         ; +2
        nop                         ; +2
        nop                         ; +2
        ; 17 total cycles = 8 + 9
    ENDM
    MAC SLEEP_32
        ldy #5                      ; +2
.Sleep
        dey                         ; +2
        bpl .Sleep                  ; +3    6 * 5 - 1 = 29 cycles
        bit $0                      ; +3
        ; 32 total cycles = 5 + 29
    ENDM
    MAC SLEEP_34
        ldy #5                      ; +2
.Sleep
        dey                         ; +2
        bpl .Sleep                  ; +3    6 * 5 - 1 = 29 cycles
        bit $0                      ; +3
        nop                         ; +2
        ; 34 total cycles = 5 + 29
    ENDM
    MAC SLEEP_35
        ldy #5                      ; +2
.Sleep
        dey                         ; +2
        bpl .Sleep                  ; +3    6 * 5 - 1 = 29 cycles
        nop                         ; +2
        nop                         ; +2
        nop                         ; +2
        ; 35 total cycles = 6 + 29
    ENDM
    MAC SLEEP_36
        ldy #6                      ; +2
.Sleep
        dey                         ; +2
        bpl .Sleep                  ; +3    7 * 5 - 1 = 34 cycles
        ; 36 total cycles = 2 + 34
    ENDM
    MAC SLEEP_43
        ldy #7                      ; +2
.Sleep
        dey                         ; +2
        bpl .Sleep                  ; +3    8 * 5 - 1 = 39 cycles
        nop                         ; +2
        ; 43 total cycles = 4 + 39
    ENDM
    MAC SLEEP_45
        ldy #7                      ; +2
.Sleep
        dey                         ; +2
        bpl .Sleep                  ; +3    8 * 5 - 1 = 39 cycles
        nop                         ; +2
        nop                         ; +2
        ; 45 total cycles = 6 + 39
    ENDM
    MAC SLEEP_48
        ldy #8                      ; +2
.Sleep
        dey                         ; +2
        bpl .Sleep                  ; +3    9 * 5 - 1 = 44 cycles
        nop                         ; +2
        ; 48 total cycles = 4 + 44
    ENDM
    MAC SLEEP_49
        ldy #8                      ; +2
.Sleep
        dey                         ; +2
        bpl .Sleep                  ; +3    9 * 5 - 1 = 44 cycles 
        bit $0                      ; +3
        ; 49 total cycles = 5 + 44
    ENDM
    MAC SLEEP_51
        ldy #9                      ; +2
.Sleep
        dey                         ; +2
        bpl .Sleep                  ; +3    10 * 5 - 1 = 49 cycles 
        ; 51 total cycles = 2 + 49
    ENDM
    MAC SLEEP_52
        ldy #8                      ; +2
.Sleep
        dey                         ; +2
        bpl .Sleep                  ; +3    9 * 5 - 1 = 44 cycles 
        bit $0                      ; +3
        bit $0                      ; +3
        ; 52 total cycles = 2 + 44 + 6
    ENDM
    MAC SLEEP_54
        ldy #9                      ; +2
.Sleep
        dey                         ; +2
        bpl .Sleep                  ; +3    10 * 5 - 1 = 49 cycles 
        bit $0                      ; +3
        ; 54 total cycles = 2 + 49 + 3
    ENDM
    MAC SLEEP_55
        ldy #9                      ; +2
.Sleep
        dey                         ; +2
        bpl .Sleep                  ; +3    10 * 5 - 1 = 49 cycles 
        nop                         ; +2
        nop                         ; +2
        ; 55 total cycles = 6 + 51
    ENDM
    MAC SLEEP_56
        ldy #10                     ; +2
.Sleep
        dey                         ; +2
        bpl .Sleep                  ; +3    11 * 5 - 1 = 54 cycles 
        ; 56 total cycles = 2 + 54
    ENDM
    MAC SLEEP_61
        ldy #11                     ; +2
.Sleep
        dey                         ; +2
        bpl .Sleep                  ; +3    12 * 5 - 1 = 59 cycles 
        ; 61 total cycles = 2 + 59
    ENDM
