#ifndef TOKEN_CC
#define TOKEN_CC

#include <string>
#include "Token.h"

Token::Token()
{}

Token::Token(int type0, string lexeme0, int line0, int pos0)
 :tokenType(type0),lexeme(lexeme0),lineNum(line0),charPos(pos0)
{}

Token::~Token()
{}

int Token::type(){
  return tokenType;
}

string Token::getLexeme(){
  return lexeme;
}

int Token::line(){
  return lineNum;
}

int Token::pos(){
  return charPos;
}

#endif
