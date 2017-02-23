#include "stdafx.h"
#include "Trip.h"

Trip::Trip()
{	
}


Trip::~Trip()
{
}

void Trip::saveTrip(string destination, string origin, double distance, string duration) {
	ostringstream strStream;
	strStream << destination << " - " << origin << "\nDistance: " << distance << "\nDuration: " << duration;
	string trip = strStream.str();
	trips.push_back(trip);

	/*Print information about current trip*/
	cout << trip;
}

void Trip::displayTrips() {
	for (int i = 0; i < trips.size(); i++) {
		cout << trips.at(i) << "\n\n";
	}
}

void Trip::clearTripCache() {
	trips.clear();
}
