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
    int moveCount =0;
    void executeSingleProblem();
    void executeProbabilisticProblem(int problemSize, double probability);
    void executeParameterizedProblem( int ballsArraySize, int blueBalls, int greenBalls, int redBalls);
    void executeFullTesting(int problemSize, int numberOfProblems, int step, int numberOfInstances);
    void SortBallsBetter();

    int findNextBall(char c, int unsBegin);

    int findNextDifferentBall(char c, int unsBegin);

    void sortGivenColour(char c, int unsortedBeginning, int amountOfBallsToSort);

    void move(int i);

    void positionBall(int unsortedBegining, int positionOfBall);

    void SortBallsWorse();

    bool areBallsSorted();

    void SortBallsBrutally();

    void printArray();
    
};

#endif