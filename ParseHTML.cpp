#include "stdafx.h"
#include "ParseHTML.h"


ParseHTML::ParseHTML()
{
}


ParseHTML::~ParseHTML()
{
}

int ParseHTML::parseDistance(string HTML) {
	string distanceBuffer;
	string valueBuffer;
	string start = "distance";
	string value = "value";

	if (HTML.find(start) != string::npos) {
		distanceBuffer = HTML.substr(HTML.find(start) + start.length());
		//10 is the value of maximum integer digits to be parsed
		valueBuffer = distanceBuffer.substr(distanceBuffer.find(value) + value.length() + 4, 10);
	}

	int distance = stoi(valueBuffer);

	return distance;
}

int ParseHTML::parseDuration(string HTML) {
	string durationBuffer;
	string valueBuffer;
	string start = "duration";
	string value = "value";

	if (HTML.find(start) != string::npos) {
		durationBuffer = HTML.substr(HTML.find(start) + start.length());
		//10 is the value of maximum integer digits to be parsed
		valueBuffer = durationBuffer.substr(durationBuffer.find(value) + value.length() + 4, 10);
	}

	int duration = stoi(valueBuffer);

	return duration;
}

string ParseHTML::getAPIkey(){
	return APIkey;
}
