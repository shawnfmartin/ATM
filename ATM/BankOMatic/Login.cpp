#include "Login.h"



Login::Login()
{
}


Login::~Login()
{
}

bool Login::valdiate(int customerNumber, int pin)
{
	return false;
}

int Login::loginLoop()
{
	bool loginSuccessful = false;
	int customerNumber, pin;
	do
	{
		cout << "Enter your customer number: ";
		cin >> customerNumber;
		cout << endl;
		cout << "Enter a pin: ";
		cin >> pin;

		if (customerNumber == 1234 && pin == 1234)
			loginSuccessful = true;
	} while (!loginSuccessful);

	return customerNumber;
}