#include "stdafx.h"
#include "Odometer.h"


Odometer::Odometer()
{
}


Odometer::~Odometer()
{
}

void Odometer::addTotalDistance(double getDistance) {
	totalDistance += getDistance;
}

void Odometer::addTotalDuration(int getDuration) {
	totalDuration += getDuration;
}

void Odometer::resetOdometer() {
	totalDistance = 0;
	totalDuration = 0;
}

void Odometer::displayTotalDistance() {
	if (totalDistance == 0)
		return;
	cout << "\nTotal distance travelled: " << distanceKm(totalDistance);
}

void Odometer::displayTotalDuration() {
	if (totalDuration == 0)
		return;
	cout << "\nTotal time travelled: " << durationHumanReadable(totalDuration);
}