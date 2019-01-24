#include "OpCodeLookup.h"
#include "ParserDefs.h"

const unsigned int length[] = {
    3, /* ABS_X */
    3, /* ABS_Y */
    3, /* ABSOLUTE */
    1, /* ACCUMULATOR */
    2, /* IMMEDIATE */
    1, /* IMPLIED */
    2, /* INDEX_IND */
    2, /* IND_INDEX */
    3, /* INDIRECT_ABS */
    2, /* REL_ZP */
    2, /* ZP_X */
    2, /* ZP_Y */
}

const char *opNames{
    "LDA",
    "LDX",
    "LDY",
    "STA",
    "STX",
    "STY",
    "ADC",
    "SBC",
    "INC",
    "INX",
    "INY",
    "DEC",
    "DEX",
    "DEY",
    "AND",
    "ORA",
    "EOR",
    "JMP",
    "BCC",
    "BCS",
    "BEQ",
    "BNE",
    "BMI",
    "BPL",
    "BVS",
    "BVC",
    "CMP",
    "CPX",
    "CPY",
    "BIT",
    "ASL",
    "LSR",
    "ROL",
    "ROR",
    "TSX",
    "TXS",
    "PHA",
    "PHP",
    "PLA",
    "PLP",
    "JSR",
    "RTS",
    "RTI",
    "CLC",
    "CLD",
    "CLI",
    "CLV",
    "SEC",
    "SED",
    "SEI",
    "NOP",
    "BRK"
};
const char *modeName[] = {
    "ABS_X",
    "ABS_Y",
    "ABSOLUTE",
    "ACCUMULATOR",
    "IMMEDIATE",
    "IMPLIED",
    "INDEX_IND",
    "IND_INDEX",
    "INDIRECT_ABS",
    "REL_ZP",
    "ZP_X",
    "ZP_Y"
};

unsigned int opCodeLength(AddressMode mode) {
    return length[mode];
}

void printOp(Operation *operation) {
    printf("Name: %s\n", opNames[operation->type]);
    if (operation->code) {
        printf("Mode: %s\n", opNames[operation->code->mode]);
    }
}
