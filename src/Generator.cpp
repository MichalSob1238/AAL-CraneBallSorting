#include "Generator.hpp"

char Generator::transformIntToCharBall(int number)
{
    if (number == 0)
        return 'B';
    if (number == 1)
        return 'G';
    if (number == 2)
        return 'R';
    return 'E'; //TODO
}

Generator::Generator()
{
    unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
    randomNumberGenerator = std::mt19937(seed);
    ballsDistributor = std::uniform_int_distribution<int>(std::uniform_int_distribution<>(0, 2));
    probabilityGenerator = std::uniform_real_distribution<double>(std::uniform_real_distribution<>(0, 1));
}

void Generator::generateRandomly(std::vector<char> &ballsArray, int ballsArraySize)
{
    for (int a = 0; a < ballsArraySize; a++)
    {
        int generatedNumber = ballsDistributor(randomNumberGenerator);
        ballsArray.push_back(transformIntToCharBall(generatedNumber));
    }
}

void Generator::generateProbabilistically(std::vector<char> &ballsArray, int ballsArraySize, double probability)
{
    int lastBall = ballsDistributor(randomNumberGenerator);
    ballsArray.push_back(transformIntToCharBall(lastBall));
    double probabilityOfSameBall;
    for (int a = 0; a < ballsArraySize - 1; a++)
    {
        probabilityOfSameBall = probabilityGenerator(randomNumberGenerator);
        if (probabilityOfSameBall <= probability)
            ballsArray.push_back(transformIntToCharBall(lastBall));
        else
        {
            int lastBall = ballsDistributor(randomNumberGenerator);
            ballsArray.push_back(transformIntToCharBall(lastBall));
        }
    }
}

void Generator::generateProportionally(std::vector<char> &ballsArray, int ballsArraySize, int b, int g, int r)
{
    int counter = 0;
    if (b == -1 && g == -1 && r == -1)
    {
        generateRandomly(ballsArray, ballsArraySize);
        return;
    }
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
    std::shuffle(ballsArray.begin(), ballsArray.end(), randomNumberGenerator);
}

bool Generator::generateFromShellInput(std::vector<char> &ballsArray)
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