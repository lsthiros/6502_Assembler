#if !defined(OP_CODE_LOOKUP)
#define OP_CODE_LOOKUP

typedef enum OpCodeType {
    LDA = 0,
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
    ABS_X = 0,
    ABS_Y,
    ABSOLUTE,
    ACCUMULATOR,
    IMMEDIATE,
    IMPLIED,
    INDEX_IND,
    IND_INDEX,
    INDIRECT_ABS,
    REL_ZP,
    ZP_X,
    ZP_Y
} AddressMode;

unsigned int opCodeLength(AddressMode mode);
const char *opName(OpCodeType type);
const char *opAddressModeName(AddressMode mode);

#endif // OP_CODE_LOOKUP
