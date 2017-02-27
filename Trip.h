#pragma once
#include <string>
#include <iostream>
#include <sstream>
#include <vector>

#pragma warning(disable:4996)

using namespace std;
class Trip
{
public:
	Trip();
	~Trip();
	void tripLookup(string destination, string origin, double distance, int duration);
	void saveTrip(string destination, string origin, double distance, int duration);
	void displayTrips();
	void clearTripCache();
	double distanceKm(double distance);
	string durationHumanReadable(int duration);

private:
	double distance;
	int duration;

	/*Trip cache (vector array)*/
	vector<string> trips;
};

