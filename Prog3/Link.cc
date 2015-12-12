/*
  CSE 109
  Amber Wallace
  alw218
  Program Description:
  Program #3
*/

#include "Link.h"
#include "Node.h"

Link::Link(char letter){
  linkChar = letter;
  nextNode = new Node();
}

Link::Link(char letter, int value):linkChar(letter){
  nextNode = new Node(value);
}

Link::~Link(){}
