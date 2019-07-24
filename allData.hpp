#ifndef ALLDATA_H
#define ALLDATA_H

#include "bot.hpp"
#define NUMBINS_ALL 25

class BOT;

typedef struct allData{
// VARIABLES
	std::string type;
    uint32_t meas_total = 0;
    uint32_t running_total = 0;
    float avg;
	float stdDev;
	float confidence;
	uint16_t minMeasure = 2048;
	uint16_t maxMeasure = 0;
	uint32_t bins[NUMBINS_ALL] = {0};

// FUNCTIONS
	void updateTotal(int newEntry);
	void get_std(std::vector<BOT*> x);
	void plotHist(std::vector<BOT *> x);
	allData(std::string s);

} allData;

#endif
