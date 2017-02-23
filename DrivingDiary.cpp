// DrivingDiary.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>
#include <string>
#include "ParseHTML.h"
#include "Trip.h"
#include "Odometer.h"
#include "Controller.h"
#include "UserInterface.h"

#pragma warning(disable:4996)
using namespace std;

int main()
{
	Trip trip;
	Odometer odometer;
	Controller controller(trip,odometer);
	UserInterface ui;

	ui.start();

	return 0;
}

