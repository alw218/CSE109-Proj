#makefile for prog5                                                                                                                                      
#Amber Wallace                                   
#CSE 109 

OBJ= silc.o Lexer.o Token.o parser.o
OPTS= -g -c -Wall -Werror

silc: $(OBJ)
	g++ -o silc $(OBJ)

silc.o: silc.cc Lexer.h Token.h parser.h
	g++ $(OPTS) silc.cc

parser.o: parser.cc parser.h Lexer.h Token.h
	g++ $(OPTS) parser.cc

Lexer.o: Lexer.cc Lexer.h Token.h
	g++ $(OPTS) Lexer.cc

Token.o: Token.h Token.cc
	g++ $(OPTS) Token.cc

clean:
	rm -f *.o *~
