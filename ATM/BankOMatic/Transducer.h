
#pragma once

#include <string>
#include "Bank.h"

using namespace std;




class Transducer
{
public:
	Transducer(int customerNumber);
	string transduce(string command);
private:
	//Add main functional object here 
	Bank bank;
	int sessionCustomerNumber;
};