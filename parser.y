%{
    #include "OpCodeLookup.h"

    typedef struct Number {
        char isZeroPage;
        int num;
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

address:
    "#" NUMBER { /* Indirect */ }
    | NUMBER { /* Relative, Abs, or Zero Page */}
    | "(" NUMBER ")" { /* Indirect Abs */ }
    | NUMBER "," INDEXER { /* Absolute/ZP, X/Y index */ }
    | "(" NUMBER "," INDEXER ")" { /* Index Ind */ }
    | "(" NUMBER ")" "," INDEXER { /* Index Ind */ }
    | "A" { /* Accumulator */ };


statement:
    LABEL ":" 