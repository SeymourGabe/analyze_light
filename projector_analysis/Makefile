# See the Makefile for myadd program
# for an example with a similar structure.

C = gcc
CXX = g++ -O0 -std=c++11
#INCLUDES =
#CFLAGS = -g -Wall $(INCLUDES)
#CXXFLAGS = -g -Wall $(INCLUDES)
#LDFLAGS = -g
#LDLIBS =

projector_analysis: projector_analysis.o bot.o color.o position.o
	$(CXX) $(CXXFLAGS) $(LDFLAGS) $(LDLIBS) projector_analysis.o bot.o color.o position.o -o projector_analysis
projector_analysis.o: projector_analysis.cpp bot.hpp color.hpp position.hpp
bot.o: bot.cpp bot.hpp color.hpp position.hpp
color.o: color.cpp color.hpp position.hpp
position.o: position.cpp position.hpp
# selectionsort: selectionsort_main.o selectionsort.o
# selectionsort_main.o: selectionsort_main.c selectionsort.h
# selectionsort.o: selectionsort.c selectionsort.h

.PHONY: clean
clean:
	rm -f *.o a.out core projector_analysis

.PHONY: all
all: clean projector_analysis
