all: ParseTree.o Lexer.yy.o Parser.o

ParseTree.o: ParseTree.c
	gcc ParseTree.c -c -o ParseTree.o

Lexer.yy.o: Parser.c Lexer.yy.c
	gcc Lexer.yy.c -c -o Lexer.yy.o

Lexer.yy.c: Lexer.l
	flex -o Lexer.yy.c Lexer.l

Parser.o: Parser.c Lexer.yy.c
	gcc Parser.c -c -o Parser.o

Parser.c: Parser.y
	bison -o Parser.c -d Parser.y
