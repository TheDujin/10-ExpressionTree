/*
 * Node.cpp
 *
 *  Created on: March 7, 2017
 *      Author: Kevin Jin
 *  More detailed method descriptions are in the .h file.
 */

#include <iostream>
#include "Node.h"
using namespace std;

//Constructs a Node
Node::Node(char* newData) {
  data = newData;
  next = NULL;
}
//Return next
Node* Node::getNext() {
  return next;
}
//Return data
char* Node::getData() {
  return data;
}
//Sets next Node
void Node::setNext(Node* newNext) {
  next = newNext;
}
//Destructs the Node
Node::~Node() {
  next = NULL;
  delete[] data;
}


