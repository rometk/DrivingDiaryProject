#pragma once
#include <string>
#include <iostream>
#include <algorithm>

using namespace std;

class ParseHTML
{
public:
	ParseHTML(string getAPIkey);
	ParseHTML();
	~ParseHTML();

	int parseDistance(string HTML);
	int parseDuration(string HTML);
	string parseOrigin(string origin);
	string parseDestination(string destination);
	string getAPIkey();

	/*Strip random letters from URL address with Scandinavic letters falsely encoded (letters that have negative ASCII value)*/
	void stripUnicode(string & str);

private:
	/*Get your API key at: https://developers.google.com/maps/documentation/distance-matrix/get-api-key*/
	string APIkey;
};