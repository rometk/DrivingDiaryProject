#include "stdafx.h"
#include "Odometer.h"


Odometer::Odometer()
{
	setConsumption = false;
}


Odometer::~Odometer()
{
}

void Odometer::addTotalDistance(double getDistance) {
	totalDistance += getDistance;
	if (setConsumption) 
		totalConsumption += (((getDistance/1000) / 100) * avgConsumption);
}

void Odometer::addTotalDuration(int getDuration) {
	totalDuration += getDuration;
}

void Odometer::resetOdometer() {
	totalDistance = 0;
	totalDuration = 0;
	totalConsumption = 0;
}

void Odometer::fuelConsumptionData(int getAvgConsumption, bool setFlag) {
	avgConsumption = getAvgConsumption;
	setConsumption = setFlag;
}

void Odometer::displayTotalDistance() {
	if (totalDistance == 0)
		return;
	wcout << "\nTotal distance travelled: " << distanceKm(totalDistance) << " km" << endl;

	if (setConsumption)
		wcout << "Total fuel consumption with " << avgConsumption << " l/100 km: " << totalConsumption << endl;
}

void Odometer::displayTotalDuration() {
	if (totalDuration == 0)
		return;
	wcout << "Total time travelled: " << durationHumanReadable(totalDuration) << endl;
}