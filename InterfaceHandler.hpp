#ifndef INTERFACEHANDLER_HPP
#define INTERFACEHANDLER_HPP

#include <iostream>
#include <exception>
#include <string>
#include <vector>
#include <stdexcept>
#include "AlgorithmRunner.hpp"

enum ProgramExecutionTypeEnum
{
    SINGLE_PROBLEM,
    PARAMETERIZED_PROBLEM,
    FULL_TESTING
};

class InterfaceHandler
{
private:
    AlgorithmRunner algorithmRunner;
    ProgramExecutionTypeEnum programExecutionType;
    std::vector<std::string> arguments;
    std::string inputFile, outputFile;
    int numberOfArguments, problemSize, blueBalls, greenBalls, redBalls, numberOfProblems, step, numberOfInstances;

    void displayHelp();
    bool isSyntaxCorrect();
    void parseSingleProblem();
    void parseParameterizedProblem();
    void parseFullTesting();

public:
    InterfaceHandler(int argc, char **&argv);
    int startInterface();
};

#endif