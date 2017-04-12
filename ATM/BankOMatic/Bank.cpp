#include "Bank.h"

#include "misc.h"

#include <fstream>

#include <iostream>

#include <numeric>

using namespace std;

//string Bank::getCustomerList()
//{
//	string result;
//	for (int i = 0; i < vCustomer.size(); i++)
//	{
//		result += vCustomer[i].name + "\n";
//	}
//	return result;
//}

Bank::Bank()
{
	random.setSeed(999);
	readCustomerFile();
	readAccountFile();
}

void Bank::readCustomerFile()
{
	string iLine;
	ifstream iFile;
	iFile.open("cust0000.txt");
	while (!iFile.eof())
	{
		getline(iFile, iLine);
		vector<string> field = tokenize(iLine);
		if (field.size() >= 4)
		{
			addCustomerFromFile(stringToInt(field[0]), field[1], field[2], field[3]);
			for (int i = 4; i < field.size(); i++)
			{
				(*(vCustomer.end() - 1)).accountNumbers.push_back(stringToInt(field[i]));
			}
		}
	}
	iFile.close();
}

void Bank::readAccountFile()
{
	string iLine;
	ifstream iFile;
	iFile.open("acnt0000.txt");
	while (!iFile.eof())
	{
		getline(iFile, iLine);
		vector<string> field = tokenize(iLine);
		if (field.size() >= 3)
		{
			addAccountFromFile(stringToInt(field[0]),field[1],dollarStringToInt(field[2]));
			for (int i = 3; i < field.size(); i++)
			{
				(*(vAccount.end() - 1)).customerNumbers.push_back(stringToInt(field[i]));
			}
		}
	}
	iFile.close();
}

Bank::~Bank()
{
	writeCustomerFile();
	writeAccountFile();
}

void Bank::writeCustomerFile()
{
	ofstream oFile;
	oFile.open("cust0000.txt");
	for each(Customer c in vCustomer)
	{
		if (!c.isDeleted) oFile << c.makeDataString() << endl;
	}
	oFile.close();
}

void Bank::writeAccountFile()
{
	ofstream oFile;
	oFile.open("acnt0000.txt");
	for each(Account a in vAccount)
	{
		if (!a.isDeleted) oFile << a.makeDataString() << endl;
	}
	oFile.close();
}

string Bank::clear()
{
	vCustomer.clear();
	indexByCustomerNumber.clear();
	vAccount.clear();
	indexByAccountNumber.clear();
	return "All customers cleared.";
}

string Bank::testAddCustomers(int numberOfTestCus)
{
	for (int i = 0; i < numberOfTestCus; i++)
	{
		string name = randString(5) + " " + randString(10);
		string bDay = randNumberString(6);
		string SSnum = randNumberString(9);
		addCustomer(name, bDay, SSnum);
	}
	return intToString(numberOfTestCus) + " random customers added.";
}

string Bank::testAddAccounts(int numberOfTestAct)
{
	if (vCustomer.size() == 0) throw (string)"Error: There must be some customers before TEST_ADD_ACCOUNTS is used.";
	for (int i = 0; i < numberOfTestAct; i++)
	{
		int randCusIndex = randInt(0, (int)vCustomer.size());
		int cusNumber = vCustomer[randCusIndex].customerNumber;
		int balance = randInt(0, 5000) * 100 + 50;
		string aType;
		switch (randInt(0, 2))
		{
		case 0:
			aType = "Checking";
			break;
		case 1:
			aType = "Savings";
			break;
		}
		addAccount(cusNumber, balance, aType);
	}
	return intToString(numberOfTestAct) + " random accounts added.";
}

string Bank::getCustomerList()
{
	string result;

	result += "\n";

	result += padRight("Customer#", '.', 9) + " ";
	result += padRight("Name", '.', 20) + " ";
	result += padRight("Birthdate", '.', 12) + " ";
	result += padRight("SS#", '.', 12) + "\n";

	result += padRight("", '_', 9) + " ";
	result += padRight("", '_', 20) + " ";
	result += padRight("", '_', 12) + " ";
	result += padRight("", '_', 12) + "\n";


	// by going through the index map instead of the vCustomer we display them in order.
	for each(pair<int, int> p in indexByCustomerNumber)
	{
		try
		{
			result += getFormatedCustomerString(p.first);
		}
		catch (string es)
		{
			// if they are deleted
			if (matchFirst("Error: Previously Deleted Customer#", es))
			{
				//do nothing
			}
			else
			{
				throw es;
			}
		}
	}

	result += padRight("", '_', 9) + " ";
	result += padRight("", '_', 20) + " ";
	result += padRight("", '_', 12) + " ";
	result += padRight("", '_', 12) + "\n";

	return result;
}

string Bank::getAccountList()
{
	string result;

	result += "\n";

	result += padRight("Account#", '.', 9) + " ";
	result += padRight("Type", '.', 10) + " ";
	result += padRight("Balance", '.', 12) + "\n";

	result += padRight("", '_', 9) + " ";
	result += padRight("", '_', 10) + " ";
	result += padRight("", '_', 12) + "\n";


	// by going through the index map instead of the vCustomer we display them in order.
	for each(pair<int, int> p in indexByAccountNumber)
	{
		try
		{
			result += getFormatedAccountString(p.first);
		}
		catch (string es)
		{
			// if they are deleted
			if (matchFirst("Error: Previously Deleted Account#", es))
			{
				//do nothing
			}
			else
			{
				throw es;
			}

		}
	}

	result += padRight("", '_', 9) + " ";
	result += padRight("", '_', 10) + " ";
	result += padRight("", '_', 12) + "\n";

	return result;
}



int Bank::addCustomer( 	string n,	string b, 	string s)
{
	Customer c;
	c.name = n;
	c.birthdate = b;
	c.SSnumber = s;



	int newCusNumber;

	do
	{
		newCusNumber = random.getInt(10000, 100010000);
	} while (isCusNumberUsed(newCusNumber));

	indexByCustomerNumber[newCusNumber] = (int)vCustomer.size();

	c.customerNumber = newCusNumber;
	vCustomer.push_back(c);
	return c.customerNumber;
}

void Bank::addCustomerFromFile(int cusNum,	string n,	string b,	string s)
{
	Customer c;
	c.name = n;
	c.birthdate = b;
	c.SSnumber = s;
	c.customerNumber = cusNum;
	indexByCustomerNumber[cusNum] = (int)vCustomer.size();
	vCustomer.push_back(c);
}

bool Bank::isCusNumberUsed(int cusNum)
{
	map<int, int>::iterator findIter;
	findIter = indexByCustomerNumber.find(cusNum);
	if (findIter != indexByCustomerNumber.end()) return true;
	return false;
}

bool Bank::isActNumberUsed(int actNum)
{
	map<int, int>::iterator findIter;
	findIter = indexByAccountNumber.find(actNum);
	if (findIter != indexByAccountNumber.end()) return true;
	return false;
}


string Bank::removeCustomer(int cusNumToBeDeleted)
{
	Customer & cus = getCustomerByCustomerNumber(cusNumToBeDeleted);
	cus.isDeleted = true;
	return cus.name + "[" + intToString(cusNumToBeDeleted) + "] was deleted.";
}

string Bank::removeAccount(int actNumToBeDeleted)
{
	Account & acc = getAccountByAccountNumber(actNumToBeDeleted);
	acc.isDeleted = true;
	for each(int cn in acc.customerNumbers)
	{
		Customer & cus = getCustomerByCustomerNumber(cn);
		cus.removeAccountNumber(actNumToBeDeleted);
	}
	return "Account [" + intToString(actNumToBeDeleted) + "] was deleted.";
}



string Bank::findCustomer(int cusNum)
{
	return getFormatedCustomerString(cusNum);
}

string Bank::findAccount(int actNum)
{
	return getFormatedAccountString(actNum);
}

int Bank::addAccount(int cn, int ba, string ty)
{
	if (!isCusNumberUsed(cn)) throw("Customer number " + intToString(cn) + " was not found.");
	Account a;


	a.customerNumbers.push_back(cn);
	a.balance = ba;
	a.accountType = ty;


	int newActNumber;

	do
	{
		newActNumber = random.getInt(10000, 100010000);
	} while (isActNumberUsed(newActNumber));

	indexByAccountNumber[newActNumber] = (int)vAccount.size();

	getCustomerByCustomerNumber(cn).accountNumbers.push_back(newActNumber);

	a.accountNumber = newActNumber;
	vAccount.push_back(a);
	return newActNumber;
}

void Bank::addAccountFromFile(int an, string ty, int ba)
{
	Account a;

	a.accountNumber = an;
	a.balance = ba;
	a.accountType = ty;
	indexByAccountNumber[an] = (int)vAccount.size();
	vAccount.push_back(a);
}

Customer & Bank::getCustomerByCustomerNumber(int cusNum)
{
	map<int, int>::iterator findIter;

	findIter = indexByCustomerNumber.find(cusNum);

	if (findIter == indexByCustomerNumber.end()) throw "Error: Unfound Customer# " + intToString(cusNum);

	if (vCustomer[(*findIter).second].isDeleted)throw  "Error: Previously Deleted Customer# " + intToString(cusNum);

	return vCustomer[(*findIter).second];
}

Account & Bank::getAccountByAccountNumber(int actNum)
{
	map<int, int>::iterator findIter;
	findIter = indexByAccountNumber.find(actNum);

	if (findIter == indexByAccountNumber.end()) throw "Error: Unfound Account# " + intToString(actNum);

	if (vAccount[(*findIter).second].isDeleted) throw "Error: Previously Deleted Account# " + intToString(actNum);

	return vAccount[(*findIter).second];
}

string Bank::makeDeposit(int actNum, int ammount)
{
	Account & act = getAccountByAccountNumber(actNum);
	act.balance += ammount;
	return intToDollarString(ammount) + " deposit was made to Account# " + intToString(actNum) + " New balance: " + intToDollarString(act.balance);
}

string Bank::makeWithdarwal(int actNum, int ammount)
{
	Account & act = getAccountByAccountNumber(actNum);
	if (act.balance > ammount){ 
	    act.balance -= ammount;
		return intToDollarString(ammount) + " a withdarwal was made to Account# " + intToString(actNum) + " New balance: " + intToDollarString(act.balance);}
	else{ return "not enough funds in the account";}
}

string Bank::MAKE_TRANSFER(int actNum,int actnum2, int ammount)
{
	Account & act = getAccountByAccountNumber(actNum);
	Account & act2 = getAccountByAccountNumber(actnum2);
	if (ammount <= act.balance)
		{act2.balance += ammount;
	     act.balance -= ammount;
	    return intToDollarString(ammount) + " a transfer was made to Account# " + intToString(actnum2) + " New balance: " + intToDollarString(act2.balance) + "\n" + intToDollarString(ammount) + " was taken from Account# " + intToString(actNum) + " New balance: " + intToDollarString(act.balance);}
        else{ return "not enough funds in the account";}
}

string Bank::ADD_CUSTOMER_TO_ACCOUNT(int cusNum, int actNum)
{
  Customer & cus = getCustomerByCustomerNumber(cusNum);
  Account & act = getAccountByAccountNumber(actNum);
  act.customerNumbers.push_back (cusNum); 
  cus.accountNumbers.push_back (actNum);
  return "";
}

string Bank::GET_CUSTOMER_TOTAL_ASSETS(int cusNum)
{
 int total=0,i=0,x,y=0;
 Customer & cus = getCustomerByCustomerNumber(cusNum);
 for (i=1; i <= cus.accountNumbers.size(); i++)
 { 

   x=cus.accountNumbers[i-1];
   Account & act = getAccountByAccountNumber(x);
   y=act.balance+y;

 }
 return intToDollarString(y);
}

int Bank::GET_CUSTOMER_TOTAL_ASSETS2(int cusNum)
{

 int total=0,i=0,x,y=0;

 Customer & cus = getCustomerByCustomerNumber(cusNum);

 for (i=1; i <= cus.accountNumbers.size(); i++)
 { 
   x=cus.accountNumbers[i-1];

   Account & act = getAccountByAccountNumber(x);
   y=act.balance+y;

 }
 return y;
}

string Bank::REPORT_TOTAL_BANK_HOLDINGS()
{
int x=0;
for each(pair<int, int> p in indexByCustomerNumber)
	{
		try
		{
			x = x + GET_CUSTOMER_TOTAL_ASSETS2(p.first);
		}
		catch (string es)
		{
			// if they are deleted
			if (matchFirst("Error: Previously Deleted Account#", es))
			{
				//do nothing
			}
			else
			{
				throw es;
			}
		}
		
    }
//for each(Customer c in vCustomer)
return intToDollarString(x) ;
}

string Bank::LIST_CUSTOMERS_WITH_HOLDINGS_ABOVE(int num)
{
	string result;
	int x = 0;
	for each(pair<int, int> p in indexByCustomerNumber)
	{
			x = GET_CUSTOMER_TOTAL_ASSETS2(p.first);
			if (x > num * 100)
			{ 
	           result += getFormatedCustomerString(p.first);   
			} 
	}
	return result;
}


	string Bank::getFormatedCustomerString(int cusNum)
{
	Customer cus = getCustomerByCustomerNumber(cusNum);

	string result;
	result = cus.makeFormatedSimpleString();
	for each(int aNum in cus.accountNumbers)
	{
		Account a = getAccountByAccountNumber(aNum);
		result += "\t" + a.makeFormatedSimpleString();
	}
	result += "\n";
	return result;
}

string Bank::getFormatedAccountString(int actNum)
{
	Account act = getAccountByAccountNumber(actNum);

	string result;
	result = act.makeFormatedSimpleString();
	for each(int cNum in act.customerNumbers)
	{
		Customer cus = getCustomerByCustomerNumber(cNum);
		result += "\t" + cus.makeFormatedSimpleString();
	}
	result += "\n";
	return result;
}


