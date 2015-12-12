#ifndef LEXER_H
#define LEXER_H

#include <string>
#include "Token.h"
#include <iostream>

using namespace std;

class Lexer{
private:
  istream& data;
  char at;
  int line;
  int pos;
  int i;
  int getKeywordVal(string value);
  char nextChar();
  
public:
  Lexer(istream& xstream);
  Token nextToken();
};

#endif
