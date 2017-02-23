#pragma once
#include <string>

using namespace std;

class ParseHTML
{
public:
	ParseHTML();
	~ParseHTML();

	int parseDistance(string HTML);
	int parseDuration(string HTML);
	string getAPIkey();

private:
	/*Get your API key at: https://developers.google.com/maps/documentation/distance-matrix/get-api-key*/
	const string APIkey = "AIzaSyAro0eBo0iVtjk_7izOBZ5sYfu6Q-qQ-SA";
};

