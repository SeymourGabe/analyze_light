#ifndef BOT_H
#define BOT_H
#include "color.hpp"
#include "position.hpp"

struct color;
struct position;

class BOT {

public:
// VARIABLES
std::string dataType = "bot";
uint8_t bot_number = 0;
uint8_t used_colors = 0;
color *colors[3];

// FUNCTIONS
void create_position(uint8_t color_flag, uint8_t position_flag);
void add_measurement(uint8_t color_flag, uint8_t position_flag, uint8_t measurement_num, uint16_t measurement);

// CONSTRUCTOR
BOT(uint8_t x); // Constructor



};


#endif
