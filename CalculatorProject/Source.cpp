#include "Calculator.h"
#include <string>

int main()
{
	Calculator calculate;
	bool flag = true;
	string continuation;
	do {
		calculate.buildList(calculate.getInput());
		calculate.calculateList();
		cout << "\nEnter 'yes' to continue or 'no' to exit.\n";
		getline(cin, continuation);
		if (continuation == "yes")
		{
			flag = true;
			calculate.deleteList();
		}
		else if (continuation == "no")
			flag = false;
		else
		{
			cout << "\nYour answer is invalid. Program will now terminate.";
			flag = false;
		}
	} while (flag);
	return 0;
}