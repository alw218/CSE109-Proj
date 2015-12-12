/*
  CSE109
  Amber Wallace
  alw218
  Program Description:
  Program #4
*/

#include <iostream>
#include <string>
#include <fstream>
#include <cstdio>
#include <cstdlib>
#include "Lexer.h"
#include "Token.h"

using namespace std;

int main(int argc, char **argv){
  Lexer *lex;
  ifstream myStream;
  if(argc >  1){
    myStream.open(argv[1]);
    lex = new Lexer(myStream);
  }
  else{
    lex = new Lexer(cin);
  }

  Token tok = lex->nextToken();
  cout << "Type\tLexeme\tLine #\t Pos\n";
  while(tok.type() != 32){
    cout << tok.type() << "\t" << tok.getLexeme() << "\t" << tok.line() << "\t" << tok.pos() << endl;
    tok = lex->nextToken();
  }
  
  return(1);
}
