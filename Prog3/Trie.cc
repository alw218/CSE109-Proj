
/*
Create a class Trie that contains:
1) A Node* member variable that holds a pointer to the start node.
2) A member function: void put(string key, int value) for adding a new key and value to
the Trie.
3) A member function: int get(string key) for retrieving a value from the Trie using the
key.
4) A constructor
5) A destructor
*/


#include "Trie.h"
#include "Node.h"
#include "Link.h"

#include <string>
#include <stdio.h>
using namespace std;


Trie::Trie(){
  startNode = new Node();
}

Trie::~Trie(){}

void Trie::doit(int **x){
  int *tmp = x[0];
  x[0] = x[1];
  x[1] = tmp;
}

void Trie::put(string key, int value){
  //code that goes through and adds a key and value to trie
  Node *currentNode = startNode;
  unsigned int letterPos;
  //goes through each letter in key either traversing or adding new
  //nodes and links
  for(letterPos = 0; letterPos < key.length(); letterPos++){
    bool linkExists = false;
    int linkID; 
    int i;
    int cNumLinks = currentNode->numLinks;
    //go through each existing link on current node and check for
    //current letter
    Link *currentLink;
    for(i = 0; i < cNumLinks; i++){
      currentLink = currentNode->links[i];
      char cLinkChar = currentNode->links[i]->linkChar;
      if(cLinkChar == key.at(letterPos)){
	linkExists = true;
	linkID = i;
      }
    }
    if(linkExists){
      //go to next node
      currentNode = currentNode->links[linkID]->nextNode;
      if(letterPos + 1 == key.length()){
	currentNode->nodeValue = value;
      }
    }else{
      //add link and connected node
      if(letterPos + 1 == key.length()){ //adding node with final value
	currentNode = currentNode->addLink(key.at(letterPos),value);
      }else{ //link another intermediate node
	currentNode = currentNode->addLink(key.at(letterPos));
      }
    }
  }
}

int Trie::get(string key){
  //code returns value of given key
  Node *currentNode = startNode;
  unsigned int letterPos;
  //goes through each letter in key
  for(letterPos = 0; letterPos < key.length(); letterPos++){
    bool linkExists = false;
    int linkID;
    int i;
    int cNumLinks = currentNode->numLinks;
    //go through each existing link on current node and check for
    //current letter
    Link *currentLink;
    for(i = 0; i < cNumLinks; i++){
      currentLink = currentNode->links[i];
      char cLinkChar = currentNode->links[i]->linkChar;
      if(cLinkChar == key.at(letterPos)){
	linkExists = true;
	linkID = i;
      }
    }
    if(linkExists){
      //go to next node
      currentNode = currentNode->links[linkID]->nextNode;
      if(letterPos + 1 == key.length()){
	return currentNode->nodeValue;
      }
    }else{
      //could not be found
      return(-1);
    }
  }
  

  //returns -1 if nothing was passed
  return(-1);
}
