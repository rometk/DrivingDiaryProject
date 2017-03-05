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
		<< "Go to a trip (save trip): trip\nDisplay all trips: display\nDisplay total distance and duration travelled: total\n"
		<< "Clear trip cache: clear";
}

void UserInterface::start() {
	help();
	string command = "";
	while (command != "quit") {
		cout << "\n\nType command: \n";
		cin >> command;
		cout << "\n";
		
		if (command == "lookup") {
			controller.tripLookup(to(), from());
		}
		else if (command == "trip") {
			controller.enterTrip(to(), from());
		}
		else if (command == "display") {
			controller.display();
		}
		else if (command == "total") {
			controller.displayTotal();
		}
		else if (command == "clear") {
			controller.clear();
		}
		else if (command == "help") {
			help();
		}
	}
}

string UserInterface::from() {
	string from;
	cout << "Starting location: ";
	cin >> from;
	
	return from;
}

string UserInterface::to() {
	string to;
	cout << "Destination: ";
	cin >> to;

	return to;
}
