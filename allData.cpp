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
/*
// Reset Max and Min as needed.
void allData::resetMaxMin(BOT::color current) {
	this->minMeasure = 2048;

}
*/

// Get the std of all colors
void allData::get_std(vector<BOT*> x) {

	float array[this->running_total];
	float all;
	all = 0;

	// Go through each group and find (measurement - avg)^2
	BOT::color threeColors;
	for (int it = 0; it < x.size(); it++ ) {
		if (this->type == "white") {
			threeColors = x[it]->white;
		} else if (this->type == "black") {
			threeColors = x[it]->black;
		} else if (this->type == "grey") {
			threeColors = x[it]->grey;
		}
		for (int i = 0; i < threeColors.running_total; i++) { // Loop through all iterations

			all += ((float)threeColors.measurements[i] - this->avg)*((float)threeColors.measurements[i] - this->avg);

		}
	}


	//  (measurement - avg)^2 / N
	all = all / this->running_total;
	//  sqrt( (measurement - avg)^2 / N )

	this->stdDev = sqrt(all);

	// confidence = stdDev / sqrt(N)
	this->confidence = this->stdDev / sqrt((float)this->running_total);

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

// Set the max and mins.... after Chauvenet applied
void allData::max_min(vector<BOT*> x) {

	this->minMeasure = 2048;
	this->maxMeasure = 0;
	this->meas_total = 0;
	this->running_total = 0;

	BOT::color threeColors;//[3] = {x[it]->white, x[it]->black, x[it]->grey};
	for (int it = 0; it < x.size(); it++ ) {
			if (this->type == "white") {
				threeColors = x[it]->white;
			} else if (this->type == "black") {
				threeColors = x[it]->black;
			} else if (this->type == "grey") {
				threeColors = x[it]->grey;
			}

       		for (int i = 0; i < threeColors.running_total; i++) { // Loop through all iterations

				if (threeColors.measurements[i] > this->maxMeasure)
					this->maxMeasure = threeColors.measurements[i];
				if (threeColors.measurements[i] < this->minMeasure)
					this->minMeasure = threeColors.measurements[i];

				this->meas_total += threeColors.measurements[i];
				++this->running_total;

        	}
	}


}


// Plot a histogram for the specified color
void allData::plotHist(vector<BOT*> x) {

	this->max_min(x); // Reset the max and min of allData of specific color

	printf("~~~~~~~~~~~~ %s ~~~~~~~~~~~\n", this->type.c_str());
    float binSize = ((float)this->maxMeasure - (float)this->minMeasure) / NUMBINS_ALL; // Intensity range each bin should cover
	this->avg = (float)this->meas_total / (float)this->running_total;

	BOT::color threeColors;//[3] = {x[it]->white, x[it]->black, x[it]->grey};
	for (int it = 0; it < x.size(); it++ ) {
			if (this->type == "white") {
				threeColors = x[it]->white;
			} else if (this->type == "black") {
				threeColors = x[it]->black;
			} else if (this->type == "grey") {
				threeColors = x[it]->grey;
			}

       		for (int i = 0; i < threeColors.running_total; i++) { // Loop through all iterations
        	        uint8_t binNum = (int)((threeColors.get_value(i) - this->minMeasure)/binSize);     // Which bin it fits in

 	               if (threeColors.get_value(i) == this->maxMeasure)  // maxMeasure will be put in bin NUMBINS... out of range so -1
                        	binNum = NUMBINS_ALL - 1;

                	this->bins[binNum] += 1; // Add one to that bin

        	}
	}

	uint32_t binner = 0;
    for (int i = 0; i < NUMBINS_ALL; i++) { // Loop through all bins
            printf("BIN %d - \t%f to %f      \t(%d items):       \t", i, this->minMeasure + i*binSize, this->minMeasure + (i+1)*binSize, this->bins[i]);
            for (int j = 0; j < this->bins[i]; j++) {     // Print stars for each bin
                    printf("~");
            }
            printf("\n");
			binner += this->bins[i];
    }
	printf("\nThere are %d items in these bins", binner);
    printf("\n\n");


}
