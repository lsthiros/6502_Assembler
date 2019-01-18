%{
    #include "OpCodeLookup.h"

    typedef struct Number {
        char isZeroPage;
        uint16_t num;
    } Number;

    typedef struct AddressLocation {
        uint8_t isLabel;
        union {
            uint16_t literal;
            char *label;
        } val;
    } AddressLocation;

    typedef struct AddressCode {
        AddressMode mode;
        AddressLocation *location;
    } AddressCode;

    typedef struct Operation {
        OpCodeType type;
        AddressCode *code;
    } Operation;
%}

%union {
    OpCodeType op;
    char *str;
    Number num;
    AddressLocation *addrLoc;
    AddressCode *addrCode;
}

%token <str> LABEL
%token <str> INDEXER
%token <op>  OPCODE
%token <num> NUMBER

%type <addrLoc> address
%type <addrCode> addressCode
%%

statements:
    | statements statement;

statement:
    LABEL ":" { /* Marked location */ }
    | operation { /* Terminating op */ };

operation:
    OPCODE addressCode { /* addressed opcode */ }
    | OPCODE { /* immediate opcode */ };

address:
    NUMBER {
        $$ = malloc(sizeof(AddressLocation));
        $$->isLabel = 0;
        $$->val.literal = $1;
    }
    | LABEL {
        $$ = malloc(sizeof(AddressLocation));
        $$->isLabel = 1;
        $$->val.label = $1;
    };

addressCode:
    "#" address {
        $$ = malloc(sizeof(AddressCode));
        $$->mode = IMMEDIATE;
        $$->location = $2;
    }
    | address { /* Relative, Absolute, or Zero Page */
        $$ = malloc(sizeof(AddressCode));
        $$->mode = REL_ABS_ZP;
        $$->location = $1;
    }
    | "(" address ")" { /* Indirect Abs */
        $$ = malloc(sizeof(AddressCode));
        $$->mode = IND_ABS;
        $$->location = $2;
    }
    | address "," INDEXER { /* Absolute/ZP, X/Y index */ }
    | "(" address "," INDEXER ")" { /* Index Ind */ }
    | "(" address ")" "," INDEXER { /* Ind Index */ }
    | "A" { /* Accumulator */ };
