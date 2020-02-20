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

//This function reads line input by user
string Calculator::getInput() {
	string expression;
	cout << "\nPlease enter expression(s) to be evaluated with spaces in between. Enter 0 to exit." << endl;
	getline(cin, expression);
	return expression;
}

//This function initializes and parses the string in order to build linked list to hold integers and operations. Also performs error checking for invalid characters
void Calculator::buildList(string expression) {
	int counter = 0;
	string holder;
	istringstream parser(expression);
	Node* currentNode;
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
					head = newNode;
				}
				else
				{
					currentNode = head;
					while (currentNode->nextPtr)
						currentNode = currentNode->nextPtr;
					currentNode->nextPtr = newNode;
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
			currentNode = head;
			while (currentNode->nextPtr)
				currentNode = currentNode->nextPtr;
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

//This function goes through and selects operations to perform
void Calculator::calculateList() {
	Node* nodePtr;
	Node* nextNode;
	nodePtr = head;
	if (!head)
	{
		cout << "\nThe list is empty.\n";
	}
	else
	{
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
			else
				nodePtr = nodePtr->nextPtr;
		}
		nodePtr = head;
		while(nodePtr->nextPtr)
		{
			nextNode = nodePtr->nextPtr;
			if (nodePtr->operation == "+")
			{
				nodePtr->operand = add(nodePtr->operand, nextNode->operand);
				nodePtr->operation = nextNode->operation;
				nodePtr->nextPtr = nextNode->nextPtr;
				delete(nextNode);
			}
			else if (nodePtr->operation == "-")
			{
				nodePtr->operand = subtract(nodePtr->operand, nextNode->operand);
				nodePtr->operation = nextNode->operation;
				nodePtr->nextPtr = nextNode->nextPtr;
				delete(nextNode);
			}
		}
	}
	cout << "\nThe result is: " << nodePtr->operand << endl << endl;

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