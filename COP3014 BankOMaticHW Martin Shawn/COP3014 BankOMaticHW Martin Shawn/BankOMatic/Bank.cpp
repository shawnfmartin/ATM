#include "Bank.h"

#include "misc.h"

#include <fstream>

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
	string iLine;
	ifstream iFile;
	iFile.open("bank0000.txt");
	while (!iFile.eof())
	{
		getline(iFile, iLine);
		vector<string> field = tokenize(iLine);
		if (field.size() >= 4)
		{
			addCustomer(stringToInt(field[0]), field[1], field[2], field[3]);
		}
	}
	iFile.close();
}

Bank::~Bank()
{
	ofstream oFile;
	oFile.open("bank0000.txt");
	for each(Customer c in vCustomer)
	{
		if(!c.isDeleted) oFile << c.makeDataString() << endl;
	}
	oFile.close();
}

string Bank::clear()
{
	vCustomer.clear();
	//setOfUsedCusNumbers.clear();
	indexByCustomerNumber.clear();
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

string Bank::testAddAccounts(int numberOfTestAcc)
{

	for (int i = 0; i < numberOfTestAcc; i++)
	{
		string accNum = randNumberString(9);
		string cusNum = randNumberString(9);
		string ia = randNumberString(6);
		string at = randomAccountType();
		addAccount(accNum, ia, at);
	}


	return intToString(numberOfTestAcc) + " random accounts added.";
}

string Bank::randomAccountType()
{
	string number = randNumberString(2); 
	string at;
	if (stringToInt(number) < 50)
	{
		at = "SAVINGS";
	}
	else
	{
		at = "CHECKING";
	}

	return at;

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

	//for each(Customer c in vCustomer)
	//{
	//	if (!c.isDeleted) result += c.makeFormatedString();
	//}

	// by going through the index map instead of the vCustomer we display them in order.
	for each(pair<int,int> p in indexByCustomerNumber)
	{		
		if (!vCustomer[p.second].isDeleted) result += vCustomer[p.second].makeFormatedString();
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
	result += padRight("Customer#", '.', 20) + " ";
	result += padRight("Balance", '.', 12) + " ";
	result += padRight("Account Type", '.', 12) + "\n";

	result += padRight("", '_', 9) + " ";
	result += padRight("", '_', 20) + " ";
	result += padRight("", '_', 12) + " ";
	result += padRight("", '_', 12) + "\n";

	//for each(Customer c in vCustomer)
	//{
	//	if (!c.isDeleted) result += c.makeFormatedString();
	//}

	// by going through the index map instead of the vCustomer we display them in order.
	for each(pair<int, int> p in indexByAccountNumber)
	{
		if (!vAccount[p.second].isDeleted) result += vAccount[p.second].makeFormatedString();
	}

	result += padRight("", '_', 9) + " ";
	result += padRight("", '_', 20) + " ";
	result += padRight("", '_', 12) + " ";
	result += padRight("", '_', 12) + "\n";

	return result;
}







int Bank::addCustomer(string n, string b, string s)
{
	Customer c;
	c.name = n;
	c.birthdate = b;
	c.SSnumber = s;

	//c.customerNumber = rand();

	int newCusNumber;

	do
	{
		newCusNumber = random.getInt(10000, 100010000);
	} while (isCusNumberUsed(newCusNumber));

	//setOfUsedCusNumbers.insert(newCusNumber);
	indexByCustomerNumber[newCusNumber] = (int)vCustomer.size();

	c.customerNumber = newCusNumber;
	vCustomer.push_back(c);
	return c.customerNumber;
}



int Bank::addAccount(string cn, string ia, string at)
{
	Account a;
	a.customerNumber = cn;
	a.initialAmount = ia;
	a.accountType = at;
	//a.balance = setBalance(a.balance, ia);
	a.balance = stringToInt(ia);
	//c.customerNumber = rand();

	int newAccNumber;

	do
	{
		newAccNumber = random.getInt(10000, 100010000);
	} while (isAccNumberUsed(newAccNumber));

	//setOfUsedCusNumbers.insert(newCusNumber);
	indexByAccountNumber[newAccNumber] = (int)vAccount.size();

	a.accountNumber = newAccNumber;
	vAccount.push_back(a);
	return a.accountNumber;
}

int Bank::setBalance(int bal, string ia)
{
	bal = stringToInt(ia);
	return bal;
}



void Bank::addAccount(int accNum, string cn, string ia, string at)
{
	Account a;
	a.customerNumber = cn;
	a.initialAmount = ia;
	a.accountType = at;
	a.accountNumber = accNum;
	a.balance = stringToInt(ia);
	//a.balance = setBalance(a.balance, ia);
	a.balance = stringToInt(ia);
	//setOfUsedCusNumbers.insert(cusNum);
	indexByAccountNumber[accNum] = (int)vAccount.size();
	vAccount.push_back(a);
}


void Bank::addCustomer(int cusNum, string n, string b, string s)
{
	Customer c;
	c.name = n;
	c.birthdate = b;
	c.SSnumber = s;
	c.customerNumber = cusNum;
	//setOfUsedCusNumbers.insert(cusNum);
	indexByCustomerNumber[cusNum] = (int)vCustomer.size();
	vCustomer.push_back(c);
}

//bool Bank::isCusNumberUsed(int cusNum)
//{
//	vector<Customer>::iterator iter;
//	iter = vCustomer.begin();
//	while (iter != vCustomer.end())
//	{
//		if ((*iter).customerNumber == cusNum)
//		{
//			return true;
//		}
//		iter++;
//	}
//	return false;
//}












bool Bank::isCusNumberUsed(int cusNum)
{
	map<int,int>::iterator findIter;
	findIter = indexByCustomerNumber.find(cusNum);
	if (findIter != indexByCustomerNumber.end()) return true;
	return false;
}

bool Bank::isAccNumberUsed(int cusNum)
{
	map<int, int>::iterator findIter;
	findIter = indexByAccountNumber.find(cusNum);
	if (findIter != indexByAccountNumber.end()) return true;
	return false;
}

//string Bank::removeCustomer(int cusNumToBeDeleted)
//{
//	string result;
//	vector<Customer>::iterator iter;
//	iter = vCustomer.begin();
//	while (iter != vCustomer.end())
//	{
//		if ((*iter).customerNumber == cusNumToBeDeleted)
//		{
//			result = (*iter).name + " was deleted";
//			vCustomer.erase(iter);
//			return result;
//		}
//		iter++;
//	}
//
//	result = "No vCustomer with number " + intToString(cusNumToBeDeleted) + " was found.";
//	return result;
//}
string Bank::removeCustomer(int cusNumToBeDeleted)
{
	map<int, int>::iterator iter;
	iter = indexByCustomerNumber.find(cusNumToBeDeleted);
	if (iter == indexByCustomerNumber.end()) return "No customer with number " + intToString(cusNumToBeDeleted) + " was found.";
	vCustomer[(*iter).second].isDeleted = true;
	return vCustomer[(*iter).second].name + " was deleted";
}


string Bank::removeAccount(int accNumToBeDeleted)
{
	map<int, int>::iterator iter;
	iter = indexByAccountNumber.find(accNumToBeDeleted);
	if (iter == indexByAccountNumber.end()) return "No customer with number " + intToString(accNumToBeDeleted) + " was found.";
	vAccount[(*iter).second].isDeleted = true;
	return "Account number " + intToString(accNumToBeDeleted) + " was deleted";
}


// sequential search is slow
//string Bank::findCustomer(int cusNum)
//{
//	string result;
//	vector<Customer>::iterator iter;
//	iter = vCustomer.begin();
//	while (iter != vCustomer.end())
//	{
//		if ((*iter).customerNumber == cusNum)
//		{
//			result = (*iter).makeFormatedString();
//			return result;
//		}
//		iter++;
//	}
//
//	result = "No vCustomer with number " + intToString(cusNum) + " was found.";
//	return result;
//}


// requires two lookups
//string Bank::findCustomer(int cusNum)
//{
//	if (!isCusNumberUsed(cusNum)) return "No customer with number " + intToString(cusNum) + " was found.";
//	return vCustomer[indexByCustomerNumber[cusNum]].makeFormatedString();
//}

string Bank::findCustomer(int cusNum)
{
	map<int, int>::iterator iter;
	iter = indexByCustomerNumber.find(cusNum);
	if (iter == indexByCustomerNumber.end()) return "No customer with number " + intToString(cusNum) + " was found.";
	return vCustomer[(*iter).second].makeFormatedString();
}

string Bank::findAccount(int accNum)
{
	map<int, int>::iterator iter;
	iter = indexByAccountNumber.find(accNum);
	if (iter == indexByAccountNumber.end()) return "No account with number " + intToString(accNum) + " was found.";
	return vAccount[(*iter).second].makeFormatedString();
}
