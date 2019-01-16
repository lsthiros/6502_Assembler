lexer: lex.yy.c
	gcc lex.yy.c -ll -o lexer

lex.yy.c: lexer.l
	flex lexer.l