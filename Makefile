CFLAGS=-g -std=c++17 `llvm-config --cflags --libs --link-shared`
parser.tab.c parser.tab.h: parser.y
	bison -v -d -t -x --debug parser.y
	xsltproc /usr/share/bison/xslt/xml2xhtml.xsl parser.xml >parser.html

lex.yy.c: scanner.l parser.tab.h
	flex scanner.l

scanner: lex.yy.c parser.tab.c parser.tab.h CodeGenVisitor.h PostFixVisitor.h
	g++ ${CFLAGS} parser.tab.c lex.yy.c -lfl -o scanner

clean:
	rm parser.tab.c parser.tab.h parser.output scanner lex.yy.c parser.html parser.xml

.DEFAULT_GOAL := scanner
