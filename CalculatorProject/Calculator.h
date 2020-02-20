#ifndef CALCULATOR_H
#define CALCULATOR_H

#include <string>
#include <iostream>
#include <sstream>

using namespace std;

struct Node {
	int operand;
	string operation;
	Node* nextPtr = nullptr;
};

class Calculator {
private:
	Node* head;
	bool validInput = false;
public:
	Calculator() {
		head = nullptr;
	}

	string getInput();
	void buildList(string);
	void calculateList();
	int multiply(int, int);
	int divide(int, int);
	int add(int, int);
	int subtract(int, int);
	//void appendNode(Node*);
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
	bool integerCheck;
	while (parser >> holder) {
		if (counter % 2 == 0)
		{
			Node* newNode = new Node;
			integerCheck = (holder.find_first_not_of("0123456789") == string::npos);
			if (integerCheck)
			{
				newNode->operand = stoi(holder);
				if (!head)
				{
					currentNode = newNode;
				}
				else
				{
					currentNode->nextPtr = newNode;
					currentNode = currentNode->nextPtr;
				}
			}
			else
			{
				cout << "\nInvalid entry.\n";
				break;
			}
		}
		else
		{
			if (holder == "*" || holder == "/" || holder == "+" || holder == "-")
			{
				currentNode->operation = holder;
			}
			else
			{
				cout << "\nInvalid input.\n";
				validInput = false;
				break;
			}
			currentNode->nextPtr = nullptr;
		}
		counter++;
	}
	return;
}

void Calculator::calculateList() {
	Node* nodePtr;
	Node* nextNode;
	nodePtr = head;
	while (nodePtr->nextPtr)
	{
		nextNode = nodePtr->nextPtr;
		if (nodePtr->operation == "*")
		{
			nodePtr->operand = multiply(nodePtr->operand, nextNode->operand);
			nodePtr->operation = nextNode->operation;
			nodePtr->nextPtr = nextNode->nextPtr;
			delete(nextNode);
		}
		else if (nodePtr->operation == "/")
		{
			if (nextNode->operand == 0)
			{
				cout << "\nDivision by 0 is not possible.\n";
				break;
			}
			nodePtr->operand = divide(nodePtr->operand, nextNode->operand);
			nodePtr->operation = nextNode->operation;
			nodePtr->nextPtr = nextNode->nextPtr;
			delete(nextNode);
		}
		else if (nodePtr->operation == "+")
		{
			nodePtr->operand = add(nodePtr->operand, nextNode->operand);
			nodePtr->operation = nextNode->operation;
			nodePtr->nextPtr = nextNode->nextPtr;
			delete(nextNode);
		}
		else if (nodePtr->operation == "-")
		{
			nodePtr->operand = multiply(nodePtr->operand, nextNode->operand);
			nodePtr->operation = nextNode->operation;
			nodePtr->nextPtr = nextNode->nextPtr;
			delete(nextNode);
		}
	}
}

int Calculator::multiply(int num1, int num2) {
	return num1 * num2;
}

int Calculator::divide(int num1, int num2) {
	return num1 / num2;
}

int Calculator::add(int num1, int num2) {
	return num1 + num2;
}

int Calculator::subtract(int num1, int num2) {
	return num1 - num2;
}

/*
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
*/
#endif // !CALCULATOR_H