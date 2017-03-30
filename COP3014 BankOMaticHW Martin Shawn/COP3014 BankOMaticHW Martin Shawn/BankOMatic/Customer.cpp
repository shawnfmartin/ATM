#include "Customer.h"
#include "misc.h"





Customer::Customer()
{
	isDeleted = false;
}

string Customer::makeFormatedString()
{
	string result;
	result += padLeft(intToString(customerNumber), '0', 9) + " ";
	result += padRight(name, ' ', 20) + " ";
	result += padRight(birthdate, ' ', 12) + " ";
	result += padRight(SSnumber, ' ', 12) + "\n";
	return result;
}

string Customer::makeDataString()
{
	string result;
	result += intToString(customerNumber) + " ";
	result += name + ";";
	result += birthdate + ";";
	result += SSnumber + ";";
	for each (int an in accountNumbers)
	{
		result += intToString(an) + " ";
	}
	return result;
}