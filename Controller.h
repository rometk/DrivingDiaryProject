#pragma once
#include <curl.h>
#include <string>
#include <sstream>
#include <algorithm>
#include <memory>
#include <codecvt>
#include "ParseJson.h"
#include "Trip.h"
#include "Odometer.h"

using namespace std;

class Controller
{
public:
	Controller(Trip setTrip, Odometer setOdometer, ParseJson setParseJson);
	Controller();
	~Controller();

	/*Get information from Google Distance Matrix API*/
	void curlHandler();

	/*Callback function for CURLOPT_WRITEDATA to get pointer to the string data copied from Json*/
	static size_t WriteCallback(void *contents, size_t size, size_t nmemb, void *userp);

	void tripLookup(wstring getDestination, wstring getOrigin);
	void enterTrip(wstring getDestination, wstring getOrigin);
	void enterCarInfo(int avgConsumption, bool setFlag);
	void display();
	void displayTotal();
	void clear();
	void tripsToFile();
	void tripsFromFile();

	/*Convert UTF-8 data downloaded from website into UTF-16*/
	wstring utf8_to_utf16(const std::string& utf8);
	/*Strip unicode characters from url*/
	void stripUnicode(char* str);

private:
	bool tripFound;
	double distance;
	int duration;
	wstring origin, destination;
	Trip trip;
	Odometer odometer;
	ParseJson parseJson;
};

