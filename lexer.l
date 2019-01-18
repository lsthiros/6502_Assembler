%{
    #include <stdio.h>
%}

%option header-file="lexer.h"
/* %option bison-bridge */

LDA (?i:LDA)
LDX (?i:LDX)
LDY (?i:LDY)
STA (?i:STA)
STX (?i:STX)
STY (?i:STY)
ADC (?i:ADC)
SBC (?i:SBC)
INC (?i:INC)
INX (?i:INX)
INY (?i:INY)
DEC (?i:DEC)
DEX (?i:DEX)
DEY (?i:DEY)
AND (?i:AND)
ORA (?i:ORA)
EOR (?i:EOR)
JMP (?i:JMP)
BCC (?i:BCC)
BCS (?i:BCS)
BEQ (?i:BEQ)
BNE (?i:BNE)
BMI (?i:BMI)
BPL (?i:BPL)
BVS (?i:BVS)
BVC (?i:BVC)
CMP (?i:CMP)
CPX (?i:CPX)
CPY (?i:CPY)
BIT (?i:BIT)
ASL (?i:ASL)
LSR (?i:LSR)
ROL (?i:ROL)
ROR (?i:ROR)
TSX (?i:TSX)
TXS (?i:TXS)
PHA (?i:PHA)
PHP (?i:PHP)
PLA (?i:PLA)
PLP (?i:PLP)
JSR (?i:JSR)
RTS (?i:RTS)
RTI (?i:RTI)
CLC (?i:CLC)
CLD (?i:CLD)
CLI (?i:CLI)
CLV (?i:CLV)
SEC (?i:SEC)
SED (?i:SED)
SEI (?i:SEI)
NOP (?i:NOP)
BRK (?i:BRK)

LABEL [a-zA-Z_][a-zA-Z0-9_]*
SMALL_VAL "$"[a-fA-F0-9]{2}


%%

(?i:[xy]) {
    printf("Found indexer: %s\n", yytext);
}

(?i:a) {
    printf("Found accumulator token: %s\n", yytext);
}

\$[a-fA-F0-9]{4} { printf("Regular address: %s\n", yytext ); }

\$[a-fA-F0-9]{2} { printf("Zero page address: %s\n", yytext ); }

{LDA} |
{LDX} |
{LDY} |
{STA} |
{STX} |
{STY} |
{ADC} |
{SBC} |
{INC} |
{INX} |
{INY} |
{DEC} |
{DEX} |
{DEY} |
{AND} |
{ORA} |
{EOR} |
{JMP} |
{BCC} |
{BCS} |
{BEQ} |
{BNE} |
{BMI} |
{BPL} |
{BVS} |
{BVC} |
{CMP} |
{CPX} |
{CPY} |
{BIT} |
{ASL} |
{LSR} |
{ROL} |
{ROR} |
{TSX} |
{TXS} |
{PHA} |
{PHP} |
{PLA} |
{PLP} |
{JSR} |
{RTS} |
{RTI} |
{CLC} |
{CLD} |
{CLI} |
{CLV} |
{SEC} |
{SED} |
{SEI} |
{NOP} |
{BRK} {
    printf( "OwO an opcode? %s\n", yytext );
}

{LABEL} {
    printf("Label: %s\n", yytext);
}


","|":"|"#"|"("|")" {
    printf("Found a gramar token: %s\n", yytext);
}

[ \t\n]+ { /* Eat whitespace */ }

. {
    printf( "Unrecognized character: %s\n", yytext );
}

%%
int main( int argc, char **argv )
    {
    ++argv, --argc;  /* skip over program name */
    if ( argc > 0 )
            yyin = fopen( argv[0], "r" );
    else
            yyin = stdin;

    yylex();
    return 0;
    }
