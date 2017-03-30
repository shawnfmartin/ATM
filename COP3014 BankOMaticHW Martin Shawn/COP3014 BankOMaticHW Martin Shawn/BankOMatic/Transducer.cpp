#include "Transducer.h"
#include <vector>
#include "misc.h"
using namespace std;


string Transducer::transduce(string command)
{
	try
	{
		string result;
		vector<string> token = tokenize(command);
		if ((token[0] == "HELP") || (token[0] == "H"))
		{
			if (token.size() != 1) throw (string)"ERROR: Wrong number of parameters for this command.";
			result = "Commands:\n";
			result += "-------------------\n";
			result += "\tHELP(H)\n";
			result += "\tCLEAR\n";
			result += "\tQUIT(Q)\n";
			result += "-------------------\n";
			result += "\tADD_CUSTOMER(AC) <NAME>;<DOB>;<SS#>\n";
			result += "\tREMOVE_CUSTOMER(RC) <Customer#>\n";
			result += "\tFIND_CUSTOMER(FC) <Customer#>\n";
			result += "\tSHOW_CUSTOMER_LIST(SCL)\n";
			result += "\tTEST_ADD_CUSTOMERS(TAC) <numberOfTestCustomers>\n";
			result += "-------------------\n";
			result += "\tADD_ACCOUNT(AA) <Customer#>;<InitialAmmount>;<AccountType>\n";
			result += "\tREMOVE_ACCOUNT(RA) <Account#>\n";
			result += "\tFIND_ACCOUNT(FA) <Account#>\n";
			result += "\tSHOW_ACCOUNT_LIST(SAL)\n";
			result += "\tTEST_ADD_ACCOUNTS(TAA) <numberOfTestAccounts>\n";
			result += "-------------------\n";
		}
		else if ((token[0] == "QUIT") || (token[0] == "Q"))
		{
			if (token.size() != 1) throw (string)"ERROR: Wrong number of parameters for this command.";
			result = "Goodbye.";
		}
		else if (token[0] == "CLEAR")
		{
			if (token.size() != 1) throw (string)"ERROR: Wrong number of parameters for this command.";
			result = bank.clear();
		}
		else if ((token[0] == "ADD_CUSTOMER") || (token[0] == "AC"))
		{
			if (token.size() != 4) throw (string)"ERROR: Wrong number of parameters for this command.";
			result = "The new Customer number is " + intToString(bank.addCustomer(token[1], token[2], token[3]));
		}
		else if ((token[0] == "REMOVE_CUSTOMER") || (token[0] == "RC"))
		{
			if (token.size() != 2) throw (string)"ERROR: Wrong number of parameters for this command.";
			result = bank.removeCustomer(stringToInt(token[1]));
		}
		else if ((token[0] == "FIND_CUSTOMER") || (token[0] == "FC"))
		{
			if (token.size() != 2) throw (string)"ERROR: Wrong number of parameters for this command.";
			result = bank.findCustomer(stringToInt(token[1]));
		}
		else if ((token[0] == "SHOW_CUSTOMER_LIST") || (token[0] == "SCL"))
		{
			if (token.size() != 1) throw (string)"ERROR: Wrong number of parameters for this command.";
			result = bank.getCustomerList();
		}
		else if ((token[0] == "TEST_ADD_CUSTOMERS") || (token[0] == "TAC"))
		{
			if (token.size() != 2) throw (string)"ERROR: Wrong number of parameters for this command.";
			result = bank.testAddCustomers(stringToInt(token[1]));
		}
		else if ((token[0] == "ADD_ACCOUNT") || (token[0] == "AA"))
		{
			if (token.size() != 4) throw (string)"ERROR: Wrong number of parameters for this command.";
			result = "The new Account number is " + intToString(bank.addAccount(token[1], token[2], token[3]));
		}
		else if ((token[0] == "REMOVE_ACCOUNT") || (token[0] == "RA"))
		{
			if (token.size() != 2) throw (string)"ERROR: Wrong number of parameters for this command.";
			result = bank.removeAccount(stringToInt(token[1]));
		}
		else if ((token[0] == "FIND_ACCOUNT") || (token[0] == "FA"))
		{
			if (token.size() != 2) throw (string)"ERROR: Wrong number of parameters for this command.";
			result = bank.findAccount(stringToInt(token[1]));
		}
		else if ((token[0] == "SHOW_ACCOUNTLIST") || (token[0] == "SAL"))
		{
			if (token.size() != 1) throw (string)"ERROR: Wrong number of parameters for this command.";
			result = bank.getAccountList();
		}
		else if ((token[0] == "TEST_ADD_ACCOUNTS") || (token[0] == "TAA"))
		{
			if (token.size() != 2) throw (string)"ERROR: Wrong number of parameters for this command.";
			result = bank.testAddAccounts(stringToInt(token[1]));
		}
		else
		{
			 throw (string)"ERROR: Unrecognized Command.";
		}
		return result;
	}
	catch (string s)
	{
		if (s == "FATAL ERROR") exit(999);
		return s;
	}
	catch (...)
	{
		return "Something went wrong but I don't know what!";
	}
}



