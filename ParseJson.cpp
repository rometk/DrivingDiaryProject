#include "stdafx.h"
#include "ParseJson.h"


ParseJson::ParseJson(wstring getAPIkey)
{
	APIkey = getAPIkey;
}

ParseJson::ParseJson() {

}


ParseJson::~ParseJson()
{
}

int ParseJson::parseDistance(wstring Json) {
	wstring distanceBuffer;
	wstring valueBuffer;
	wstring start = L"distance";
	wstring value = L"value";

	if (Json.find(start) != wstring::npos) {
		distanceBuffer = Json.substr(Json.find(start) + start.length());
		//10 is the value of maximum integer digits to be parsed
		valueBuffer = distanceBuffer.substr(distanceBuffer.find(value) + value.length() + 4, 10);
	}

	int distance = stoi(valueBuffer);

	return distance;
}

int ParseJson::parseDuration(wstring Json) {
	wstring durationBuffer;
	wstring valueBuffer;
	wstring start = L"duration";
	wstring value = L"value";

	if (Json.find(start) != wstring::npos) {
		durationBuffer = Json.substr(Json.find(start) + start.length());
		//10 is the value of maximum integer digits to be parsed
		valueBuffer = durationBuffer.substr(durationBuffer.find(value) + value.length() + 4, 10);
	}

	int duration = stoi(valueBuffer);

	return duration;
}

wstring ParseJson::parseOrigin(wstring Json) {
	wstring originBuffer;
	wstring field = L"origin_addresses";

	if (Json.find(field) != wstring::npos) {
		originBuffer = Json.substr(Json.find(field) + field.length(), Json.find(L"rows") - (Json.find(field) + field.length() + 1));
		replace(originBuffer.begin(), originBuffer.end(), '[', ' ');
		replace(originBuffer.begin(), originBuffer.end(), ']', ' ');
		replace(originBuffer.begin(), originBuffer.end(), ':', ' ');
		replace(originBuffer.begin(), originBuffer.end(), '"', ' ');
		originBuffer.erase(remove_if(originBuffer.begin(), originBuffer.end(), ::isspace), originBuffer.end());
		originBuffer.erase(originBuffer.end() - 1, originBuffer.end());
	}
	return originBuffer;
}

wstring ParseJson::parseDestination(wstring Json) {
	wstring destinationBuffer;
	wstring field = L"destination_addresses";

	if (Json.find(field) != wstring::npos) {
		destinationBuffer = Json.substr(Json.find(field) + field.length(), Json.find(L"origin_addresses") - (Json.find(field) + field.length() + 1));
		replace(destinationBuffer.begin(), destinationBuffer.end(), '[', ' ');
		replace(destinationBuffer.begin(), destinationBuffer.end(), ']', ' ');
		replace(destinationBuffer.begin(), destinationBuffer.end(), ':', ' ');
		replace(destinationBuffer.begin(), destinationBuffer.end(), '"', ' ');
		destinationBuffer.erase(remove_if(destinationBuffer.begin(), destinationBuffer.end(), ::isspace), destinationBuffer.end());
		destinationBuffer.erase(destinationBuffer.end() - 1, destinationBuffer.end());
	}
	return destinationBuffer;
}

wstring ParseJson::getAPIkey(){
	return APIkey;
}
