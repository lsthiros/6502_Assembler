%{
    #include "OpCodeDefs.h"
    #include "ParserPrimitives.h"

    #include "Parser.h"
    #include "Lexer.h"

    #include <stdint.h>
    #include <stdlib.h>
    #include <string.h>

    void printOp(Operation *operation) {
        printf("Name: %s\n", opName(operation->type));
        if (operation->code) {
            printf("Mode: %s\n", opAddressModeName(operation->code->mode));
        }
    }

    void initContext(ParseContext *context) {
        context->position = 0;
        context->list = initOpList();
    }
%}

%define api.pure full
%lex-param   { yyscan_t scanner }
%parse-param { yyscan_t scanner }
%parse-param { ParseContext *context }

%code requires {
    #include "ParseTree.h"

    #ifndef YY_TYPEDEF_YY_SCANNER_T
    #define YY_TYPEDEF_YY_SCANNER_T
    typedef void* yyscan_t;
    #endif
    int yylex();
    int yyerror();


    typedef struct ParseContext {
        OpList *list;
        unsigned int position;
    } ParseContext;

    void printOp(Operation *operation);
    void initContext(ParseContext *context);
}


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
    LABEL_DEC {
        printf("Lexer: Marking label location\n");
        insertLabel(context->list, $1, context->position);
    }
    | operation {
        $1->position = context->position;
        context->position += opCodeLength($1->code->mode);
        printOp($1);
    };

operation:
    OPCODE addressCode { /* addressed opcode */ 
        $$ = malloc(sizeof(Operation));
        $$->type = $1;
        $$->code = $2;
    };

address:
    NUMBER {
        printf("Lexer: Constructing an address\n");
        $$ = malloc(sizeof(AddressLocation));
        $$->isLabel = 0;
        $$->val.literal = $1;
    }
    | LABEL {
        printf("Lexer: Constructing an label\n");
        $$ = malloc(sizeof(AddressLocation));
        $$->isLabel = 1;
        $$->val.label = $1;
    };

addressCode:
    '#' address {
        $$ = malloc(sizeof(AddressCode));
        $$->mode = IMMEDIATE;
        $$->location = $2;
    }
    | address { /* Relative, Absolute, or Zero Page */
        $$ = malloc(sizeof(AddressCode));
        $$->mode = (!($1->isLabel) && !($1->val.literal->isZp)) ? ABSOLUTE : REL_ZP;
        $$->location = $1;
    }
    | '(' address ')' { /* Indirect Abs */
        printf("Lexer: Constructing an Ind Abs code\n");
        $$ = malloc(sizeof(AddressCode));
        $$->mode = INDIRECT_ABS;
        $$->location = $2;
    }
    | address ',' INDEXER { /* Absolute/ZP, X/Y index */
        $$ = malloc(sizeof(AddressCode));
        if (strcmp($3, "X") == 0) {
            $$->mode = ABS_X;
        } else {
            $$->mode = ABS_Y;
        }
        $$->location = $1;
    }
    | '(' address ',' INDEXER ')' { /* Index Ind */ 
        $$ = malloc(sizeof(AddressCode));
        $$->mode = INDEX_IND;
        $$->location = $2;
    }
    | '(' address ')' ',' INDEXER { /* Ind Index */
        $$ = malloc(sizeof(AddressCode));
        $$->mode = IND_INDEX;
        $$->location = $2;
    }
    | 'A' { /* Accumulator */
        $$ = malloc(sizeof(AddressCode));
        $$->mode = ACCUMULATOR;
        $$->location = NULL;
    }
    | { /* No address. Implied mode */
        $$ = malloc(sizeof(AddressCode));
        $$->mode = IMPLIED;
        $$->location = NULL;
    };
