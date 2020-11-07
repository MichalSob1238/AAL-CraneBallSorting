#include "Generator.hpp"

char Generator::transformIntToCharBall(int number)
{
    if (number == 0)
        return 'B';
    if (number == 1)
        return 'G';
    if (number = 2)
        return 'R';
    return 'E'; //TODO
}

Generator::Generator(int ballsNumber, std::vector<char> &ballsArray)
{
    ballsArraySize = ballsNumber;
    this->ballsArray = ballsArray;
    randomNumberGenerator = std::mt19937(device());
    ballsDistributor = std::uniform_int_distribution<int>(std::uniform_int_distribution<>(0, 2));
}

void Generator::generateRandomly()
{
    for (int a = 0; a < ballsArraySize; a++)
    {
        int generatedNumber = ballsDistributor(randomNumberGenerator);
        ballsArray.push_back(transformIntToCharBall(generatedNumber));
    }
}

void Generator::generateProportionally(int b, int g, int r)
{
    int counter = 0;
    while (counter < b)
    {
        ballsArray.push_back('B');
        counter++;
    }
    counter = 0;
    while (counter < g)
    {
        ballsArray.push_back('G');
        counter++;
    }
    counter = 0;
    while (counter < r)
    {
        ballsArray.push_back('R');
        counter++;
    }
    std::random_shuffle(ballsArray.begin(), ballsArray.end());
}

bool Generator::generateFromShellInput()
{
    char character;
    while (std::cin >> character)
    {
        if (character != 'B' && character != 'G' && character != 'R')
            return false;
        ballsArray.push_back(character);
    }
    return true;
}