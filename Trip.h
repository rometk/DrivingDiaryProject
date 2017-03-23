#pragma once
#include <string>
#include <iostream>
#include <sstream>
#include <vector>
#include <fstream>

#pragma warning(disable:4996)

using namespace std;
class Trip
{
public:
	Trip();
	~Trip();
	void tripLookup(wstring destination, wstring origin, double distance, int duration);
	void saveTrip(wstring destination, wstring origin, double distance, int duration);
	void displayTrips();
	void clearTripCache();
	double distanceKm(double distance);
	wstring durationHumanReadable(int duration);

	const vector<wstring> &getTrips() const;
	void writeFromDisc(wstring trip);

private:
	double distance;
	int duration;

	/*Trip cache (vector array)*/
	vector<wstring> trips;
};

