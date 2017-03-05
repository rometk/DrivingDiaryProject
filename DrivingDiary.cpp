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

	/*Get your API key at: https://developers.google.com/maps/documentation/distance-matrix/get-api-key*/
	string APIkey = "Insert your API key here";
	ParseHTML parseHtml(APIkey);

	Controller controller(trip,odometer,parseHtml);
	UserInterface ui;

	ui.start();

	return 0;
}

