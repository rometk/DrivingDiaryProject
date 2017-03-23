#include "stdafx.h"
#include "Trip.h"

Trip::Trip()
{	
}


Trip::~Trip()
{
}

void Trip::tripLookup(wstring destination, wstring origin, double getDistance, int getDuration) {
	distance = getDistance;
	duration = getDuration;

	/*Distance into kilometers and duration into human readable form*/
	double getDistanceKm = distanceKm (distance);
	wstring getDurationHumanReadable = durationHumanReadable (duration);

	wcout << "\nOrigin: " << origin;
	wcout << "\nDestination: " << destination;
	wcout << "\nDistance: " << getDistanceKm << " km";
	wcout << "\nDuration: " << getDurationHumanReadable;
}

void Trip::saveTrip(wstring destination, wstring origin, double getDistance, int getDuration) {
	distance = getDistance;
	duration = getDuration;

	/*Distance into kilometers and duration into human readable form*/
	double getDistanceKm = distanceKm(distance);
	wstring getDurationHumanReadable = durationHumanReadable(duration);

	wostringstream strStream;
	strStream << origin << " - " << destination << "\nDistance: " << getDistanceKm << " km\nDuration: " << getDurationHumanReadable << "\n\n";
	wstring trip = strStream.str();
	trips.push_back(trip);

	/*Print information about current trip*/
	wcout << "\n" << trip;
}

void Trip::displayTrips() {
	for (int i = 0; i < trips.size(); i++) {
		wcout << trips.at(i) << endl;
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
wstring Trip::durationHumanReadable(int getDuration) {
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

	wostringstream strStream;
	strStream << hours << " h " << minutes << " min " << seconds << " s ";
	wstring durationStr = strStream.str();

	return durationStr;
}

const vector<wstring> &Trip::getTrips() const{
	return trips;
}

void Trip::writeFromDisc(wstring trip) {
	trips.push_back(trip);
}

