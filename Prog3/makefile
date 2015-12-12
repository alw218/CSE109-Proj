#makefile for trie
#Amber Wallace
#CSE 109
OBJ= prog3.o Trie.o Link.o Node.o
OPTS= -g -c -Wall -Werror

testtrie: $(OBJ)
	g++ -o testtrie $(OBJ)

prog3.o: prog3.cc Trie.h Link.h Node.h
	g++ $(OPTS) prog3.cc

Trie.o: Trie.cc Trie.h Link.h Node.h
	g++ $(OPTS) Trie.cc

Link.o: Link.h Link.cc
	g++ $(OPTS) Link.cc

Node.o: Node.cc Node.h
	g++ $(OPTS) Node.cc

clean:
	rm -f *.o *~

