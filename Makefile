# Makefile for Writing Make Files Example

# *****************************************************
# Variables to control Makefile operation

CXX = g++
CXXFLAGS = -Wall -g

# ****************************************************
# Targets needed to bring the executable up to date

main: main.o InterfaceHandler.o Clock.o
	$(CXX) $(CXXFLAGS) -o crane main.o InterfaceHandler.o Clock.o

main.o: main.cpp InterfaceHandler.hpp Clock.hpp
	$(CXX) $(CXXFLAGS) -c main.cpp

AlgorithmRunner.o: AlgorithmRunner.hpp Clock.hpp

Clock.o: Clock.hpp

Generator.o: Generator.hpp

InterfaceHandler.o: InterfaceHandler.hpp AlgorithmRunner.hpp
