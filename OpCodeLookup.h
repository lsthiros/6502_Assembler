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

typedef enum AddressMode {
    INDIRECT, REL_ABS_ZP, INDIRECT_ABS, ABS_X, ABS_Y, ZP_X, ZP_Y, INDEX_IND,
    IND_INDEX, ACC, IMMEDIATE}
} AddressMode;

#endif // OP_CODE_LOOKUP
