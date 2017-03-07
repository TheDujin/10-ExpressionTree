/*
 * ShuntingYard.cpp
 *
 *  Created on: March 7, 2017
 *      Author: Kevin Jin
 *  This file uses the shunting yard algorithm to convert infix notation to postfix.
 */

#include <iostream>
#include "Node.h"
#include <string.h>
#include <stdio.h>
using namespace std;

//Define the functions used by a Stack data structure
void push(Node* newNode, Node* & bottom);
Node* pop(Node* & bottom);
Node* peek(Node* & bottom);

//Main method. Prompts for the infix expression, then converts it.
int main() {
	//Read in input and define the Stack's "head" (bottom of the stack) as NULL
	char* input = new char[101];
	Node* head = NULL;

	cout << "Please input the infix expression with spaces between each token." << endl << "Input: ";
	cin.get(input, 100);
	cin.ignore();
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
			while (peek(head) != NULL && (peek(head)->getData() == '^' || peek(head)->getData() == '*' || peek(head)->getData() == '/'
					|| peek(head)->getData() == '+' || peek(head)->getData() == '-')) {
							if (output[counter - 1] != ' ')
								output[counter++] = ' ';
							output[counter] = pop(head)->getData();
							counter++;
						}
						push(new Node(input[i]), head);
						output[counter++] = ' ';
		}
		//If it's DM, ditto AS.
		else if (input[i] == '*' || input[i] == '/') {
			while (peek(head) != NULL && (peek(head)->getData() == '^' || peek(head)->getData() == '*' || peek(head)->getData() == '/')) {
				if (output[counter - 1] != ' ')
					output[counter++] = ' ';
				output[counter] = pop(head)->getData();
				counter++;
			}
			push(new Node(input[i]), head);
			output[counter++] = ' ';
		}
		//If it's E, push it on (it will always have higher precedence than any other operators on the stack).
		else if (input[i] == '^') {
			push(new Node('^'), head);
			output[counter++] = ' ';
		}
		//If it's a left paren, push it.
		else if (input[i] == '(') {
			push(new Node('('), head);
		}
		//If it's a right paren, pop everything between it and the corresponding left paren.
		else if (input[i] == ')') {
			while (peek(head)->getData() != '(') {
				output[counter] = pop(head)->getData();
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
			output[counter] = pop(head)->getData();
			counter++;
		}
		cout << output << endl;
	}
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
