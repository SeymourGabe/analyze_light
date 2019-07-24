#include <iostream>
#include <sstream>
#include <vector>
#include <math.h>

#include "allData.hpp"

#define BUFFER 1024
#define NUMBINS 10
#define NUMBINS_ALL 25
using namespace std;

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
/*
        printf("~~~~~~~~~~~~ %s ~~~~~~~~~~~\n", this->type.c_str());
        float binSize = ((float)this->maxMeasure - (float)this->minMeasure) / NUMBINS_ALL; // Intensity range each bin should cover
        uint8_t bins[NUMBINS_ALL] = {0};    // Initialize with all zeros

	for (int it = 0; it < x.size(); it++ ) {
       		for (int i = 0; i < x[it]->white.running_total; i++) { // Loop through all iterations
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
*/
}


// Get the std for all data of a specific color
void allData::get_std() {


}
