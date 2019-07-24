//#include <list>
//#include <iterator>
//#include <stdio.h>
//#include <string>
#include <iostream>
#include <sstream>
#include <vector>
#include "analyze_light.hpp"

#define BUFFER 1024 
#define NUMBINS 10

using namespace std;

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
void BOT::updateColor(string s, uint8_t color_flag) {
	uint16_t tempLight = stoi(s);
	if (color_flag == 0){
        	this->white.updateColor(s);
        } else if (color_flag == 1) {
                this->black.updateColor(s);
        } else if (color_flag == 2) {
                this->grey.updateColor(s);
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

}

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
				x[bots - 1]->updateColor(s, color_flag);	// And set the appropriate values
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
		printf("\n\nBot %d white average = %f\n", x[i]->bot_number, x[i]->white.avg);
                printf("Bot %d black average = %f\n", x[i]->bot_number, x[i]->black.avg);
                printf("Bot %d grey average = %f\n\n", x[i]->bot_number, x[i]->grey.avg);
		x[i]->plotHist();
	}

	fclose(readFile); // Close the file
	return 0;
}
