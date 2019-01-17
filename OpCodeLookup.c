#include "OpCodeLookup.h"

typedef struct OpTuple {
    const char *name;
    OpCodeType code
} OpTuple;

static const OpTuple lookupTable[] = {
    {"LDA", LDA},
{"LDX", OpCodeType.LDX},
{"LDY", OpCodeType.LDY},
{"STA", OpCodeType.STA},
{"STX", OpCodeType.STX},
{"STY", OpCodeType.STY},
{"ADC", OpCodeType.ADC},
{"SBC", OpCodeType.SBC},
{"INC", OpCodeType.INC},
{"INX", OpCodeType.INX},
{"INY", OpCodeType.INY},
{"DEC", OpCodeType.DEC},
{"DEX", OpCodeType.DEX},
{"DEY", OpCodeType.DEY},
{"AND", OpCodeType.AND},
{"ORA", OpCodeType.ORA},
{"EOR", OpCodeType.EOR},
{"JMP", OpCodeType.JMP},
{"BCC", OpCodeType.BCC},
{"BCS", OpCodeType.BCS},
{"BEQ", OpCodeType.BEQ},
{"BNE", OpCodeType.BNE},
{"BMI", OpCodeType.BMI},
{"BPL", OpCodeType.BPL},
{"BVS", OpCodeType.BVS},
{"BVC", OpCodeType.BVC},
{"CMP", OpCodeType.CMP},
{"CPX", OpCodeType.CPX},
{"CPY", OpCodeType.CPY},
{"BIT", OpCodeType.BIT},
{"ASL", OpCodeType.ASL},
{"LSR", OpCodeType.LSR},
{"ROL", OpCodeType.ROL},
{"ROR", OpCodeType.ROR},
{"TSX", OpCodeType.TSX},
{"TXS", OpCodeType.TXS},
{"PHA", OpCodeType.PHA},
{"PHP", OpCodeType.PHP},
{"PLA", OpCodeType.PLA},
{"PLP", OpCodeType.PLP},
{"JSR", OpCodeType.JSR},
{"RTS", OpCodeType.RTS},
{"RTI", OpCodeType.RTI},
{"CLC", OpCodeType.CLC},
{"CLD", OpCodeType.CLD},
{"CLI", OpCodeType.CLI},
{"CLV", OpCodeType.CLV},
{"SEC", OpCodeType.SEC},
{"SED", OpCodeType.SED},
{"SEI", OpCodeType.SEI},
{"NOP", OpCodeType.NOP},
{"BRK", OpCodeType.BRK}
}

OpCodeType GetOpCode(char *code) {

}