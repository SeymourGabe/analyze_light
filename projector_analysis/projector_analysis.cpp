#include <iostream>
#include <sstream>
#include <vector>
#include <math.h>
#include "bot.hpp"
#include "allData.hpp"

#define POSITIONS 26
#define BUFFER 1024
#define NUMBINS 10
#define NUMBINS_ALL 25
#define HEADERSIZE 100
using namespace std;

// PREDEFINE SOME FUNCTIONS
uint8_t unusedColors(vector<BOT*> x, uint8_t bots);
uint8_t unusedPositions(vector<BOT*> x, uint8_t bots);
void setAvg(vector<BOT*> x, uint8_t bots);

// MAIN
int main( int argc, char **argv ){

	// OPEN FILE
	FILE *readFile;
	readFile = fopen("projector_analysis.txt", "r");
//	readFile = fopen("test.txt", "r");
	if (!readFile){
		printf("projector_analysis.txt didn't open\n");
		return 0;
	}
	printf("\n"); // Formatting :)

	// START READING FILE
	char buffer[BUFFER];
	istringstream iss(buffer);
   	string s;

	// FLAGS, ITERATORS, ETC
	uint32_t bots = 0;
	uint8_t bot_flag = 0;
	uint8_t color_flag;
	uint8_t prev_is_equal = 0;
	uint8_t position_flag;
	uint8_t pos_flag = 0;
	uint8_t current_bot;
	uint16_t measurement = 0;
	uint8_t measurement_flag = 0;
	uint8_t measurement_num;

	// ARRAY OF BOTS
	vector<BOT*> x;

	// ARRAY OF ALL DATA
	//allData *allWhite = new allData("white");
    //allData *allBlack = new allData("black");
    //allData *allGrey = new allData("grey");
	//allData *allColor[3] = { allWhite, allBlack, allGrey };


	// READ THE ENTIRE FILE
	while(fgets(buffer, sizeof(buffer), readFile) != NULL) {
		iss.clear();		// Clear previous buffer
		iss.str(buffer);	// Load new buffer
		while (iss >> s) {	// Pump this buffer into string, bit by bit
		//printf("s = %s\n", s.c_str());

			/*
			 * If we detect "BOT", and this specific bot number doesn't exist,
			 * Create a new bot. Otherwise, set current bot to the previous BOT
			 */
			if (bot_flag == 1) {	// If we last picked up a bot,
				uint8_t new_bot = 1;	// Temp flag
				uint8_t match;
				uint8_t holdNum = stoi(s);	// Current bot number
				for (int i = 0; i < bots; i++) {	// Check if bot exists
					if (x[i]->bot_number == holdNum) {
						new_bot = 0;	// Reset temp flag if it does exist
						match = i;		// Hold which bot it is
					}
				}
				if (new_bot) {	// If you didn't find this bot already
					x.push_back(new BOT(holdNum));	// Create a bot class
					current_bot = bots;	// Update current_bot
					++bots;	// Add another
				} else {
					//printf("Adding to bot %i\n", x[match]->bot_number);
					current_bot = match;	// Now acting on matching bot
				}
				bot_flag = 0;	// Reset bot flag
			} else if (s == "BOT") {	// If we just detected a bot
				//uint8_t new_bot = 1;
				bot_flag = 1;	// Set bot flag
			}


			/*
			 * Set the appropriate color flag as needed
			 */
			if (s == "White") {
				color_flag = 0;
			} else if (s == "Black") {
				color_flag = 1;
			} else if (s == "Grey"){
				color_flag = 2;
			}

			/*
			 * If we are detecting a measurement (by detecting '=')
			 */
			if (prev_is_equal) {	// If the last string we read was an equal sign
				measurement = stoi(s);
				//printf("measurement = %i\n", measurement);
				x[current_bot]->add_measurement(color_flag, position_flag, measurement_num, measurement);
				prev_is_equal = 0;	// Reset the flag
				// Set the value of the current bot stuff
				//x[bots - 1]->updateColor(s, color_flag, allColor);	// And set the appropriate values
			} else if (s == "=") {	// Set the "=" flag when needed
				prev_is_equal = 1;
			}

			if (s == "Measurement") {
				measurement_flag = 1;
			} else if (measurement_flag) {
				measurement_flag = 0;
				measurement_num = stoi(s);
			}


			// If we're detecting a new position, create a new position for the
			// current color for the current bot
			if (pos_flag) {
				//printf("New position is %s\n", s.c_str());
				position_flag = stoi(s) - 1;
				//printf("Current bot is %i\n", current_bot);
				x[current_bot]->create_position(color_flag, position_flag);
				pos_flag = 0;
			}
			else if (s == "POS") {
				pos_flag = 1;
			}

		}

	}
	fclose(readFile); // Close the file

	printf("There are %d bots\n\n", bots);

	uint8_t not_used_color = unusedColors(x, bots);
	uint8_t not_used_positions = unusedPositions(x, bots);

	printf("There are %i unused colors\n", not_used_color);
	printf("There are %i unused positions\n", not_used_positions);
	setAvg(x, bots);

	return 0;
}

void setAvg(vector<BOT*> x, uint8_t bots) {

	for (int i = 0; i < bots; i++){
		x[i]->setAvg();
	}

}


uint8_t unusedPositions(vector<BOT*> x, uint8_t bots) {
	uint8_t running_total;
	for (int i = 0; i < bots; i++) { // Loop through all bots
		for (int j = 0; j < 3; j++) { // Loop through all colors
			for (int k = 0; k < POSITIONS; k++ ) {

				if (x[i]->colors[j]->positions[k]->num_meas == 0) {
					printf("Bot %i, color %s, position %i not used\n\n\n\n", i, x[i]->colors[j]->my_color.c_str(), k);
					++running_total;
				}/* else {
                                        printf("Bot %i, color %s, position %i has %i measurements\n", i, x[i]->colors[j]->my_color.c_str(), k, x[i]->colors[j]->positions[k]->num_meas);
				}*/

			} // k loop
		} // j loop
	} // i loop
	return running_total;
}


uint8_t unusedColors(vector<BOT*> x, uint8_t bots){
	uint8_t running_total;
	for (int i = 0; i < bots; i++) {
		if (x[i]->colors[0]->num_positions == 0) {
			printf("Bot %i color %s is not used\n", x[i]->bot_number, x[i]->colors[0]->my_color.c_str());
		 	++running_total;
		}
		if (x[i]->colors[1]->num_positions == 0) {
			printf("Bot %i color %s is not used\n", x[i]->bot_number, x[i]->colors[1]->my_color.c_str());
		    ++running_total;
		}
		if (x[i]->colors[2]->num_positions == 0) {
			printf("Bot %i color %s is not used\n", x[i]->bot_number, x[i]->colors[2]->my_color.c_str());
	  		++running_total;
		}
	}
	return running_total;
}
