#include "stdafx.h"
#include "UserInterface.h"


UserInterface::UserInterface(Controller getController)
{
	controller = getController;
}


UserInterface::~UserInterface()
{
}

void UserInterface::help() {
	wcout << "Commands:\nLook up approximate distance and duration between cities: lookup\n"
		<< "Go to a trip (save trip data): add\nDisplay all trips (read trip data): read\nDisplay total distance and duration travelled: total\n"
		<< "Clear trip cache: initialize\n Set automobile consumption (optional): consumption\n"
		<< "Display total distance driven and total duration (total consumption optionally): total";
}

void UserInterface::start() {
	controller.tripsFromFile();
	help();
	wstring command = L"";
	while (command != L"quit") {
		wcout << L"\n\nType command: \n";
		wcin >> command;
		wcout << L"\n";
		
		if (command == L"lookup") {
			controller.tripLookup(to(), from());
		}
		else if (command == L"add") {
			controller.enterTrip(to(), from());
		}
		else if (command == L"read") {
			controller.display();
		}
		else if (command == L"total") {
			controller.displayTotal();
		}
		else if (command == L"initialize") {
			controller.clear();
		}
		else if (command == L"consumption") {
			controller.enterCarInfo(avgConsumption(), true);
		}
		else if (command == L"help") {
			help();
		}
		else if (command == L"quit") {
			controller.tripsToFile();
		}
		else {
			cout << "Invalid command.\nType 'help' to see commands.";
		}
	}
}

wstring UserInterface::from() {
	wstring from;
	wcout << "Starting location: ";
	wcin >> from;
	
	return from;
}

wstring UserInterface::to() {
	wstring to;
	wcout << "Destination: ";
	wcin >> to;

	return to;
}

int UserInterface::avgConsumption() {
	int avgConsumption;
	cout << "Avarage consumption of your automobile (litres/100 km): ";
	cin >> avgConsumption;

	return avgConsumption;
}
