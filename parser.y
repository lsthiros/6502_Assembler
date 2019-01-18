%{
    #include "OpCodeLookup.h"

    typedef struct Number {
        char isZeroPage;
        uint16_t num;
    } Number;

%}

%union {
    OpCodeType op;
    char *str;
    Number num;
}

%token <str> LABEL
%token <str> INDEXER
%token <op>  OPCODE
%token <num> NUMBER
%%

statements:
    | statements statement;

statement:
    LABEL ":" statement { /* Marked location */ }
    | operation { /* Terminating op */ };

operation:
    OPCODE address { /* addressed opcode */ }
    | OPCODE { /* immediate opcode */ }

address:
    NUMBER
    | LABEL;

addressCode:
    "#" address { /* Indirect */ }
    | address { /* Relative, Abs, or Zero Page */}
    | "(" address ")" { /* Indirect Abs */ }
    | address "," INDEXER { /* Absolute/ZP, X/Y index */ }
    | "(" address "," INDEXER ")" { /* Index Ind */ }
    | "(" address ")" "," INDEXER { /* Index Ind */ }
    | "A" { /* Accumulator */ };
