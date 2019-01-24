# Mothafuggin colahs
COLOR_NONE="$$(tput sgr0)"
COLOR_GREEN="$$(tput setaf 2)"
COLOR_YELLOW="$$(tput setaf 3)"
COLOR_RED="$$(tput setaf 1)"

# Compiler variables
CC = gcc
CC_FLAGS = -g

# Project variables
EXECUTABLE_NAME = assembler
SOURCES = main.c OpCodeDefs.c ParseTree.c Parser.c Lexer.c ParserPrimitives.c
LEXER_DEF = Lexer.l
PARSER_DEF = Parser.y
EXT_LIB =

# Generated variables (Don't change these)
LIBFLAGS = $(addprefix -l, $(EXT_LIB))
OBJECTS = $(SOURCES:.c=.o)
OBJECT_LEXER = $(LEXER_DEF:.o=.c)
OBJECT_PARSER= $(PARSER_DEF:.o=.c)
GENERATED_LEXER = $(LEXER_DEF:.l=.c)
GENERATED_PARSER = $(PARSER_DEF:.y=.c)
GENERATED_PARSER_HEADER = $(PARSER_DEF:.y=.h)
GENERATED_LEXER_HEADER = $(LEXER_DEF:.l=.h)

all : $(EXECUTABLE_NAME)

$(EXECUTABLE_NAME) : $(OBJECTS)
	@echo "$(COLOR_RED)Linking $@$(COLOR_NONE)"
	@$(CC) $(CC_FLAGS) $(OBJECTS) $(LIBFLAGS) -o $(EXECUTABLE_NAME)

$(GENERATED_PARSER) : $(PARSER_DEF)
	@echo "$(COLOR_YELLOW)Generating Parser$(COLOR_NONE)"
	@bison -d -o $(GENERATED_PARSER) $(PARSER_DEF)

$(GENERATED_LEXER) : $(LEXER_DEF) $(GENERATED_PARSER)
	@echo "$(COLOR_YELLOW)Generating Lexer$(COLOR_NONE)"
	@flex --header-file=$(LEXER_DEF:.l=.h) -o $(GENERATED_LEXER) $(LEXER_DEF) 

%.o : %.c $(GENERATED_PARSER) $(GENERATED_LEXER)
	@echo "$(COLOR_GREEN)Compiling $<$(COLOR_NONE)"
	@$(CC) $(CC_FLAGS) -c $< -o $@

clean:
	rm -f $(OBJECTS) $(EXECUTABLE_NAME) $(GENERATED_PARSER) $(GENERATED_PARSER_HEADER) $(GENERATED_LEXER) $(GENERATED_LEXER_HEADER)