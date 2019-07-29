#include <iostream>
#include <sstream>
#include <vector>
#include <math.h>

#include "bot.hpp"
#include "color.hpp"


#define BUFFER 1024
#define NUMBINS 10
#define NUMBINS_ALL 25
using namespace std;

// Bot constructor
BOT::BOT(uint8_t x) {
	//printf("BOT CONSTRUCTOR -> %i\n", x);
	bot_number = x;
	colors[0] = new color("White");
	colors[1] = new color("Black");
	colors[2] = new color("Grey");

}


void BOT::create_position(uint8_t color_flag, uint8_t position_flag) {
	if (color_flag == 0) {
		this->colors[0]->create_position(position_flag);
		++used_colors;
	} else if (color_flag == 1) {
		this->colors[1]->create_position(position_flag);
		++used_colors;
	} else if (color_flag == 2) {
		this->colors[2]->create_position(position_flag);
		++used_colors;
	}
}

void BOT::add_measurement(uint8_t color_flag, uint8_t position_flag, uint8_t measurement_num, uint16_t measurement){
	//printf("Adding measurement for bot %i with c_f %i, p_f %i, and m %i\n", this->bot_number, color_flag, position_flag, measurement);
	if (color_flag == 0)
		this->colors[0]->add_measurement(position_flag, measurement_num, measurement);
	if (color_flag == 1)
		this->colors[1]->add_measurement(position_flag, measurement_num, measurement);
	if (color_flag == 2)
		this->colors[2]->add_measurement(position_flag, measurement_num, measurement);

}
