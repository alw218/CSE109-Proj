#ifndef LEXER_CPP
#define LEXER_CPP

#include <string>
#include <iostream>
#include"Lexer.h"
#include"Token.h"

Lexer::Lexer(istream& xstream):data(xstream){
  i = 0;
  line = 1;
  pos = 0;
  at = ' ';
}

char Lexer::nextChar(){
  //get next char and update i, line, and pos
  if(!data.eof()){
    char temp = data.get();
    pos++;
    if(temp == '#'){
      while(temp != '\n' && !data.eof()){
	temp = data.get();
	pos++;
      }
    }
    if(data.eof()){
      return '$';
    }
    else{
      return temp;
    }
  }
  else{
    return '$';
  }  
}

Token Lexer::nextToken()
{
  //next token code
  do{
      switch(at){
	case '$': //EOF
	  return Token(32, "", line, pos);
	case '=': //ASSIGNMENT & EQ
	  at = nextChar();
	  if(at == '=')
	    {
	      at = nextChar();
	      return Token(14, "==", line, pos);
	    }
	  return Token(10, "=", line, pos);
	  break;
	case '<': //LT 15 LE 16
	  at = nextChar();
	  if(at == '='){
	    at = nextChar();
	    return Token(16, "<=", line, pos);
	  }
	  return Token(15, "<", line, pos);
	  break;
	case '>': //GT & GE
	  at = nextChar();
	  if(at== '='){
	    at = nextChar();
	    return Token(18, ">=", line, pos);
	  }
	  return Token(17, ">",line, pos);
	  break;
	case '!': //NE
	  at = nextChar();
	  if(at == '='){
	    at = nextChar();
	    return Token(19, "!=", line, pos);
	  }
	  return Token(33, "!", line, pos);
	  break;
	case '+': //PLUS
	  at = nextChar();
	  return Token(5, "+", line, pos);
	  break;
	case '-': //MINUS
	  at = nextChar();
	  return Token(6, "-", line, pos);
	  break;
	case '*': //TIMES
	  at = nextChar();
	  return Token(7, "*", line, pos);
	  break;
	case '/': //DIVIDE
	  at = nextChar();
	  return Token(8, "/", line, pos);
	  break;
	case '%': //REM
	  at = nextChar();
	  return Token(9, "%", line, pos);
	  break;
	case '(': //LPAREN
	  at = nextChar();
	  return Token(11, "(", line, pos);
	  break;
	case ')': //RPAREN
	  at = nextChar();
	  return Token(12, ")", line, pos);
	  break;
	case ',': //COMMA
	  at = nextChar();
	  return Token(13, ",", line, pos);
	  break;
        case '\t':case ' ':case '\r':
	  at = nextChar();
	  break;
        case '\n':
	  at = nextChar();
	  line++;
	  pos = 0;
	  break;
      case '"':{ //STRLIT
	  string tempStore = ""; //////////////
	  at = nextChar();
	  while(at != '"'){
	    tempStore += at;
	    at = nextChar();
	  }
	  at = nextChar();
	  return Token(3, tempStore, line, pos);
	  break;
      }
	default: //INTLIT FLOATLIT IDENT KEYWORD
	  if(isdigit(at)){ //INTLIT FLOATLIT
	    if(at == '0'){
	      at = nextChar();
	      if(at == 'x'){
		string hex = "0x";
		at = nextChar();
		if(isxdigit(at)){
		  while(isxdigit(at)){
		    hex += at;
		    at = nextChar();
		  }
		  return Token(1, hex, line, pos);
		}
		else{
		  hex += at;
		  return Token(33, hex, line, pos);
		}
	      }
	      else if(at != '.'){
		return Token(1, "0", line, pos);
	      }
	      else{
		at = nextChar();
		string value = "0.";
		if(isdigit(at)){
		  while(isdigit(at)){
		    value += at;
		    at = nextChar();
		  }
		  return Token(2, value, line, pos);
		}
		else{
		  string myChar = "";
		  myChar += at;
		  return Token(33, myChar, line, pos);
		}
	      }
	    }
	    else{ //digit is not 0
	      string value;
	      value += at;
	      at = nextChar();
	      while(isdigit(at)){
		value += at;
		at = nextChar();
	      }
	      if(at == '.'){
		  value += at;
		  at = nextChar();
		  if(!isdigit(at)){
		    value += at;
		      return Token(33, value, line, pos);
		  }
		  while(isdigit(at)){
		      value += at;
		      at = nextChar();
		  }
		  return Token(2, value, line, pos);
	      }
	      else{
		  return Token(1, value, line, pos);
	      }
	    }
	  }
	  else if(isalpha(at)){ //IDENT, KEYWORD
	    string value = "";
	    value =+ at;
	    at = nextChar();
	    while(isalnum(at) || at == '_'){
	      value += at;
	      at = nextChar();
	    }
	    //check for keywords
	    int keywordVal = getKeywordVal(value);
	    if(keywordVal > 19){
	      return Token(keywordVal, value, line, pos);
	    }
	    else{
	      return Token(4, value, line, pos);
	    }
	  }
	  else{
	    string val = "";
	    val += at;
	    at = nextChar();
	    return Token(33, val, line, pos);
	  }
      }
    }while(true);
}

int Lexer::getKeywordVal(string value){
  string val = "";
  unsigned int i;
  for(i = 0; i < value.length(); i++){
    val += toupper(value[i]);
  }

  if(val == "SET"){
    return 20;
  }
  else if(val == "PRINT"){
    return 21;
  }
  else if(val == "WHILE"){
    return 22;
  }
  else if(val == "DO"){
    return 23;
  }
  else if(val == "END"){
    return 24;
  }
  else if(val == "AND"){
    return 25;
  }
  else if(val == "OR"){
    return 26;
  }
  else if(val == "IF"){
    return 27;
  }
  else if(val == "THEN"){
    return 28;
  }
  else if(val == "ELSE"){
    return 29;
  }
  else if(val == "ENDIF"){
    return 30;
  }
  else if(val == "PROGRAM"){
    return 31;
  }
  else{
    return -1;
  }
}


#endif
