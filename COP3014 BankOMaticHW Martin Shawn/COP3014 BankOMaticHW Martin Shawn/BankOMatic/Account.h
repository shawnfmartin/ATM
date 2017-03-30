#pragma once
#include <string>
#include <vector>
using namespace std;



class Account
{
	friend class Bank;
	Account();
	string makeFormatedString();
	string makeDataString();

private:
	bool isDeleted;
	int balance;  // kept as the number of pennies in the account
	void getBalance(int x, int balance);
	int setBalance(int balance);

	int accountNumber;
	string initialAmount;
	string customerNumber;
	string accountType;  // "Checking" or "Savings"
	vector<int> customerNumbers;
};
