%{
    #include "OpCodeLookup.h"
    #include <stdio.h>

    #define LITERAL(IS_ZP) \
    yylval.addrLit = malloc(sizeof(LiteralAddress)); \
    yylval.addrLit->isZp = IS_ZP; \
    yylval.addrLit->literal = strtol(yytext + 1, NULL, 16);
    
%}

%option header-file="Lexer.h"
%option bison-bridge

%%

[XY] {
    printf("Found indexer: %s\n", yytext);
    return yytext[0];
}

[A] {
    printf("Found accumulator token: %s\n", yytext);
    return yytext[0];
}

\$[a-fA-F0-9]{4} {
    LITERAL(0);
}

\$[a-fA-F0-9]{2} {
    LITERAL(1);
}

(?i:LDA) { yylval.op = LDA; return OPCODE;}
(?i:LDX) { yylval.op = LDX; return OPCODE;}
(?i:LDY) { yylval.op = LDY; return OPCODE;}
(?i:STA) { yylval.op = STA; return OPCODE;}
(?i:STX) { yylval.op = STX; return OPCODE;}
(?i:STY) { yylval.op = STY; return OPCODE;}
(?i:ADC) { yylval.op = ADC; return OPCODE;}
(?i:SBC) { yylval.op = SBC; return OPCODE;}
(?i:INC) { yylval.op = INC; return OPCODE;}
(?i:INX) { yylval.op = INX; return OPCODE;}
(?i:INY) { yylval.op = INY; return OPCODE;}
(?i:DEC) { yylval.op = DEC; return OPCODE;}
(?i:DEX) { yylval.op = DEX; return OPCODE;}
(?i:DEY) { yylval.op = DEY; return OPCODE;}
(?i:AND) { yylval.op = AND; return OPCODE;}
(?i:ORA) { yylval.op = ORA; return OPCODE;}
(?i:EOR) { yylval.op = EOR; return OPCODE;}
(?i:JMP) { yylval.op = JMP; return OPCODE;}
(?i:BCC) { yylval.op = BCC; return OPCODE;}
(?i:BCS) { yylval.op = BCS; return OPCODE;}
(?i:BEQ) { yylval.op = BEQ; return OPCODE;}
(?i:BNE) { yylval.op = BNE; return OPCODE;}
(?i:BMI) { yylval.op = BMI; return OPCODE;}
(?i:BPL) { yylval.op = BPL; return OPCODE;}
(?i:BVS) { yylval.op = BVS; return OPCODE;}
(?i:BVC) { yylval.op = BVC; return OPCODE;}
(?i:CMP) { yylval.op = CMP; return OPCODE;}
(?i:CPX) { yylval.op = CPX; return OPCODE;}
(?i:CPY) { yylval.op = CPY; return OPCODE;}
(?i:BIT) { yylval.op = BIT; return OPCODE;}
(?i:ASL) { yylval.op = ASL; return OPCODE;}
(?i:LSR) { yylval.op = LSR; return OPCODE;}
(?i:ROL) { yylval.op = ROL; return OPCODE;}
(?i:ROR) { yylval.op = ROR; return OPCODE;}
(?i:TSX) { yylval.op = TSX; return OPCODE;}
(?i:TXS) { yylval.op = TXS; return OPCODE;}
(?i:PHA) { yylval.op = PHA; return OPCODE;}
(?i:PHP) { yylval.op = PHP; return OPCODE;}
(?i:PLA) { yylval.op = PLA; return OPCODE;}
(?i:PLP) { yylval.op = PLP; return OPCODE;}
(?i:JSR) { yylval.op = JSR; return OPCODE;}
(?i:RTS) { yylval.op = RTS; return OPCODE;}
(?i:RTI) { yylval.op = RTI; return OPCODE;}
(?i:CLC) { yylval.op = CLC; return OPCODE;}
(?i:CLD) { yylval.op = CLD; return OPCODE;}
(?i:CLI) { yylval.op = CLI; return OPCODE;}
(?i:CLV) { yylval.op = CLV; return OPCODE;}
(?i:SEC) { yylval.op = SEC; return OPCODE;}
(?i:SED) { yylval.op = SED; return OPCODE;}
(?i:SEI) { yylval.op = SEI; return OPCODE;}
(?i:NOP) { yylval.op = NOP; return OPCODE;}
(?i:BRK) { yylval.op = BRK; return OPCODE;}

","|"#"|"("|")" {
    printf("Found a gramar token: %s\n", yytext);
    return yytext[0];
}

[a-zA-Z_][a-zA-Z0-9_]*[:] {
    yylval.str = strndup(yytext, strlen(yytext) - 1);
    return LABEL_DEC;
}

[a-zA-Z_][a-zA-Z0-9_]* {
    yylval.str = strdup(yytext);
    return LABEL;
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
