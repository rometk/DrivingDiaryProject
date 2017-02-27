#include "stdafx.h"
#include "Trip.h"

Trip::Trip()
{	
}


Trip::~Trip()
{
}

void Trip::tripLookup(string destination, string origin, double getDistance, int getDuration) {
	distance = getDistance;
	duration = getDuration;

	/*Distance into kilometers and duration into human readable form*/
	double getDistanceKm = distanceKm (distance);
	string getDurationHumanReadable = durationHumanReadable (duration);

	cout << "\nOrigin: " << origin;
	cout << "\nDestination: " << destination;
	cout << "\nDistance: " << getDistanceKm << " km";
	cout << "\nDuration: " << getDurationHumanReadable;
}

void Trip::saveTrip(string destination, string origin, double getDistance, int getDuration) {
	distance = getDistance;
	duration = getDuration;

	/*Distance into kilometers and duration into human readable form*/
	double getDistanceKm = distanceKm(distance);
	string getDurationHumanReadable = durationHumanReadable(duration);

	ostringstream strStream;
	strStream << origin << " - " << destination << "\nDistance: " << getDistanceKm << " km\nDuration: " << getDurationHumanReadable;
	string trip = strStream.str();
	trips.push_back(trip);

	/*Print information about current trip*/
	cout << "\n" << trip;
}

void Trip::displayTrips() {
	for (int i = 0; i < trips.size(); i++) {
		cout << trips.at(i) << "\n\n";
	}
}

void Trip::clearTripCache() {
	trips.clear();
}

/*Meters into kilometers*/
double Trip::distanceKm(double getDistance) {
	return getDistance / 1000;
}

/*Duration in seconds into h:min:s form*/
string Trip::durationHumanReadable(int getDuration) {
	int hours = 0, minutes = 0, seconds = 0;
	int thisDuration = getDuration;

	bool i = false;
	while (!i) {
		if ((thisDuration - 3600 >= 0)) {
			hours++;
			thisDuration -= 3600;
		}
		else if ((thisDuration - 60) >= 0) {
			minutes++;
			thisDuration -= 60;
		}
		else {
			seconds++;
			thisDuration--;
		}

		if (thisDuration == 0)
			i = true;
	}

	ostringstream strStream;
	strStream << hours << " h " << minutes << " min " << seconds << " s ";
	string durationStr = strStream.str();

	return durationStr;
}
