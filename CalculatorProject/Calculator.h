#ifndef CALCULATOR_H
#define CALCULATOR_H

#include <string>
#include <iostream>
#include <stringstream>

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
	void appendNode(Node*)
};

string Calculator::getInput() {
	string expression;
	cout << "\nPlease enter expression(s) to be evaluated with spaces in between. Enter 0 to exit." << endl;
	getline(cin, expression);
	return expression;
}

void Calculator::buildList(string expression) {
	string holder;
	int counter = 0;
	stringstream parser(expression)
	{
		while (expression >> holder) {
			if (counter % 2 == 0)
			{
				Node* newNode = new Node;
				newNode->operand = stoi(holder);
			}
			else
			{

			}
		}
	}
}

void Calculator::appendNode(Node* newNode)
{
	Node* nodePtr;
	nodePtr = head;
	while (nodePtr->next) {
		nodePtr = nodePtr->next;
	}
	nodePtr->next = newNode;
	newNode->next = nullptr;
	return;
}
#endif // !CALCULATOR_H