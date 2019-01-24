assembler: ParseTree.o Lexer.yy.o Parser.o OpCodeDefs.o main.o
	gcc ParseTree.o Lexer.yy.o Parser.o OpCodeDefs.o main.o -o assembler

main.o: main.c
	gcc main.c -c -o main.o

OpCodeDefs.o: OpCodeDefs.c
	gcc OpCodeDefs.c -c -o OpCodeDefs.o

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

clean:
	rm -f Parser.c Parser.h Lexer.yy.c Lexer.yy.h ParseTree.o Lexer.yy.o Parser.o OpCodeDefs.o main.o