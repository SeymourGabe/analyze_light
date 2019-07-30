#ifndef POSITION_H
#define POSITION_H

#define MEASUREMENTS 50
#include "position.hpp"

typedef struct position{
// VARIABLES
    uint16_t running_total = 0; // Running totol of all measurements in this pos
    uint8_t num_meas = 0; // Number of measurements in this pos
    float avg; // Average of all measurments at this pos
    int16_t my_position = -1; // Where this is located
    uint16_t measurements[MEASUREMENTS] = {0};
    uint8_t near_proj; // Projector 0 or 1
    float my_x, my_y; // Where I'm located in x and y
    float near_delta_x, near_delta_y, near_delta_z; // How far from closest proj
    float far_delta_x, far_delta_y, far_delta_z; // How far from farthest proj
    float my_near_dist, my_far_dist; // Distance from near and far projector


// FUNCTIONS
    void add_measurement(uint8_t measurement_num, uint16_t measurement);
    void setAvg();
// CONSTRUCTOR
    position(uint8_t position_flag);

} position;


#endif
