Section .data
        answer: word
        alpha:  word
        gamma:  word
        C3P0:   word
        R2D2:   word
Section .code
        LVALUE  answer
        RVALUE  alpha
        PUSH    2
        RVALUE  gamma
        MPY
        RVALUE  C3P0
        RVALUE  R2D2
        SUB
        DIV
        ADD
        STO
        HALT
