#include <iostream>
#include <sstream>
#include <vector>
#include <math.h>

#include "color.hpp"
#include "position.hpp"

using namespace std;


// Constructor
color::color(std::string s) {
    my_color = s;
    //printf("COLOR CONSTRUCTOR -> %s\n", my_color.c_str());
    //printf("\tset mycolor to %s\n", my_color.c_str());
}

// ---------- FUNCTIONS ----------

/*
 * Alloc space for a new position struct
 */
void color::create_position(uint8_t position_flag){
    //printf("creating a new position for color %s\n", my_color.c_str());
    ++num_positions;
    positions[position_flag] = new position(position_flag);
}

void color::add_measurement(uint8_t position_flag, uint8_t measurement_num, uint16_t measurement){
    //printf("Adding measurement for color %s\n", my_color.c_str());
    //printf("About to go to %i\n", this->positions[position_flag]->my_position);
    this->positions[position_flag]->add_measurement(measurement_num, measurement);

}
