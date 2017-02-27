#pragma once
#include <curl.h>
#include <string>
#include <sstream>
#include <algorithm>
#include "ParseHTML.h"
#include "Trip.h"
#include "Odometer.h"

using namespace std;

class Controller
{
public:
	Controller(Trip setTrip, Odometer setOdometer, ParseHTML setParseHtml);
	Controller();
	~Controller();

	/*Get information from Google Distance Matrix API*/
	void curlHandler();

	/*Callback function for CURLOPT_WRITEDATA to get pointer to the string data copied from HTML*/
	static size_t WriteCallback(void *contents, size_t size, size_t nmemb, void *userp);

	void tripLookup(string getDestination, string getOrigin);
	void enterTrip(string getDestination, string getOrigin);
	void display();
	void displayTotal();
	void clear();

private:
	bool tripFound;
	double distance;
	int duration;
	string origin, destination;
	Trip trip;
	Odometer odometer;
	ParseHTML parseHtml;
};

