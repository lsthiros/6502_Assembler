%{
    #include "OpCodeLookup.h"
    #include "ParserDefs.h"

    typedef struct Number {
        char isZeroPage;
        uint16_t num;
    } Number;

    typedef struct LiteralAddress {
        uint8_t isZp;
        uint16_t literal;
    } LiteralAddress;

    typedef struct AddressLocation {
        uint8_t isLabel;
        union {
            char *label;
            LiteralAddress *literal;
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
    LiteralAddress *addrLit;
    AddressLocation *addrLoc;
    AddressCode *addrCode;
    Operation *operation;
}

%token <str> LABEL
%token <str> LABEL_DEC
%token <str> INDEXER
%token <op>  OPCODE
%token <addrLit> NUMBER

%type <addrLoc> address
%type <addrCode> addressCode
%type <operation> operation
%%

statements:
    | statements statement;

statement:
    LABEL_DEC { /* Marked location */ }
    | operation { /* Terminating op */ };

operation:
    OPCODE addressCode { /* addressed opcode */ 
        $$ = malloc(sizeof(Operation));
        $$->type = $1;
        $$->code = $2;
    };

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
    | address "," INDEXER { /* Absolute/ZP, X/Y index */
        $$ = malloc(sizeof(AddressCode));
        if (strcmp($3, "X") == 0) {
            $$->mode = ABS_X;
        } else {
            $$->mode = ABS_Y;
        }
        $$->location = $1;
    }
    | "(" address "," INDEXER ")" { /* Index Ind */ 
        $$ = malloc(sizeof(AddressCode));
        $$->mode = INDEX_IND;
        $$->location = $2;
    }
    | "(" address ")" "," INDEXER { /* Ind Index */
        $$ = malloc(sizeof(AddressCode));
        $$->mode = IND_INDEX;
        $$->location = $2;
    }
    | "A" { /* Accumulator */
        $$ = malloc(sizeof(AddressCode));
        $$->mode = ACCUMULATOR;
        $$->location = NULL;
    }
    | { /* No address. Implied mode */
        $$ = NULL;
    };
