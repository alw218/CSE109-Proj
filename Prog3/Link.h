/*
  CSE 109
  Amber Wallace
  alw218
  Program Description:
  Program #3
*/

#pragma once
#include "Node.h"

//class Node;

class Link{
public:
  //constructor
  Link(char letter);
  Link(char letter, int value);

  //destructor
  ~Link();

  //members
  char linkChar;
  Node *nextNode;
};
  
