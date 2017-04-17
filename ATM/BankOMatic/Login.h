#pragma once
#include <string>
#include <iostream>
using namespace std;
class Login
{
public:
	Login();
	~Login();

	bool valdiate(int customerNumber, int pin);

	int loginLoop();

};

