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
	void saveTrip(string destination, string origin, double distance, string duration);
	void displayTrips();
	void clearTripCache();

private:
	/*Trip cache (vector array)*/
	vector<string> trips;
};

