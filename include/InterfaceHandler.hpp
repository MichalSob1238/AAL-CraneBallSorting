#ifndef INTERFACEHANDLER_HPP
#define INTERFACEHANDLER_HPP

#include <iostream>
#include <exception>
#include <string>
#include <vector>
#include <stdexcept>
#include "AlgorithmRunner.hpp"

class InterfaceHandler
{
private:
    AlgorithmRunner algorithmRunner;
    std::vector<std::string> arguments;
    int numberOfArguments, problemSize, blueBalls, greenBalls, redBalls, numberOfProblems, step, numberOfInstances;
    double probability;
    void displayHelp();
    bool isSyntaxCorrect();
    void parseSingleProblem();
    void parseProbabilisticProblem();
    void parseParameterizedProblem();
    void parseFullTesting();

public:
    InterfaceHandler(int argc, char **&argv);
    int startInterface();
};

#endif