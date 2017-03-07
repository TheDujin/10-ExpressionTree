/*
 * Node.h
 *
 *  Created on: March 7, 2017
 *      Author: Kevin Jin
 */

#ifndef NODE_H_
#define NODE_H_

#include <iostream>
using namespace std;
/** -- Class Node --
  * The Node object is a component that, in conjunction with other nodes,
  * can form singly-linked lists.
  * The Node can be used to store and access chars.
  *
  * Members:
  * private char data
  * - The char value that the Node holds.
  *    The data of a Node cannot be changed after construction.
  * private Node* next
  * - The Node pointer that represents what the next Node in the list is.
  *
  * Methods:
  * Node(char newData)
  * - Constructs a new Node object
  *    Parameters: newData - the char value that the member data is set to.
  * Node* getNext()
  * - Returns the Node pointer that is the next Node in the singly-linked list;
  *    returns the value in the member next.
  * char getData();
  * - Returns the char value that this Node contains;
  *    returns the value in the member data.
  * void setNext(Node* newNext)
  * - Sets the value for the member next.
  *    Parameters: newNext - the Node pointer that the member next is set to.
  * ~Node()
  * - Destructs the Node.
  *    WARNING: The user must use calls to setNext to fix any gaps in the list
  *    caused by deleting the Node.
  *
  **/
class Node {
 public:
  Node(char newData);
  Node* getNext();
  char getData();
  void setNext(Node* newNext);
  ~Node();

 private:
  char data;
  Node* next;
};



#endif /* NODE_H_ */
