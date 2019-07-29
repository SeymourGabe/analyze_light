# See the Makefile for myadd program
# for an example with a similar structure.

C = gcc
CXX = g++ -O0 -std=c++11
#INCLUDES =
#CFLAGS = -g -Wall $(INCLUDES)
#CXXFLAGS = -g -Wall $(INCLUDES)
#LDFLAGS = -g
#LDLIBS =

noise_analysis: noise_analysis.o allData.o bot.o
	$(CXX) $(CXXFLAGS) $(LDFLAGS) $(LDLIBS) noise_analysis.o bot.o allData.o -o noise_analysis
noise_analysis.o: noise_analysis.cpp bot.hpp allData.hpp
bot.o: bot.cpp bot.hpp allData.hpp
allData.o: allData.cpp allData.hpp
# selectionsort: selectionsort_main.o selectionsort.o
# selectionsort_main.o: selectionsort_main.c selectionsort.h
# selectionsort.o: selectionsort.c selectionsort.h

.PHONY: clean
clean:
	rm -f *.o a.out core noise_analysis

.PHONY: all
all: clean noise_analysis
