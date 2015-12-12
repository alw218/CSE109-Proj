#Amber Wallace                                                                                                                                                                      
#CSE 109                                                                                                                                                            
OBJ= assembler.o
OPTS= -g -c -Wall -Werror

assembler: $(OBJ)
	g++ -o assembler $(OBJ)

assembler.o: assembler.cc
	g++ $(OPTS) assembler.cc

clean:
	rm -f *.o *~

