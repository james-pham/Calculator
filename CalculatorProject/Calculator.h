#ifndef CALCULATOR_H
#define CALCULATOR_H

#include <string>
#include <iostream>
#include <sstream>

using namespace std;

//Nodes for linked list.
struct Node {
	int operand;
	string operation;
	Node* nextPtr = nullptr;
};

class Calculator {
private:
	Node* head;
	bool validInput = true;
public:
	Calculator() {
		head = nullptr;
	}

	~Calculator();

	string getInput();
	void buildList(string);
	void calculateList();
	int multiply(int, int);
	int divide(int, int);
	int add(int, int);
	int subtract(int, int);
	void deleteList();
	//void appendNode(Node*);
};

//This function reads line input by user
string Calculator::getInput() {
	string expression;
	cout << "\nPlease enter expression(s) to be evaluated with spaces in between." << endl;
	getline(cin, expression);
	return expression;
}

//This function initializes and parses the string in order to build linked list to hold integers and operations. Also performs error checking for invalid characters
void Calculator::buildList(string expression) {
	validInput = true;
	int counter = 0;
	string holder;
	istringstream parser(expression);
	Node* currentNode;
	bool integerCheck;
	//Separate expression by using spaces.
	while (parser >> holder) {
		//This allows to swap between placing operands and operators.
		if (counter % 2 == 0)
		{
			Node* newNode = new Node;
			//Checking operand for integers and negative symbol, if applicable.
			integerCheck = (holder.find_first_not_of("-0123456789") == string::npos);
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
				validInput = false;
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
	if (validInput)
	{
		Node* nodePtr;
		Node* nextNode;
		bool validDivision = true;
		nodePtr = head;
		if (!head)
		{
			cout << "\nThe list is empty.\n";
		}
		else
		{
			//Multiplication and division first.
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
					//Exception if divisor is 0 since it is not possible.
					if (nextNode->operand == 0)
					{
						cout << "\nDivision by 0 is not possible.\n";
						validDivision = false;
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

			//This allows program to continue traversing the list if there were no 0 divisors.
			while (nodePtr->nextPtr && validDivision)
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

		if (validDivision)
		{
			cout << "\nThe result is: " << nodePtr->operand << endl << endl;
		}
	}
	else
		cout << "\nYour input was invalid. No calculations were performed.\n" << endl << endl;
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


//Clear list in case user wishes to perform additional calculations.
void Calculator::deleteList() {
	Node* nodePtr;
	Node* nextNode;
	nodePtr = head;
	while (nodePtr)
	{
		nextNode = nodePtr->nextPtr;
		delete(nodePtr);
		nodePtr = nextNode;
	}
	head = nullptr;
}

Calculator::~Calculator() {
	Node* nodePtr;
	Node* nextNode;
	nodePtr = head;
	while (nodePtr)
	{
		nextNode = nodePtr->nextPtr;
		delete nodePtr;
		nodePtr = nextNode;
	}
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