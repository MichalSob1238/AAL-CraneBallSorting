#ifndef GENERATOR_HPP
#define GENERATOR_HPP

#include <iostream>
#include <algorithm>
#include <random>
#include <vector>

class Generator
{
    int ballsArraySize;
    std::random_device device;
    std::mt19937 randomNumberGenerator;
    std::uniform_int_distribution<int> ballsDistributor;
    std::vector<char> ballsArray;

private:
    char transformIntToCharBall(int number);

public:
    Generator(int ballsNumber, std::vector<char> &ballsArray);
    void generateRandomly();
    void generateProportionally(int b, int g, int r);
    bool generateFromShellInput();
};

#endif