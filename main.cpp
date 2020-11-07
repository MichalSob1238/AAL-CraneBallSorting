#include <iostream>
#include <fstream>
#include <exception>
#include <string>
#include <vector>
#include <stdexcept>
#include <chrono>
#include <random>
#include <algorithm>
#include "InterfaceHandler.hpp"
#include "Clock.hpp"

int main(int argc, char **argv)
{
    InterfaceHandler interface(argc, argv);
    Clock timer;
    timer.start();
    for (int a = 0; a < 10000; a++)
        std::cout << "*";
    timer.end();
    std::cout << "\n TADAM " << timer.elapsedTime() << std::endl;
    interface.startInterface();
}