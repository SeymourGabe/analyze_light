#ifndef BOT_H
#define BOT_H
#include "allData.hpp"

struct allData;

class BOT {
public:
uint8_t bot_number;

void set_avg();
typedef struct {
	std::string type;
	uint16_t measurements[50];
	uint8_t running_total = 0;
	uint32_t meas_total = 0;
	float avg;
	uint16_t maxMeasure = 0;
	uint16_t minMeasure = 2048; // since light measure < 2^10
	float stdDev;
	float confidence;

	void updateColor(std::string s);
	void set_avg();
	void plotHist();
	void get_std();
	uint16_t get_value(uint8_t i);
} color;

void get_std();
void plotHist();
void updateColor(std::string s, uint8_t color_flag, allData *allColor[3]);
color black;
color grey;
color white;

// BOT constructor. Will have to change later on when this becomes more generalized.
BOT() {
	black.type = "black";
	grey.type = "grey";
	white.type = "white";
}

};


#endif
