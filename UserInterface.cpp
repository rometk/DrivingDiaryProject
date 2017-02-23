#include "stdafx.h"
#include "UserInterface.h"


UserInterface::UserInterface() : controller()
{
}


UserInterface::~UserInterface()
{
}

void UserInterface::help() {
	cout << "Commands:\nLook up approximate distance and duration between cities: lookup\n"
		<< "Go to a trip (save trip): trip\n Display all trips: display\nDisplay total distance and duration travelled: total";
}

void UserInterface::start() {
	help();
	string command = "";
	while (command != "quit") {
		cout << "\n\nType command: \n";
		cin >> command;
		
		if (command == "lookup") {
			cout << "\n";
			controller.tripLookup(to(), from());
		}
		else if (command == "trip") {
			cout << "\n";
			controller.enterTrip(to(), from());
		}
		else if (command == "display") {

		}
		else if (command == "total") {

		}
		else if (command == "clear") {

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
