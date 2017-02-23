#pragma once
#include <curl.h>
#include <string>
#include <sstream>
#include "ParseHTML.h"
#include "Trip.h"
#include "Odometer.h"

using namespace std;

class Controller
{
public:
	Controller(Trip setTrip, Odometer setOdometer);
	Controller();
	~Controller();

	/*Get information from Google Distance Matrix API*/
	void curlHandler();

	/*Callback function for CURLOPT_WRITEDATA to get pointer to the string data copied from HTML*/
	static size_t WriteCallback(void *contents, size_t size, size_t nmemb, void *userp);

	void tripLookup(string getDestination, string getOrigin);
	void enterTrip(string getDestination, string getOrigin);

	/*Meters into kilometers*/
	double distanceKm(int getDistance);

	/*Duration in seconds into h:min:s form*/
	string durationHumanReadable(int getDuration);

private:
	double distance;
	string origin, destination, duration;
	Trip trip;
	Odometer odometer;
	ParseHTML parseHtml;
};

