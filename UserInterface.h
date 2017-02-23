#pragma once
#include <iostream>
#include <string>
#include "Controller.h"

using namespace std;
class UserInterface
{
public:
	UserInterface();
	~UserInterface();

	void start();
	void help();
	string from();
	string to();

private:
	Controller controller;
};

