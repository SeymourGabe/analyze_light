#ifndef COLOR_H
#define COLOR_H

#define POSITIONS 13
#include "position.hpp"

typedef struct color{
// VARIABLES
    std::string my_color;
    uint8_t num_positions = 0;
    position *positions[POSITIONS];

// FUNCTIONS
    void create_position(uint8_t position_flag);
    void add_measurement(uint8_t position_flag, uint8_t measurement_num, uint16_t measurement);

// CONSTRUCTORS
    color(std::string s); // Constructor

} color;


#endif
