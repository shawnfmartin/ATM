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
	Bank();
	~Bank();
	int addCustomer(string n, string b, string s);
	void addCustomer(int cusNum, string n, string b, string s);
	string removeCustomer(int cusNum);
	string findCustomer(int cusNum);
	string clear();
	string testAddCustomers(int numberOfTestCus);
	bool isCusNumberUsed(int cusNum);
	string getCustomerList();

	int addAccount(string cn, string ia, string at);
	void addAccount(int accNum, string cn, string ia, string at);
	bool isAccNumberUsed(int accNum);
	string testAddAccounts(int numberOfTestAcc);
	string getAccountList();
	int setBalance(int bal, string ia);
	string removeAccount(int accNumToBeDeleted);
	string findAccount(int accNum);
	string randomAccountType();




private:
	TomRandom random;
	vector<Customer> vCustomer;
	map<int, int> indexByCustomerNumber;
	// We can use the map indexByCustomerNumber instead of the set
	//set<int> setOfUsedCusNumbers;

	vector<Account> vAccount;
	map<int, int> indexByAccountNumber;

};

