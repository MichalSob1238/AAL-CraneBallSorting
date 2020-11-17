#ifndef ALGORITHMRUNNER_HPP
#define ALGORITHMRUNNER_HPP

#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include "Clock.hpp"
#include "Generator.hpp"

class AlgorithmRunner
{
std::vector<char> ballsArray;
Generator generator;
Clock clock;
public:
    //AlgorithmRunner();
    void executeSingleProblem();
    void executeParameterizedProblem( int ballsArraySize, int blueBalls, int greenBalls, int redBalls);
    void executeFullTesting(int problemSize, int numberOfProblems, int step, int numberOfInstances);

    void SortBalls(std::vector<char> ballsArray);
};

#endif