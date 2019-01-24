#include "Parser.h"
#include "Lexer.h"

#include "ParseTree.h"

#include <stdlib.h>
#include <stdio.h>

int yyerror(yyscan_t scanner, const char *msg) {
  return 0;
}

int main(int argc, char const *argv[])
{
    ParseContext context;
    yyscan_t scanner;
    YY_BUFFER_STATE buf;
    FILE *source;

    initContext(&context);

    if (yylex_init(&scanner)) {
        fprintf(stderr, "Could not init scanner\n");
        exit(1);
    }

    if (argc > 1) {
        source = fopen(argv[1], "r");

        if (!source) {
            perror("Cound not open requested file");
            exit(1);
        }

        buf = yy_create_buffer(source, YY_BUF_SIZE, scanner);
        yy_switch_to_buffer(buf, scanner);
    }
    if (yyparse(scanner, &context)) {
        fprintf(stderr, "Parsing error\n");
        exit(1);
    }

    yy_delete_buffer(buf, scanner);
    yylex_destroy(scanner);
    return 0;
}
