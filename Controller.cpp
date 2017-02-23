#include "stdafx.h"
#include "Controller.h"


Controller::Controller() {

}

Controller::Controller(Trip setTrip, Odometer setOdometer) : parseHtml()
{
	trip = setTrip;
	odometer = setOdometer;
}


Controller::~Controller()
{
}

void Controller::tripLookup(string getDestination, string getOrigin) {
	origin = getOrigin;
	destination = getDestination;
	curlHandler();
	
	cout << "\nDistance: " << distance;
	cout << "\nDuration: " << duration;
}

void Controller::enterTrip(string getDestination, string getOrigin) {
	origin = getOrigin;
	destination = getDestination;
	curlHandler();

	trip.saveTrip(destination, origin, distance, duration);
}

/*Callback function for CURLOPT_WRITEDATA to get pointer to the string data copied from HTML*/
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
	sprintf(APIurl, "https://maps.googleapis.com/maps/api/distancematrix/json?units=metric&origins=%s&destinations=%s&key=%s", origin.c_str(), destination.c_str(), parseHtml.getAPIkey().c_str());

	string readBuffer;
	curl = curl_easy_init();
	if (curl) {
		curl_easy_setopt(curl, CURLOPT_URL, APIurl);

		/*Callback function for CURLOPT_WRITEDATA to get pointer to the string data copied from HTML*/
		curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteCallback);

		/*Copy data to readBuffer*/
		curl_easy_setopt(curl, CURLOPT_WRITEDATA, &readBuffer);

		/* example.com is redirected, so we tell libcurl to follow redirection */
		curl_easy_setopt(curl, CURLOPT_FOLLOWLOCATION, 1L);

		/* Perform the request, res will get the return code */
		res = curl_easy_perform(curl);

		/*Parse distance value and duration value from HTML string.*/
		int getDistance = parseHtml.parseDistance(readBuffer);
		int getDuration = parseHtml.parseDuration(readBuffer);

		/*Distance into kilometers and duration into human readable form*/
		distance = distanceKm(getDistance);
		duration = durationHumanReadable(getDuration);

		/* Check for errors */
		if (res != CURLE_OK)
			fprintf(stderr, "curl_easy_perform() failed: %s\n",
				curl_easy_strerror(res));

		/* always cleanup */
		curl_easy_cleanup(curl);
	}
	delete APIurl;
}

/*Meters into kilometers*/
double Controller::distanceKm(int getDistance) {
	return getDistance / 1000;
}

/*Duration in seconds into h:min:s form*/
string Controller::durationHumanReadable(int duration) {
	int hours=0, minutes=0, seconds=0;

	bool i = false;
	while (!i) {
		if ((duration - 3600 >= 0))
			hours++;
		else if ((duration - 60) >= 0)
			minutes++;
		else
			seconds++;
	}

	ostringstream strStream;
	strStream << hours << " h " << minutes << " min " << seconds << " s ";
	string durationStr = strStream.str();

	return durationStr;
}
