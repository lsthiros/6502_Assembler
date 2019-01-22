all: ParseTree.o Lexer.yy.o

ParseTree.o: ParseTree.c
	gcc ParseTree.c -c -o ParseTree.o

Lexer.yy.o: Lexer.yy.c
	gcc Lexer.yy.c -c -o Lexer.yy.o

Lexer.yy.c: lexer.l
	flex -o Lexer.yy.c lexer.l