/*
  4) Create a class Node that contains:
  1) An int member variable to hold the value for the Node.
  2) An array member variable of 10 Link* to hold up to 10 Links to
  other Nodes
  3) An int member variable to hold the number of links being used by
  this Node.
  4) A constructor
  5) A destructor
*/
#pragma once
class Link;

class Node{
public:
  //constructor
  Node();
  Node(int nodeValue);

  //destructor
  ~Node();
  
  //members
  Node * addLink(char letter);
  Node * addLink(char letter, int value);
  
  int nodeValue;
  Link *links[26];
  int numLinks;
};
