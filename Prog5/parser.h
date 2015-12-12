#ifndef PARSER_H
#define PARSER_H

#include "Token.h"
#include "Lexer.h"
#include <iostream>
#include <string>
#include <cstring>
#include <stdlib.h>
#include <sstream>

using namespace std;

class Parser {

private:

  enum Operation {
    ADD, SUB, AND, DIV, REM, ISEQ, ISGE, ISGT, ISLE, ISLT,
    ISNE, MULT, OR,
    LOADL, LOADV, STOREV, JUMPF, JUMP, INSLABEL,
    PRINT, SEQ, NULLX, PRINTLN, PRINTS
  };

public:
  class TreeNode {

  public:

    Operation op;
    string val;
    TreeNode *leftChild;
    TreeNode *rightChild;

    void init(Operation opx, string valx, TreeNode *leftChildx, TreeNode *rightChildx) {
      op = opx;
      val = valx;
      leftChild = leftChildx;
      rightChild = rightChildx;
    }


    TreeNode(Operation op, string val) {
      init(op, val, NULL, NULL);
    }

    TreeNode(Operation op, string val, TreeNode *leftChild, TreeNode *rightChild) {
      init(op, val, leftChild, rightChild);
    }

    TreeNode(Operation op) {
      init(op, "", NULL, NULL);
    }

    TreeNode(Operation op, TreeNode *leftChild, TreeNode *rightChild) {
      init(op, "", leftChild, rightChild);
    }

    static string operandFormat(TreeNode *node) {
      if (node->op == PRINTS)
	return "\"" + node->val + "\"";
      return node->val;
    }

    static string toString(TreeNode *node) {
      return toString0(node, 0);
    }

    static string toString0(TreeNode *node, int spaces) {
      static string blanks = "                                        ";
      string left = "";
      string right = "";
      bool isLeaf = true;
      if (node->leftChild != NULL) {
	left = toString0(node->leftChild, spaces+2);
	isLeaf = false;
      }
      if (node->rightChild != NULL) {
	right = toString0(node->rightChild, spaces+2);
	isLeaf = false;
      }
      string ret;
      if (isLeaf) {
	ret = blanks.substr(0, spaces) + ops[node->op] + "[" + operandFormat(node) + "]";
      } else {
	ret = blanks.substr(0, spaces) + ops[node->op] + "(\n" + left + ",\n" + right + "\n" +
	  blanks.substr(0, spaces) + ")";
      }
      return ret;
    }

  };

private:
  Lexer lexer;
  Token token;
  ostream& out;
  int lindex;
  int tindex;

  string itos(int i) { stringstream ss; ss << i; string res = ss.str(); return res;}

  string makeLabel() { string tmp = "L"; stringstream ss; ss << ++lindex; string res = ss.str(); tmp = tmp + res; return tmp;}


  string makeTemp() { string tmp = "$TEMP"; stringstream ss; ss << ++tindex; string res = ss.str(); tmp = tmp + res; return tmp;}

  static const string ops[];
  void emit(Operation op, string object) { out << ops[op] << " " <<  object << endl; }
  void emit(Operation op) { out << ops[op] << endl; }
  void emit(string label) { out << label << endl; }

  void gen(TreeNode* node);
  void error(string message);
  void check(int tokenType, string message);
  void optimizeAndGenerateExpressionCode(TreeNode* exp);

public:
  TreeNode* optimize(TreeNode* node);
  TreeNode *program();
  TreeNode* compoundStatement();
  TreeNode* statement();
  TreeNode* setStatement();
  TreeNode* parsePrintExpression();
  TreeNode* printStatement();
  TreeNode* whileStatement();
  TreeNode* forStatement();
  TreeNode* ifStatement();
  TreeNode* switchStatement();
  TreeNode* logicalExpression();
  TreeNode* relationalExpression();
  TreeNode* expression();
  TreeNode* term();
  TreeNode* factor();


  Parser(Lexer& lexer, ostream& out);
  ~Parser();

  void generateCode(TreeNode* node);
  void genCode();
};

#endif
