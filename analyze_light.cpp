//#include <list>
//#include <iterator>
//#include <stdio.h>
//#include <string>
/*
#include <iostream>
#include <sstream>
#include <vector>
#include <math.h>
#include "analyze_light.hpp"

#define BUFFER 1024
#define NUMBINS 10
#define NUMBINS_ALL 25
using namespace std;
*/
/*
// --------------------  For all data -------------------- \\

// allData constructor
allData::allData(string s) {
	this->type = s;
}

// Update the total for a specific color
void allData::updateTotal(int newEntry) {
	this->meas_total += newEntry;
	this->running_total += 1;

	if (newEntry < this->minMeasure)
		this->minMeasure = newEntry;

	if (newEntry > this->maxMeasure)
		this->maxMeasure = newEntry;
}

// Plot a histogram for the specified color
void allData::plotHist(vector<BOT*> x) {

        printf("~~~~~~~~~~~~ %s ~~~~~~~~~~~\n", this->type.c_str());
        float binSize = ((float)this->maxMeasure - (float)this->minMeasure) / NUMBINS_ALL; // Intensity range each bin should cover
        uint8_t bins[NUMBINS_all] = {0};    // Initialize with all zeros

	for (int it = 0; it < x.size(); it++ ) {
       		for (int i = 0; i < x[it]->running_total; i++) { // Loop through all iterations
        	        uint8_t binNum = (int)((x[it]->white.get_value() - this->minMeasure)/binSize);     // Which bin it fits in

 	               if (x[it]->white.get_value() == this->maxMeasure)  // maxMeasure will be put in bin NUMBINS... out of range so -1
                        	binNum = NUMBINS_ALL - 1;

                	bins[binNum] += 1; // Add one to that bin

        	}
	}






        for (int i = 0; i < NUMBINS_ALL; i++) { // Loop through all bins
                printf("BIN %d - %f to %f:     \t", i, this->minMeasure + i*binSize, this->minMeasure + (i+1)*binSize);
                for (int j = 0; j < bins[i]; j++) {     // Print stars for each bin
                        printf("*");
                }
                printf("\n");
        }
        printf("\n\n");
}
*/
/*
// Plot a histogram for each color
void plotHist() {

        allWhite->plotHist();
        allBlack->plotHist();
        allGrey->plotHist();

}






void get_std(allData *all[3]) {



}
*/
/*
// Get the std for all data of a specific color
void allData::get_std() {


}
*/
/*

// --------------------- For BOT::color and BOT-------------------- \\

// Get std for specified color
void BOT::color::get_std() {

	float array[this->running_total];
	float all = 0;

	for (int i = 0; i < this->running_total; i++) {
		array[i] = ((float)this->measurements[i] - this->avg)*((float)this->measurements[i] - this->avg);
		all += array[i];

	}

	all = all / this->running_total;
	this->stdDev = sqrt(all);
	this->confidence = this->stdDev / sqrt((float)this->running_total);
}

// Return measurement value
uint16_t BOT::color::get_value(uint8_t i) {
	return this->measurements[i];
}

// Get std dev for each color
void BOT::get_std() {

	this->white.get_std();
	this->black.get_std();
	this->grey.get_std();

	printf("Bot %d white std = %f\n", this->bot_number, this->white.stdDev);
        printf("Bot %d black std = %f\n", this->bot_number, this->black.stdDev);
        printf("Bot %d grey std = %f\n", this->bot_number, this->grey.stdDev);

	printf("\nBot %d white confidence = %f\n", this->bot_number, this->white.confidence);
        printf("Bot %d black confidence = %f\n", this->bot_number, this->black.confidence);
        printf("Bot %d grey confidence = %f\n\n", this->bot_number, this->grey.confidence);

}

// Plot a histogram for the specified color
void BOT::color::plotHist() {

        printf("~~~~~~~~~~~~ %s ~~~~~~~~~~~\n", this->type.c_str());
	float binSize = ((float)this->maxMeasure - (float)this->minMeasure) / NUMBINS; // Intensity range each bin should cover
	uint8_t	bins[NUMBINS] = {0};	// Initialize with all zeros

	for (int i = 0; i < this->running_total; i++) {	// Loop through all iterations
		uint8_t binNum = (int)((this->measurements[i] - this->minMeasure)/binSize);	// Which bin it fits in

		if (this->measurements[i] == this->maxMeasure)	// maxMeasure will be put in bin NUMBINS... out of range so -1
			binNum = NUMBINS - 1;

		bins[binNum] += 1; // Add one to that bin

	}

	for (int i = 0; i < NUMBINS; i++) { // Loop through all bins
		printf("BIN %d - %f to %f:     \t", i, this->minMeasure + i*binSize, this->minMeasure + (i+1)*binSize);
		for (int j = 0; j < bins[i]; j++) {	// Print stars for each bin
			printf("*");
		}
		printf("\n");
	}
	printf("\n\n");
}

// Plot a histogram for each color
void BOT::plotHist() {

	this->white.plotHist();
	this->black.plotHist();
	this->grey.plotHist();

}


// Update the specific color of a specific bot
void BOT::color::updateColor(string s) {
        uint16_t tempLight = stoi(s);
	this->measurements[this->running_total++] = tempLight;
	this->meas_total += tempLight;
	if (tempLight < this->minMeasure)
		this->minMeasure = tempLight;

	if (tempLight > this->maxMeasure)
		this->maxMeasure = tempLight;
}

// Update a specified color of this (a specific bot) based on color_flag
void BOT::updateColor(string s, uint8_t color_flag, allData *allColor[3]) {
	uint16_t tempLight = stoi(s);
	if (color_flag == 0){
        	this->white.updateColor(s);
		allColor[0]->updateTotal(tempLight);
        } else if (color_flag == 1) {
                this->black.updateColor(s);
		allColor[1]->updateTotal(tempLight);
        } else if (color_flag == 2) {
                this->grey.updateColor(s);
		allColor[2]->updateTotal(tempLight);
	}
}

// Set the average and print some stuff about a specific color
void BOT::color::set_avg() {
	printf("~~~~~~~~~~~~ %s ~~~~~~~~~~~\n", this->type.c_str());
	printf("Total measurement = %d\nRunning total = %d\n", this->meas_total, this->running_total);
	this->avg = (float)(this->meas_total) / (float)(this->running_total);
	printf("Min = %d. Max = %d. Range = %d\n", this->minMeasure, this->maxMeasure, this->maxMeasure - this->minMeasure);

}

// All three colors
void BOT::set_avg() {

	this->white.set_avg();
	this->black.set_avg();
	this->grey.set_avg();
	printf("\n\nBot %d white average = %f\n", this->bot_number, this->white.avg);
        printf("Bot %d black average = %f\n", this->bot_number, this->black.avg);
        printf("Bot %d grey average = %f\n\n", this->bot_number, this->grey.avg);

}
*/
/*
int main( int argc, char **argv ){

	// OPEN FILE
	FILE *readFile;
	readFile = fopen("light_tests.txt", "r");
	if (!readFile){
		printf("light_tests.txt didn't open\n");
		return 0;
	}

	// START READING FILE
	char buffer[BUFFER];
	istringstream iss(buffer);
   	string s;

	// FLAGS, ITERATORS, ETC
	uint32_t bots = 0;
	uint8_t bot_flag = 0;
	uint8_t color_flag;
	uint8_t prev_is_equal = 0;

	// ARRAY OF BOTS
	vector<BOT*> x;

	// ARRAY OF ALL DATA
	allData *allWhite = new allData("white");
        allData *allBlack = new allData("black");
        allData *allGrey = new allData("grey");
	allData *allColor[3] = { allWhite, allBlack, allGrey };


	// READ THE ENTIRE FILE
	while(fgets(buffer, sizeof(buffer), readFile) != NULL) {
		iss.clear();		// Clear previous buffer
		iss.str(buffer);	// Load new buffer
		while (iss >> s) {	// Pump this buffer into string, bit by bit
			if (bot_flag == 1) {	// If we last picked up a bot,
				uint8_t holdNum = stoi(s);
				x[bots++]->bot_number = holdNum;	// Set bot number
				bot_flag = 0;	// Reset bot flag
			}
			if (s == "BOT") {	// If we just detected a bot
				x.push_back(new BOT());	// Create a bot class
				bot_flag = 1;	// Set bot flag
			}
			// Set the appropriate color flag as needed
			if (s == "White") {
				color_flag = 0;
			}

			if (s == "Black") {
				color_flag = 1;
			}

			if (s == "Grey"){
				color_flag = 2;
			}

			if (prev_is_equal) {	// If the last string we read was an equal sign
				prev_is_equal = 0;	// Reset the flag
				x[bots - 1]->updateColor(s, color_flag, allColor);	// And set the appropriate values
			}
			if (s == "=")	// Set the "=" flag when needed
				prev_is_equal = 1;
		}

	}

	printf("There are %d bots\n\n", bots);
	// LOOP OVER ALL BOTS AND SET THEIR AVERAGE. PRINT THE AVERAGE
	for (int i = 0; i < x.size(); i++) {

		printf("\n~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~");
		if (x[i]->bot_number < 10)
			printf("\n~~~~~~~~~~~~~~~~~~~~~~ Bot number %d ~~~~~~~~~~~~~~~~~~~\n", x[i]->bot_number);
		else
                        printf("\n~~~~~~~~~~~~~~~~~~~~~~ Bot number %d~~~~~~~~~~~~~~~~~~~\n", x[i]->bot_number);

		printf("~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n");

		x[i]->set_avg();

		x[i]->get_std();

		x[i]->plotHist();
	}


	printf("White total = %d with %d entries.\n", allWhite->meas_total, allWhite->running_total);
	printf("White average = %f.\n", (float)allWhite->meas_total / (float)allWhite->running_total);


	fclose(readFile); // Close the file
	return 0;
}
*/
