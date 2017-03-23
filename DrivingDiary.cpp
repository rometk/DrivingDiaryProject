// DrivingDiary.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>
#include <string>
#include "ParseJson.h"
#include "Trip.h"
#include "Odometer.h"
#include "Controller.h"
#include "UserInterface.h"
#include <Windows.h>

#pragma warning(disable:4996)
using namespace std;

int main()
{
	SetConsoleOutputCP(1252);
	SetConsoleCP(1252);
	Trip trip;
	Odometer odometer;

	/*Get your API key at: https://developers.google.com/maps/documentation/distance-matrix/get-api-key*/
	wstring APIkey = L"AIzaSyAro0eBo0iVtjk_7izOBZ5sYfu6Q-qQ-SA";
	ParseJson parseJson(APIkey);

	Controller controller(trip,odometer, parseJson);
	UserInterface ui(controller);

	ui.start();

	return 0;
}

