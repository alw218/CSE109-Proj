/*
4) Create a class Node that contains:
1) An int member variable to hold the value for the Node.
2) An array member variable of 10 Link* to hold up to 10 Links to other Nodes
3) An int member variable to hold the number of links being used by this Node.
4) A constructor
5) A destructor
*/

#include "Node.h"
#include "Link.h"

Node::Node(){
  //default node
  nodeValue = -1;
  numLinks = 0;
}

Node::Node(int nodeValue):nodeValue(nodeValue){
  //node with end value for some key
  numLinks = 0;
}

Node::~Node(){
  int i;
  for(i = 0; i < numLinks; i++){
    delete links[i];
  }
}

Node *  Node::addLink(char letter){
  //add a link with the given letter
  Link *newLink = new Link(letter);
  links[numLinks] = newLink;
  numLinks++;
  return newLink->nextNode;
}

Node * Node::addLink(char letter, int value){
  //add a link with the given letter
  Link *newLink = new Link(letter, value);
  links[numLinks] = newLink;
  numLinks++;
  return newLink->nextNode;
}
