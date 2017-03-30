#include "Account.h"
#include "misc.h"





Account::Account()
{
	isDeleted = false;
}

string Account::makeFormatedString()
{
	string result;
	result += padLeft(intToString(accountNumber), '0', 9) + " ";
	result += padRight(customerNumber, ' ', 20) + " ";
	result += padRight(intToDollarString(balance), ' ', 12) + " ";
	result += padRight(accountType, ' ', 12) + "\n";
	return result;
}

string Account::makeDataString()
{
	string result;
	result += intToString(accountNumber) + " ";
	result += customerNumber + ";";
	result += intToDollarString(balance) + ";";
	result += accountType, ' ', 12 + "\n";
	for each (int cn in customerNumbers)
	{
		result += intToString(cn) + " ";
	}
	return result;
}

//string Account::makeFormatedString()
//{
//	string result;
//	result += padLeft(intToString(accountNumber), '0', 9) + " ";
//	result += padRight(name, ' ', 20) + " ";
//	result += padRight(birthdate, ' ', 12) + " ";
//	result += padRight(SSnumber, ' ', 12) + "\n";
//	return result;
//}
//
//string Account::makeDataString()
//{
//	string result;
//	result += intToString(accountNumber) + " ";
//	result += name + ";";
//	result += birthdate + ";";
//	result += SSnumber + ";";
//	for each (int an in customerNumbers)
//	{
//		result += intToString(an) + " ";
//	}
//	return result;
//}
