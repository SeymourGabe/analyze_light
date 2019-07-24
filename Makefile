# See the Makefile for myadd program
# for an example with a similar structure.

C = gcc
CXX = g++ -O0 -std=c++11
#INCLUDES =
#CFLAGS = -g -Wall $(INCLUDES)
#CXXFLAGS = -g -Wall $(INCLUDES)
#LDFLAGS = -g
#LDLIBS =

analyze_light: analyze_light.o allData.o bot.o
	$(CXX) $(CXXFLAGS) $(LDFLAGS) $(LDLIBS) analyze_light.o bot.o allData.o -o analyze_light
analyze_light.o: analyze_light.cpp bot.hpp allData.hpp
bot.o: bot.cpp bot.hpp allData.hpp
allData.o: allData.cpp allData.hpp
# selectionsort: selectionsort_main.o selectionsort.o
# selectionsort_main.o: selectionsort_main.c selectionsort.h
# selectionsort.o: selectionsort.c selectionsort.h

.PHONY: clean
clean:
	rm -f *.o a.out core analyze_light

.PHONY: all
all: clean analyze_light
