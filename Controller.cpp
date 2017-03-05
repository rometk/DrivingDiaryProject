#include "stdafx.h"
#include "Controller.h"


Controller::Controller(Trip setTrip, Odometer setOdometer, ParseHTML setParseHtml)
{
	trip = setTrip;
	odometer = setOdometer;
	parseHtml = setParseHtml;
}

Controller::Controller() {

}

Controller::~Controller()
{
}

void Controller::tripLookup(string getDestination, string getOrigin) {
	origin = getOrigin;
	destination = getDestination;
	curlHandler();

	/*If origin and destination addresses were found*/
	if(tripFound)
		trip.tripLookup(destination, origin, distance, duration);
}

void Controller::enterTrip(string getDestination, string getOrigin) {
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
		/*Check if these places exist (if field 'NOT_FOUND wasn't found in HTML page')*/
		if (readBuffer.find("NOT_FOUND")==string::npos && readBuffer.find("ZERO_RESULTS") == string::npos) {
			
			/*Set trip is found flag 'true'*/
			tripFound = true;

			/*Parse distance value and duration value from HTML string.*/
			distance = parseHtml.parseDistance(readBuffer);
			duration = parseHtml.parseDuration(readBuffer);

			/*Parse full origin and destination*/
			origin = parseHtml.parseOrigin(readBuffer);
			destination = parseHtml.parseDestination(readBuffer);

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