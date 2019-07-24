//#include <list>
//#include <iterator>
//#include <stdio.h>
//#include <string>
#include <iostream>
#include <sstream>
#include <vector>
#include <math.h>
#include "bot.hpp"
#include "allData.hpp"


#define BUFFER 1024
#define NUMBINS 10
#define NUMBINS_ALL 25
using namespace std;

void plotHist(allData *allWhite, allData *allBlack, allData *allGrey) {

        //allWhite->plotHist();
        //allBlack->plotHist();
        //allGrey->plotHist();

}

// Get std dev for each color
void get_std(allData *allColor[3], vector<BOT*> x) {

	allColor[0]->get_std(x);
	allColor[1]->get_std(x);
	allColor[2]->get_std(x);

	printf("All white std = %f\n",  allColor[0]->stdDev);
    printf("All black std = %f\n",  allColor[1]->stdDev);
    printf("All grey std = %f\n",  allColor[2]->stdDev);

	printf("\nAll white confidence = %f\n",  allColor[0]->confidence);
    printf("All black confidence = %f\n",  allColor[1]->confidence);
    printf("All grey confidence = %f\n\n",  allColor[2]->confidence);

}

int main( int argc, char **argv ){

	// OPEN FILE
	FILE *readFile;
	readFile = fopen("light_tests.txt", "r");
	if (!readFile){
		printf("light_tests.txt didn't open\n");
		return 0;
	}

	// START READING FILE
	char buffer[BUFFER];
	istringstream iss(buffer);
   	string s;

	// FLAGS, ITERATORS, ETC
	uint32_t bots = 0;
	uint8_t bot_flag = 0;
	uint8_t color_flag;
	uint8_t prev_is_equal = 0;

	// ARRAY OF BOTS
	vector<BOT*> x;

	// ARRAY OF ALL DATA
	allData *allWhite = new allData("white");
    allData *allBlack = new allData("black");
    allData *allGrey = new allData("grey");
	allData *allColor[3] = { allWhite, allBlack, allGrey };


	// READ THE ENTIRE FILE
	while(fgets(buffer, sizeof(buffer), readFile) != NULL) {
		iss.clear();		// Clear previous buffer
		iss.str(buffer);	// Load new buffer
		while (iss >> s) {	// Pump this buffer into string, bit by bit
			if (bot_flag == 1) {	// If we last picked up a bot,
				uint8_t holdNum = stoi(s);
				x[bots++]->bot_number = holdNum;	// Set bot number
				bot_flag = 0;	// Reset bot flag
			}
			if (s == "BOT") {	// If we just detected a bot
				x.push_back(new BOT());	// Create a bot class
				bot_flag = 1;	// Set bot flag
			}
			// Set the appropriate color flag as needed
			if (s == "White") {
				color_flag = 0;
			}

			if (s == "Black") {
				color_flag = 1;
			}

			if (s == "Grey"){
				color_flag = 2;
			}

			if (prev_is_equal) {	// If the last string we read was an equal sign
				prev_is_equal = 0;	// Reset the flag
				x[bots - 1]->updateColor(s, color_flag, allColor);	// And set the appropriate values
			}
			if (s == "=")	// Set the "=" flag when needed
				prev_is_equal = 1;
		}

	}

	printf("There are %d bots\n\n", bots);
	// LOOP OVER ALL BOTS AND SET THEIR AVERAGE. PRINT THE AVERAGE
	for (int i = 0; i < x.size(); i++) {

		printf("\n~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~");
		if (x[i]->bot_number < 10)
			printf("\n~~~~~~~~~~~~~~~~~~~~~~ Bot number %d ~~~~~~~~~~~~~~~~~~~\n", x[i]->bot_number);
		else
                        printf("\n~~~~~~~~~~~~~~~~~~~~~~ Bot number %d~~~~~~~~~~~~~~~~~~~\n", x[i]->bot_number);

		printf("~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n");

		x[i]->set_avg();

		x[i]->get_std();

		x[i]->plotHist();
	}

	allColor[0]->plotHist(x);
	allColor[1]->plotHist(x);
	allColor[2]->plotHist(x);

	get_std(allColor, x);


	printf("White total = %d with %d entries.\n", allWhite->meas_total, allWhite->running_total);
	printf("White average = %f.\n", (float)allWhite->meas_total / (float)allWhite->running_total);


	fclose(readFile); // Close the file
	return 0;
}
