#pragma once
#include <iostream>
#include <string>
#include "Controller.h"

using namespace std;
class UserInterface
{
public:
	UserInterface(Controller controller);
	~UserInterface();

	void start();
	void help();
	wstring from();
	wstring to();
	int avgConsumption();

private:
	Controller controller;
};

