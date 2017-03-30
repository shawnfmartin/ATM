#pragma once
#include <string>
#include <vector>
using namespace std;


class Customer
{
	friend class Bank;
	Customer();
	string makeFormatedString();
	string makeDataString();

private:
	bool isDeleted;
	string name;
	string birthdate;
	string SSnumber;
	int customerNumber;
	vector<int> accountNumbers;
};
