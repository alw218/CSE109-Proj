#makefile for trie                                                                                                                                                                  
#Amber Wallace                                   
#CSE 109 

OBJ= prog4.o Lexer.o Token.o
OPTS= -g -c -Wall -Werror

lextest: $(OBJ)
	g++ -o lextest $(OBJ)

prog4.o: prog4.cc Lexer.h Token.h
	g++ $(OPTS) prog4.cc

Lexer.o: Lexer.cc Lexer.h Token.h
	g++ $(OPTS) Lexer.cc

Token.o: Token.h Token.cc
	g++ $(OPTS) Token.cc

clean:
	rm -f *.o *~
