#if !defined(OP_CODE_LOOKUP)
#define OP_CODE_LOOKUP

typedef enum OpCodeType {
    LDA,
    LDX,
    LDY,
    STA,
    STX,
    STY,
    ADC,
    SBC,
    INC,
    INX,
    INY,
    DEC,
    DEX,
    DEY,
    AND,
    ORA,
    EOR,
    JMP,
    BCC,
    BCS,
    BEQ,
    BNE,
    BMI,
    BPL,
    BVS,
    BVC,
    CMP,
    CPX,
    CPY,
    BIT,
    ASL,
    LSR,
    ROL,
    ROR,
    TSX,
    TXS,
    PHA,
    PHP,
    PLA,
    PLP,
    JSR,
    RTS,
    RTI,
    CLC,
    CLD,
    CLI,
    CLV,
    SEC,
    SED,
    SEI,
    NOP,
    BRK
} OpCodeType;

#endif // OP_CODE_LOOKUP