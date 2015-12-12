/*
  Amber Wallace
  alw217
  cse109
  Prog5
*/

#include "parser.h"
#include <cstring>

const string Parser::ops[] = {"ADD", "SUB", "AND", "DIV", "REM", "ISEQ", "ISGE", "ISGT", "ISLE",
			      "ISLT", "ISNE", "MULT", "OR", "LOADL", "LOADV", "STOREV", "JUMPF",
			      "JUMP", "INSLABEL", "PRINT", "SEQ", "NULLX", "PRINTLN", "PRINTS"};

Parser::Parser(Lexer& lexerx, ostream& outx): lexer(lexerx), out(outx), lindex(1), tindex(1) {
  token = lexer.nextToken();
}

Parser::~Parser() {
}

void Parser::genCode() {
  TreeNode* programNode = program();
  generateCode(programNode);
}

void Parser::gen(TreeNode* node) {
  switch (node->op) {
  case SEQ:
  case NULLX:
    break;
  case LOADL:
  case LOADV:
  case STOREV:
  case JUMPF:
  case JUMP:
    emit(node->op, node->val);
    break;
  case PRINTS:
    emit(node->op, "\"" + node->val + "\"");
    break;
  case INSLABEL:
    emit(node->val);
    break;
  default:
    emit(node->op);
    break;
  }
}

void Parser::generateCode(TreeNode* node) {
  if (node != NULL) {
    generateCode(node->leftChild);
    generateCode(node->rightChild);
    gen(node);
  }
}

Parser::TreeNode* Parser::optimize(TreeNode* node) {
  return NULL;
}

void Parser::error(string message) {
  cerr << message << " Found " << token.getLexeme() << " at line " << token.line() << " position " << token.pos() << endl;
  exit(1);
}

void Parser::check(int tokenType, string message) {
  if (token.type() != tokenType)
    error(message);
}

/*<factor> = LPAREN <expression> RPAREN | INTLIT | FLOATLIT | IDENT*/
Parser::TreeNode* Parser::factor() {
  TreeNode* factorNode;
  int tokenType = token.type();
  if(tokenType == Token::INTLIT){
    factorNode = new TreeNode(LOADL, token.getLexeme());
    token = lexer.nextToken();
  }
  else if(tokenType == Token::FLOATLIT){
    factorNode = new TreeNode(LOADL, token.getLexeme());
    token = lexer.nextToken();
  }
  else if(tokenType == Token::IDENT){
    factorNode = new TreeNode(LOADV, token.getLexeme());
    token = lexer.nextToken();

  }
  else if(tokenType == Token::LPAREN){
    token = lexer.nextToken();
    factorNode = expression();
    tokenType = token.type();
    if(tokenType == Token::RPAREN){
      token = lexer.nextToken();
    }
    else {
      error("Missing RPAREN after expression");
    }
  }
  else{
    error("Unrecognized factor");
  }
  return factorNode;
}

/*<term> = <factor> { TIMES <factor> | DIVIDE <factor> | REM <factor> }*/
Parser::TreeNode* Parser::term() {
  TreeNode* termNode = factor();
  TreeNode* factorNode;
  int tokenType = token.type();
  while (tokenType == Token::TIMES || tokenType == Token::DIVIDE || tokenType == Token::REM) {
    token = lexer.nextToken();
    factorNode = factor();
    switch (tokenType) {
    case Token::TIMES:
      termNode = new TreeNode(MULT, termNode, factorNode);
      break;
    case Token::DIVIDE:
      termNode = new TreeNode(DIV, termNode, factorNode);
      break;
    case Token::REM:
      termNode = new TreeNode(REM, termNode, factorNode);
      break;
    }
    tokenType = token.type();
  }
  return termNode;
}

/*<expression> = <term> { PLUS <term> | MINUS <term> }*/
Parser::TreeNode* Parser::expression() {
  TreeNode* expressionNode = term();
  TreeNode* termNode;
  int tokenType = token.type();
  while (tokenType == Token::PLUS || tokenType == Token::MINUS) {
    token = lexer.nextToken();
    termNode = term();
    switch (tokenType) {
    case Token::PLUS:
      expressionNode = new TreeNode(ADD, expressionNode, termNode);
      break;
    case Token::MINUS:
      expressionNode = new TreeNode(SUB, expressionNode, termNode);
      break;
    }
    tokenType = token.type();
  }
  return expressionNode;
}

Parser::TreeNode* Parser::relationalExpression() {
  return NULL;
}

Parser::TreeNode* Parser::logicalExpression() {
  return NULL;
}

/*<setstatement> = SET IDENT ASSIGN <expression>*/
Parser::TreeNode* Parser::setStatement() {
  TreeNode* setstatementNode = NULL;
  TreeNode* expressionNode = NULL;
  if(token.type() == Token::SET){
    token = lexer.nextToken();
    if(token.type() == Token::IDENT){
      setstatementNode = new TreeNode(STOREV, token.getLexeme());
      token = lexer.nextToken();
      if(token.type() == Token::ASSIGN){
	token = lexer.nextToken();
	expressionNode = expression();
	setstatementNode = new TreeNode(SEQ, expressionNode, setstatementNode); 
      }
      else{
	error("Missing assignment after IDENT");
      }
    }
    else{
      error("Missing IDENT after SET");
    }
  }
  else{
    error("Unrecognizable setstatement");
  }
      
  return setstatementNode;
}

/*<printExpression> = <expression> | STRLIT*/
Parser::TreeNode* Parser::parsePrintExpression() {
  TreeNode* printENode = NULL;
  if(token.type() == Token::STRLIT){
    printENode = new TreeNode(PRINTS, token.getLexeme());
    token = lexer.nextToken();
  }
  else{
    printENode = new TreeNode(PRINT, expression(), NULL);
  }
  
  return printENode;
}

/*<printstatement> = PRINT <printExpression> { COMMA <printExpression> }*/
Parser::TreeNode* Parser::printStatement() {
  TreeNode* printstatementNode = NULL;
  if(token.type() == Token::PRINT){
    token = lexer.nextToken();
    printstatementNode = parsePrintExpression();
    while(token.type() == Token::COMMA){
      token = lexer.nextToken();
      printstatementNode = new TreeNode(PRINTLN, printstatementNode, parsePrintExpression());
    }
  }
  else{
    error("Unrecognized printstatement");
  }
  return printstatementNode;
}

Parser::TreeNode* Parser::whileStatement() {
  return NULL;
}

Parser::TreeNode* Parser::forStatement() {
  return NULL;
}

Parser::TreeNode* Parser::ifStatement() {
  return NULL;
}

Parser::TreeNode* Parser::switchStatement() {
  return NULL;
}

/*<statement> = <setstatement> | <printstatement>*/
Parser::TreeNode* Parser::statement() {
  TreeNode* statement = NULL;
  switch (token.type()) {
  case Token::SET:
    statement = setStatement();
    break;
  case Token::PRINT:
    statement = printStatement();
    break;
  default:
    error("Unrecognized statement");
    break;
  }
  return statement;
}

/*<compoundstatement> = <statement> { <statement> }*/
Parser::TreeNode* Parser::compoundStatement() {
  TreeNode* compoundstatementNode = statement();
  TreeNode* statementNode;
  int tokenType = token.type();
  while(token.type() == Token::SET || token.type() == Token::PRINT){
    statementNode = statement();
    switch (tokenType){
    case Token::SET:
      compoundstatementNode = new TreeNode(NULLX, compoundstatementNode, statementNode);
      break;
    case Token::PRINT:
      compoundstatementNode = new TreeNode(NULLX, compoundstatementNode, statementNode);
      break;
    }
    tokenType = token.type();
  }
  return compoundstatementNode;
}

/*<program> = PROGRAM IDENT <compoundstatement> END PROGRAM*/
Parser::TreeNode* Parser::program() {
  TreeNode* programNode = NULL;
  if(token.type() == Token::PROGRAM){
    token = lexer.nextToken();
    if(token.type() == Token::IDENT){
      token = lexer.nextToken();
      programNode = compoundStatement();
      if(token.type() == Token::END){
	token = lexer.nextToken();
	if(token.type() == Token::PROGRAM){
	}
	else{
	  error("Missing 'PROGRAM' at end of program");
	}
      }
      else{
	error("Missing 'END' at end of program");
      }
    }
    else{
      error("Unrecognized compoundstatement");
    }
  }
  else{
    error("Missing 'PROGRAM' at begining of program");
  }
  return programNode;
}
