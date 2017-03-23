#include "stdafx.h"
#include "Controller.h"


Controller::Controller(Trip setTrip, Odometer setOdometer, ParseJson setParseJson)
{
	trip = setTrip;
	odometer = setOdometer;
	parseJson = setParseJson;
}

Controller::Controller() {

}

Controller::~Controller()
{
}

void Controller::tripLookup(wstring getDestination, wstring getOrigin) {
	origin = getOrigin;
	destination = getDestination;
	curlHandler();

	/*If origin and destination addresses were found*/
	if(tripFound)
		trip.tripLookup(destination, origin, distance, duration);
}

void Controller::enterTrip(wstring getDestination, wstring getOrigin) {
	origin = getOrigin;
	destination = getDestination;
	curlHandler();

	/*If origin and destination addresses were found*/
	if (tripFound) {
		trip.saveTrip(destination, origin, distance, duration);
		odometer.addTotalDistance(distance);
		odometer.addTotalDuration(duration);
	}
}

void Controller::display() {
	trip.displayTrips();
}

void Controller::displayTotal() {
	odometer.displayTotalDistance();
	odometer.displayTotalDuration();
}

void Controller::clear() {
	trip.clearTripCache();
	odometer.resetOdometer();

	ofstream tripsList;
	tripsList.open("trips.txt", ofstream::out | ofstream::trunc);
}

void Controller::enterCarInfo(int avgConsumption, bool setFlag) {
	odometer.fuelConsumptionData(avgConsumption, setFlag);
}

void Controller::tripsToFile() {
	wofstream tripsToDisk;
	tripsToDisk.open("trips.txt");

	for (wstring trip : trip.getTrips()) {
		tripsToDisk << trip;
	}

	tripsToDisk.close();
}

void Controller::tripsFromFile() {
	wstring line;
	wifstream tripsFromDisk("trips.txt");

	if (tripsFromDisk.is_open()) {
		wstring temp;
		while (getline(tripsFromDisk, line)) {
			temp = temp + line + L'\n';
			int test = line.find(L"Distance");
			if (line == L"") {
				trip.writeFromDisc(temp);
				temp.clear();
			}
			//Conevert distance back to meters
			else if ((line.find(L"Distance")) != wstring::npos) {
				wstring distanceParse = line.substr(line.find(L" "), (line.find_first_of(L"k") - line.find_first_of(L":") - 1));
				odometer.addTotalDistance(stod(distanceParse)*1000);
			}
			//Convert human readable duration back to seconds for further calculations
			else if ((line.find(L"Duration")) != wstring::npos) {
				wstring parseHour, parseMin, parseSec;
				parseHour = line.substr(line.find(L" "), line.find(L"h") - line.find(L" "));
				parseMin = line.substr(line.find(L"h") + 1, line.find(L"min") - line.find(L"h") - 1);
				parseSec = line.substr(line.find(L"min") + 3, line.find(L"s") - line.find(L"min") - 3);

				int backToSec = stoi(parseHour) * 3600 + stoi(parseMin) * 60 + stoi(parseSec);
				odometer.addTotalDuration(backToSec);
			}
		}
	}
}

/*Callback function for CURLOPT_WRITEDATA to get pointer to the string data copied from Json*/
size_t Controller::WriteCallback(void *contents, size_t size, size_t nmemb, void *userp)
{
	((std::string*)userp)->append((char*)contents, size * nmemb);
	return size * nmemb;
}

/*Get information from Google Distance Matrix API*/
void Controller::curlHandler() {
	CURL *curl;
	CURLcode res;

	char* APIurl = new char[200];
	/*sprintf to append origin, destination and API key to URL*/
	
	sprintf(APIurl, "https://maps.googleapis.com/maps/api/distancematrix/json?units=metric&origins=%ls&destinations=%ls&key=%ls", origin.c_str(), destination.c_str(), parseJson.getAPIkey().c_str());
	
	/*Strip unicode characters from url*/
	stripUnicode(APIurl);

	string readBuffer;
	curl = curl_easy_init();
	if (curl) {
		curl_easy_setopt(curl, CURLOPT_URL, APIurl);

		/*Callback function for CURLOPT_WRITEDATA to get pointer to the string data copied from Json*/
		curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteCallback);

		/*Copy data to readBuffer*/
		curl_easy_setopt(curl, CURLOPT_WRITEDATA, &readBuffer);

		/* example.com is redirected, so we tell libcurl to follow redirection */
		curl_easy_setopt(curl, CURLOPT_FOLLOWLOCATION, 1L);

		/* Perform the request, res will get the return code */
		res = curl_easy_perform(curl);

		wstring bufferUTF16 = utf8_to_utf16(readBuffer);
		/*Check if these places exist (if field 'NOT_FOUND wasn't found in Json page')*/
		if (bufferUTF16.find(L"NOT_FOUND")==wstring::npos && bufferUTF16.find(L"ZERO_RESULTS") == wstring::npos) {
			
			/*Set trip is found flag 'true'*/
			tripFound = true;

			/*Parse distance value and duration value from Json string.*/
			distance = parseJson.parseDistance(bufferUTF16);
			duration = parseJson.parseDuration(bufferUTF16);

			/*Parse full origin and destination*/
			origin = parseJson.parseOrigin(bufferUTF16);
			destination = parseJson.parseDestination(bufferUTF16);

			/* Check for errors */
			if (res != CURLE_OK)
				fprintf(stderr, "curl_easy_perform() failed: %s\n",
					curl_easy_strerror(res));

			/* always cleanup */
			curl_easy_cleanup(curl);
		}
		else {
			/*If origin or destination not found, set flag to false*/
			tripFound = false;
			cout << "\nTrip not found.";
		}
	}
	delete APIurl;
}

/*Convert UTF-8 data downloaded from website into UTF-16*/
wstring Controller::utf8_to_utf16(const std::string& utf8)
{
	std::vector<unsigned long> unicode;
	size_t i = 0;
	while (i < utf8.size())
	{
		unsigned long uni;
		size_t todo;
		bool error = false;
		unsigned char ch = utf8[i++];
		if (ch <= 0x7F)
		{
			uni = ch;
			todo = 0;
		}
		else if (ch <= 0xBF)
		{
			throw std::logic_error("not a UTF-8 string");
		}
		else if (ch <= 0xDF)
		{
			uni = ch & 0x1F;
			todo = 1;
		}
		else if (ch <= 0xEF)
		{
			uni = ch & 0x0F;
			todo = 2;
		}
		else if (ch <= 0xF7)
		{
			uni = ch & 0x07;
			todo = 3;
		}
		else
		{
			throw std::logic_error("not a UTF-8 string");
		}
		for (size_t j = 0; j < todo; ++j)
		{
			if (i == utf8.size())
				throw std::logic_error("not a UTF-8 string");
			unsigned char ch = utf8[i++];
			if (ch < 0x80 || ch > 0xBF)
				throw std::logic_error("not a UTF-8 string");
			uni <<= 6;
			uni += ch & 0x3F;
		}
		if (uni >= 0xD800 && uni <= 0xDFFF)
			throw std::logic_error("not a UTF-8 string");
		if (uni > 0x10FFFF)
			throw std::logic_error("not a UTF-8 string");
		unicode.push_back(uni);
	}
	std::wstring utf16;
	for (size_t i = 0; i < unicode.size(); ++i)
	{
		unsigned long uni = unicode[i];
		if (uni <= 0xFFFF)
		{
			utf16 += (wchar_t)uni;
		}
		else
		{
			uni -= 0x10000;
			utf16 += (wchar_t)((uni >> 10) + 0xD800);
			utf16 += (wchar_t)((uni & 0x3FF) + 0xDC00);
		}
	}
	return utf16;
}

/*Strip unicode characters from url*/
void Controller::stripUnicode(char* str)
{
	for (int i = 0; i < strlen(str); i++) {
		if ((int)str[i] < 0)
			str[i] = 44;
	}
}