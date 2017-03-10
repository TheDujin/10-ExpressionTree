/*
 * BinaryNode.h
 *
 *  Created on: Mar 9, 2017
 *      Author: 293359
 */

#ifndef BINARYNODE_H_
#define BINARYNODE_H_

#include <iostream>
using namespace std;
/** -- Class BinaryNode --
  * The BinaryNode object is a component that, in conjunction with other binary nodes,
  * can form binary trees.
  * The BinaryNode can be used to store and access char pointers.
  *
  * Members:
  * private char* data
  * - The char* value that the Node holds.
  *    The data of a BinaryNode cannot be changed after construction.
  * private BinaryNode* left
  * - The BinaryNode pointer that represents the left child in the tree.
  * private BinaryNode* right
  * - The BinaryNode pointer that represents the right child in the tree.
  * private BinaryNode* parent
  * - The BinaryNode pointer that represents the parent of this BinaryNode (root's parent should be null).
  *
  * Methods:
  * BinaryNode(char* newData, BinaryNode* parent)
  * - Constructs a new BinaryNode object
  *    Parameters: newData - the char* value that the member data is set to.
  * BinaryNode* getLeft()
  * - Returns the BinaryNode pointer that is the left child of this BinaryNode;
  *    returns the value in the member left.
  * BinaryNode* getRight()
  * - Returns the BinaryNode pointer that is the right child of this BinaryNode;
  *    returns the value in the member right.
  * BinaryNode* getParent()
  * - Returns the BinaryNode pointer that is the parent of this BinaryNode;
  *    returns the value in the member parent.
  * char* getData();
  * - Returns the char* value that this BinaryNode contains;
  *    returns the value in the member data.
  * void setLeft(BinaryNode* newLeft)
  * - Sets the value for the member left.
  *    Parameters: newLeft - the BinaryNode pointer that the member left is set to.
  * void setRight(BinaryNode* newRight)
  * - Sets the value for the member right.
  *    Parameters: newRight - the BinaryNode pointer that the member right is set to.
  * ~BinaryNode()
  * - Destructs the BinaryNode.
  *
  **/
class BinaryNode {
 public:
  BinaryNode(char* newData, BinaryNode* newParent);
  BinaryNode* getLeft();
  BinaryNode* getRight();
  BinaryNode* getParent();
  char* getData();
  void setLeft(BinaryNode* newLeft);
  void setRight(BinaryNode* newRight);
  ~BinaryNode();

 private:
  char* data;
  BinaryNode* left;
  BinaryNode* right;
  BinaryNode* parent;
};



#endif /* BINARYNODE_H_ */
