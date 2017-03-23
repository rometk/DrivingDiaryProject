#pragma once
#include "Trip.h"
class Odometer : public Trip
{
public:
	Odometer();
	~Odometer();

	void addTotalDistance(double getDistance);
	void addTotalDuration(int getDuration);
	void resetOdometer();
	void displayTotalDistance();
	void displayTotalDuration();
	void fuelConsumptionData(int getAvgConsumption, bool setFlag);

private:
	double totalDistance;
	int totalDuration;

	bool setConsumption;
	int avgConsumption;
	double totalConsumption;
};

