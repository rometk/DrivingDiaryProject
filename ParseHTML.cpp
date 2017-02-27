#include "stdafx.h"
#include "ParseHTML.h"


ParseHTML::ParseHTML(string getAPIkey)
{
	APIkey = getAPIkey;
}

ParseHTML::ParseHTML() {

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

string ParseHTML::parseOrigin(string HTML) {
	string originBuffer;
	string field = "origin_addresses";

	if (HTML.find(field) != string::npos) {
		originBuffer = HTML.substr(HTML.find(field) + field.length(), HTML.find("rows") - (HTML.find(field) + field.length() + 1));
		replace(originBuffer.begin(), originBuffer.end(), '[', ' ');
		replace(originBuffer.begin(), originBuffer.end(), ']', ' ');
		replace(originBuffer.begin(), originBuffer.end(), ':', ' ');
		replace(originBuffer.begin(), originBuffer.end(), '"', ' ');
		stripUnicode(originBuffer);
		originBuffer.erase(remove_if(originBuffer.begin(), originBuffer.end(), ::isspace), originBuffer.end());
		originBuffer.erase(originBuffer.end() - 1, originBuffer.end());
	}
	return originBuffer;
}

string ParseHTML::parseDestination(string HTML) {
	string destinationBuffer;
	string field = "destination_addresses";

	if (HTML.find(field) != string::npos) {
		destinationBuffer = HTML.substr(HTML.find(field) + field.length(), HTML.find("origin_addresses") - (HTML.find(field) + field.length() + 1));
		replace(destinationBuffer.begin(), destinationBuffer.end(), '[', ' ');
		replace(destinationBuffer.begin(), destinationBuffer.end(), ']', ' ');
		replace(destinationBuffer.begin(), destinationBuffer.end(), ':', ' ');
		replace(destinationBuffer.begin(), destinationBuffer.end(), '"', ' ');
		stripUnicode(destinationBuffer);
		destinationBuffer.erase(remove_if(destinationBuffer.begin(), destinationBuffer.end(), ::isspace), destinationBuffer.end());
		destinationBuffer.erase(destinationBuffer.end() - 1, destinationBuffer.end());
	}
	return destinationBuffer;
}

string ParseHTML::getAPIkey(){
	return APIkey;
}

/*Strip random letters from URL address with Scandinavic letters falsely encoded (letters that have negative ASCII value)*/
void ParseHTML::stripUnicode(string & str)
{
	int j = 0;
	for (int i = 0; i < str.length(); i++) {
		j = (int)str.at(i);
		if (j < 0) {
			str.erase(remove(str.begin(), str.end(), str.at(i)), str.end());
			i--;
		}
	}
}
