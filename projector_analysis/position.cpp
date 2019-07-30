#include <iostream>
#include <sstream>
#include <vector>
#include <math.h>

#include "position.hpp"

#define POSITIONS 26
#define FOOT 12
#define PROJ_1_Z 4*FOOT + 6.5 // 4'6.5"
#define PROJ_2_Z 4*FOOT + 6.5

#define PROJ_1_X -1*FOOT
#define PROJ_2_X 9*FOOT + 2 // 9'2"

#define PROJ_1_Y 4*FOOT
#define PROJ_2_Y 4*FOOT

using namespace std;

// Constructor
position::position(uint8_t position_flag){

	my_position = position_flag;

    // Measured values
	// Projector 1
	float col0 = 4;
	float col1 = 1*FOOT + 1.5;
	float col2 = 1*FOOT + 11.5;
	float col3 = 2*FOOT + 8.5;
	float col4 = 3*FOOT + 5;
	// Projector 2
	float col5 = 8*FOOT - (3*FOOT + 7.5);
	float col6 = 8*FOOT - (2*FOOT + 10);
	float col7 = 8*FOOT - (2*FOOT);
	float col8 = 8*FOOT - (1*FOOT + 3.25);
	float col9 = 8*FOOT - 5.5;

	// Projector 1
	float row0 = 4;
	float row1 = 2*FOOT + 0.5;
	float row2 = 4*FOOT;
	float row3 = 5*FOOT + 8.25;
	float row4 = 7*FOOT + 5;
	// Projector 2
	float row5 = 6;
	float row6 = 1*FOOT + 1.75;
	float row7 = 4*FOOT + 1.5;
	float row8 = 5*FOOT + 9.25;
	float row9 = 7*FOOT + 6.5;

	float x_dist[2][13] =
	{
		{col4, col2, col0, col3, col1, col4, col2, col0, col3, col1, col4, col2, col0},
		{col9, col7, col5, col8, col6, col9, col7, col5, col8, col6, col9, col7, col5}
	};

	float y_dist[2][13] =
	{
		{row4, row4, row4, row3, row3, row2, row2, row2, row1, row1, row0, row0, row0},
		{row9, row9, row9, row8, row8, row7, row7, row7, row6, row6, row5, row5, row5}

	};



	if (my_position < 13)
		near_proj = 0;
	else
		near_proj = 1;

	float proj_x[2] = {PROJ_1_X, PROJ_2_X};
	float proj_y[2] = {PROJ_1_Y, PROJ_2_Y};
	float proj_z[2] = {PROJ_1_Z, PROJ_2_Z};

	my_x = x_dist[near_proj][my_position % 13];
	my_y = y_dist[near_proj][my_position % 13];

	near_delta_x = my_x - proj_x[near_proj];
	near_delta_y = my_y - proj_y[near_proj];
	near_delta_z = proj_z[near_proj];

        far_delta_x = my_x - proj_x[!near_proj];
	far_delta_y = my_y - proj_y[!near_proj];
	far_delta_z = proj_z[!near_proj];

	my_near_dist = sqrt(near_delta_x*near_delta_x + near_delta_y*near_delta_y + near_delta_z*near_delta_z);
        my_far_dist = sqrt(far_delta_x*far_delta_x + far_delta_y*far_delta_y + far_delta_z*far_delta_z);


//	printf("Position %i is %f inches from the near projector (%i) and %f inches from the far projector (%i)\n", my_position + 1, my_near_dist, near_proj + 1, my_far_dist, !near_proj + 1);

//    printf("POSITION CONSTRUCTOR -> %i\n", my_position);
}

void position::setAvg() {
    avg = (float)running_total / (float)num_meas;
    printf("\t\tposition %i has average %f\n", my_position, avg);
}

// add_measurement to specific position
void position::add_measurement(uint8_t measurement_num, uint16_t measurement){
    //printf("Adding measurement for position %i\n", my_position);
    measurements[measurement_num] = measurement;
    running_total += measurement;
    ++num_meas;

}
