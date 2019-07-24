#ifndef ANALYZE_LIGHT_H
#define ANALYZE_LIGHT_H


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
	
	void updateColor(std::string s);	 
	void set_avg();
	void plotHist();
} color;

void plotHist();
void updateColor(std::string s, uint8_t color_flag);
color black;
color grey;
color white;

// BOT constructor. This will need changed with this is made more generalized
BOT() {
	black.type = "black";
	grey.type = "grey";
	white.type = "white";
}

};


#endif
