parser.tab.c parser.tab.h: parser.y
	bison -v -d parser.y

lex.yy.c: scanner.l parser.tab.h
	flex scanner.l

scanner: lex.yy.c parser.tab.c parser.tab.h
	g++ parser.tab.c lex.yy.c -lfl -o scanner

clean:
	rm parser.tab.c parser.tab.h parser.output a.out scanner lex.yy.c

.DEFAULT_GOAL := scanner