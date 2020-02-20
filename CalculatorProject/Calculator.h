#ifndef CALCULATOR_H
#define CALCULATOR_H

#include <string>
#include <iostream>
#include <sstream>

using namespace std;

struct Node {
	int operand;
	string operation;
	Node* nextPtr;
};

class Calculator {
private:
	Node* head;
public:
	Calculator() {
		head = nullptr;
	}

	string getInput();
	void buildList(string);
	void appendNode(Node*);
};

string Calculator::getInput() {
	string expression;
	cout << "\nPlease enter expression(s) to be evaluated with spaces in between. Enter 0 to exit." << endl;
	getline(cin, expression);
	return expression;
}

void Calculator::buildList(string expression) {
	int counter = 0;
	string holder;
	istringstream parser(expression);
	Node* currentNode;
	currentNode = head;
	while (parser >> holder) {
		if (counter % 2 == 0)
		{
			Node* newNode = new Node;
			newNode->operand = stoi(holder);
		}
		else
		{
			currentNode->operation = holder;
		}
	}
}

void Calculator::appendNode(Node* newNode)
{
	Node* nodePtr;
	nodePtr = head;
	while (nodePtr->nextPtr) {
		nodePtr = nodePtr->nextPtr;
	}
	nodePtr->nextPtr = newNode;
	newNode->nextPtr = nullptr;
	return;
}
#endif // !CALCULATOR_H