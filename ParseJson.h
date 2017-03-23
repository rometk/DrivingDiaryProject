#pragma once
#include <string>
#include <iostream>
#include <algorithm>

using namespace std;

class ParseJson
{
public:
	ParseJson(wstring getAPIkey);
	ParseJson();
	~ParseJson();

	int parseDistance(wstring Json);
	int parseDuration(wstring Json);
	wstring parseOrigin(wstring origin);
	wstring parseDestination(wstring destination);
	wstring getAPIkey();

private:
	/*Get your API key at: https://developers.google.com/maps/documentation/distance-matrix/get-api-key*/
	wstring APIkey;
};