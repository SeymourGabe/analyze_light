#include <iostream>
#include <sstream>
#include <vector>
#include <math.h>

#include "bot.hpp"
#include "allData.hpp"

#define BUFFER 1024
#define NUMBINS 10
#define NUMBINS_ALL 25
using namespace std;

// --------------------- For BOT::color and BOT-------------------- \\

// Get std for specified color
void BOT::color::get_std() {

	float array[this->running_total];
	float all;
	all = 0;

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
