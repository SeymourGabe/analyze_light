#ifndef ALLDATA_H
#define ALLDATA_H

#include "bot.hpp"

class BOT;

typedef struct allData{

	std::string type;
        uint32_t meas_total = 0;
        uint32_t running_total = 0;
        float avg;
	float stdDev;
	uint16_t minMeasure = 2048;
	uint16_t maxMeasure = 0;

	void updateTotal(int newEntry);
	void get_std();
	void plotHist(std::vector<BOT *> x);
//	allData(std::string s) {type = s;}
	allData(std::string s);
} allData;

#endif
