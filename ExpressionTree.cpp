/*
 * ShuntingYard.cpp
 *
 *  Created on: March 7, 2017
 *      Author: Kevin Jin
 *  This file uses the shunting yard algorithm to convert infix notation to postfix.
 */

#include <iostream>
#include "Node.h"
#include "BinaryNode.h"
#include <string.h>
using namespace std;

//Define the functions used by a Stack data structure
void push(Node* newNode, Node* & bottom);
Node* pop(Node* & bottom);
Node* peek(Node* & bottom);
void createTree (BinaryNode* & root, Node* & tempStack);

//Main method. Prompts for the infix expression, then converts it.
int main() {
	const char quit[] = "QUIT";
	bool isRunning = true;
	while (isRunning) {
		//Read in input and define the Stack's "head" (bottom of the stack) as NULL
		char* input = new char[101];
		Node* head = NULL;

		cout << "Please input the infix expression with spaces between each token. Or, you could type \"quit\" to quit."
				<< endl << "Input: ";
	        cin.get(input, 100);
		cin.ignore();
		if (strncasecmp(quit, input, strlen(quit)) == 0) {
			isRunning = false;
		}
		else {
			//Creates output char* and uses a counter to keep track how far we've written into it.
			int counter = 0;
			char* output = new char[201];
			//If the expression is invalid, bool invalid is set to true and program kills itself.
			bool invalid = false;
			for (int i = 0; i < strlen(input); i++) {
				//For each char in input, if it's a number write it to output, else perform operations upon the operator stack.
				if (input[i] - '0' >= 0 && input[i] - '0' <= 9) {
					output[counter] = input[i];
					counter++;
				}
				//If it's AS, pop out of the stack all operators with more precedence (including other AS) then push it onto the stack.
				else if (input[i] == '+' || input[i] == '-') {
					while (peek(head) != NULL && (peek(head)->getData()[0] == '^' || peek(head)->getData()[0] == '*' || peek(head)->getData()[0] == '/'
							|| peek(head)->getData()[0] == '+' || peek(head)->getData()[0] == '-')) {
									if (output[counter - 1] != ' ')
										output[counter++] = ' ';
									output[counter] = pop(head)->getData()[0];
									counter++;
								}
								char* temp = new char[1];
								temp[0] = input[i];
								push(new Node(temp), head);
								output[counter++] = ' ';
				}
				//If it's DM, ditto AS.
				else if (input[i] == '*' || input[i] == '/') {
					while (peek(head) != NULL && (peek(head)->getData()[0] == '^' || peek(head)->getData()[0] == '*' || peek(head)->getData()[0] == '/')) {
						if (output[counter - 1] != ' ')
							output[counter++] = ' ';
						output[counter] = pop(head)->getData()[0];
						counter++;
					}
					char* temp = new char[1];
					temp[0] = input[i];
					push(new Node(temp), head);
					output[counter++] = ' ';
				}
				//If it's E, push it on (it will always have higher precedence than any other operators on the stack).
				else if (input[i] == '^') {
					char* temp = "^";
					push(new Node(temp), head);
					output[counter++] = ' ';
				}
				//If it's a left paren, push it.
				else if (input[i] == '(') {
					char* temp = "(";
					push(new Node(temp), head);
				}
				//If it's a right paren, pop everything between it and the corresponding left paren.
				else if (input[i] == ')') {
					while (peek(head)->getData()[0] != '(') {
						if (output[counter - 1] != ' ')
							output[counter++] = ' ';
						output[counter] = pop(head)->getData()[0];
						counter++;
					}
					pop(head);
				}
				//If it's anything else that isn't a natural part of a char* or isn't a space, we have an error.
				else if (input[i] != '\0' && input[i] != '\r' && input[i] != ' '){
					cout << "Invalid input" << endl;
					//It's invalid, so program kills itself.
					invalid = true;
					i = strlen(input);
				}

			}
			//If the expression is not invalid, pop the operator stack onto output then print output.
			if (!invalid) {
				while (peek(head) != NULL) {
					output[counter++] = ' ';
					output[counter] = pop(head)->getData()[0];
					counter++;
				}
				cout << "The postfix expression created from your input: " << output << endl;
				bool loopThis = true;
				BinaryNode* root = NULL;
				Node* tempStack = NULL;
				char* temp = new char[80];
				int counter = 0;
				for (int i = 0; i < strlen(output); i++) {
					if (output[i] != ' ') {
						temp[counter] = output[i];
						counter++;
					}
					else {
						temp[counter] = '\0';
						push(new Node(temp), tempStack);
						counter = 0;
						temp = new char[80];
					}
				}
				createTree(root, tempStack);
				temp[counter] = '\0';
				push(new Node(temp), tempStack);

//				createTree(output, root, 2);
				while (loopThis) {
					cout << "Would you like to print \"prefix\", \"postfix\", or enter the \"next\" string?" << endl << "Input: ";
					cin.get(input, 100);
					cin.ignore();
					if (input[1] == 'r' || input[1] == 'R') {
						cout << "Prefix notation" << endl;
						//TODO Write prefix
					}
					else if (input[1] == 'o' || input[1] == 'O') {
						cout << "Postfix notation" << endl;
						//TODO Write postfix
					}
					else if (input[0] == 'n' || input[0] == 'N') {
						loopThis = false;
					}
					else {
						cout << "Invalid input, please try again." << endl;
					}
				}
			}
		}
	}
	cout << "Thank you for using my program!" << endl;
	return 0;
}


//Pushes a node onto the top of the stack. It replaces bottom/head if it's NULL.
void push(Node* newNode, Node* & bottom) {
	if (peek(bottom) != NULL)
		peek(bottom)->setNext(newNode);
	else
		bottom = newNode;
}
//Pop the topmost node, if there is one. If the topmost node is bottom/head, pop it then set it to NULL.
Node* pop(Node* & bottom) {
	Node* current = bottom;
	Node* temp = NULL;
	if (current != NULL) {
		if (current->getNext() != NULL) {
			while (current->getNext()->getNext() != NULL)
				current = current->getNext();
			temp = current->getNext();
			current->setNext(NULL);
		}
		else {
			temp = bottom;
			bottom = NULL;
		}
	}
	return temp;
}
//Returns the topmost node without popping it.
Node* peek(Node* & bottom) {
	Node* current = bottom;
		if (current != NULL) {
			while (current->getNext() != NULL)
				current = current->getNext();
			return current;
		}
		else
			return NULL;
}

void createTree (BinaryNode* & root, Node* & tempStack) {
	BinaryNode* current = root;
	while (peek(tempStack) != NULL) {
		if (root == NULL) {
			root = new BinaryNode(pop(tempStack)->getData(), NULL);
		}
		else {
			while (current->getLeft() != NULL && current->getRight() != NULL) {
				current = current->getParent();
			}
			if (current->getLeft() == NULL) {
				if (peek(tempStack)->getData()[0] - '0' >= 0 && peek(tempStack)->getData()[0] - '0' <= 9)
					current->setLeft(new BinaryNode(pop(tempStack)->getData(), current));
				else {
					current->setLeft(new BinaryNode(pop(tempStack)->getData(), current));
					current = current->getLeft();
				}
			}
			else if (current->getRight() == NULL) {
				if (peek(tempStack)->getData()[0] - '0' >= 0 && peek(tempStack)->getData()[0] - '0' <= 9)
					current->setRight(new BinaryNode(pop(tempStack)->getData(), current));
				else {
					current->setRight(new BinaryNode(pop(tempStack)->getData(), current));
					current = current->getRight();
				}
			}
		}

	}
}
