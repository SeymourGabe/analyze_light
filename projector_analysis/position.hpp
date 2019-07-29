#ifndef POSITION_H
#define POSITION_H

#define MEASUREMENTS 50
#include "position.hpp"

typedef struct position{
// VARIABLES
    uint8_t num_meas = 0;
    int16_t my_position = -1;
    uint16_t measurements[MEASUREMENTS] = {0};

// FUNCTIONS
    void add_measurement(uint8_t measurement_num, uint16_t measurement);

// CONSTRUCTOR
    position(uint8_t position_flag);

} position;


#endif
