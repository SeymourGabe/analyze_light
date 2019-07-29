#include <iostream>
#include <sstream>
#include <vector>
#include <math.h>

#include "position.hpp"

using namespace std;

// Constructor
position::position(uint8_t position_flag){
    my_position = position_flag;
    //printf("POSITION CONSTRUCTOR -> %i\n", my_position);

    //printf("\tSet my_position to %i\n", my_position);
}

// add_measurement to specific position
void position::add_measurement(uint8_t measurement_num, uint16_t measurement){
    //printf("Adding measurement for position %i\n", my_position);
    measurements[measurement_num] = measurement;
    ++num_meas;

}
