#ifndef ALGORITHMRUNNER_HPP
#define ALGORITHMRUNNER_HPP

#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include "Clock.hpp"
#include "Generator.hpp"
#include <utility>

class AlgorithmRunner
{
    std::vector<char> ballsArray;
    Generator generator;
    Clock clock;
    bool print = false;

public:
    int algorithmType = 1;

    int moveCount = 0;

    void executeSingleProblem();

    void setType(int type);

    void runAlgorithm();

    void executeProbabilisticProblem(int problemSize, double probability);

    void executeParameterizedProblem(int ballsArraySize, int blueBalls, int greenBalls, int redBalls);

    void executeFullTesting(int problemSize, int numberOfProblems, int step, int numberOfInstances);

    void sortBallsBetter();

    int findNextBall(char c, int unsBegin);

    int findNextDifferentBall(char c, int unsBegin);

    void sortGivenColour(char c, int unsortedBeginning, int amountOfBallsToSort);

    void move(int i);

    void positionBall(int unsortedBeginning, int positionOfBall);

    void sortBallsWorse();

    bool areBallsSorted();

    void sortBallsBrutally();

    void printArray(int head = -1, int tail = -1);

    std::pair<int, int> longestColour(int beginning, char colour);

    void sortByLongestColourProcedure();

    void sortByLongestColour(std::pair<int, int> sequence, int beginning);
};

#endif