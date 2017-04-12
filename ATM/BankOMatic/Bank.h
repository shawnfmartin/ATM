#include <string>
#include <vector>
#include <set>
#include <map>
#include "Customer.h"
#include "Account.h"
#include "TomRandom.h"
using namespace std;


class Bank
{
public:
	friend class Account;
	Bank();
	~Bank();

	void readCustomerFile();
	void writeCustomerFile();

	void readAccountFile();
	void writeAccountFile();

	int addCustomer(string n, string b, string s);
	void addCustomerFromFile(int cusNum, string n, string b, string s);
	string removeCustomer(int cusNum);
	string findCustomer(int cusNum);
	string clear();
	string testAddCustomers(int numberOfTestCus);
	bool isCusNumberUsed(int cusNum);
	string getCustomerList();

	int addAccount(int cn, int ba, string ty);
	void addAccountFromFile(int an, string ty, int ba);

	bool isActNumberUsed(int actNum);
	string getAccountList();
	string removeAccount(int actNumToBeDeleted);
	Customer & getCustomerByCustomerNumber(int cusNum);
	string findAccount(int actNum);
	string testAddAccounts(int numberOfTestAct);

	Account & getAccountByAccountNumber(int actNum);

	string makeDeposit(int actNum, int ammount);
	string makeWithdarwal(int actNum, int ammount);
	string MAKE_TRANSFER(int actNum,int actnum2, int ammount);
	string ADD_CUSTOMER_TO_ACCOUNT(int cusNum, int actNum);
	string GET_CUSTOMER_TOTAL_ASSETS(int cusNum);
	string REPORT_TOTAL_BANK_HOLDINGS();
	
	string getFormatedCustomerString(int cusNum);
	string getFormatedAccountString(int actNum);
	int GET_CUSTOMER_TOTAL_ASSETS2(int cusNum);
	string LIST_CUSTOMERS_WITH_HOLDINGS_ABOVE(int num);

	



private:
	TomRandom random;
	vector<Customer> vCustomer;
	map<int, int> indexByCustomerNumber;
	// We can use the map indexByCustomerNumber instead of the set
	//set<int> setOfUsedCusNumbers;

	vector<Account> vAccount;
	map<int, int> indexByAccountNumber;

};

