#include <iostream>
#include <fstream>
#include <exception>
#include <string>
#include <vector>
#include <stdexcept>
#include <chrono>
#include <random>

enum ProgramExecutionTypeEnum
{
    SINGLE_PROBLEM,
    PARAMETERIZED_PROBLEM,
    FULL_TESTING
};

class Clock
{
};

class Generator
{
    int ballsArraySize;
    std::random_device device;
    std::mt19937 randomNumberGenerator;
    std::uniform_int_distribution<int> ballsDistributor;
    std::vector<char> ballsArray;
private:
char transformIntToCharBall(int number)
    {
        if (number == 0)
            return 'B';
        if (number == 1)
            return 'G';
        if (number = 2)
            return 'R';
        return;
    }

public:
    Generator(int ballsNumber)
    {
        ballsArraySize = ballsNumber;
        randomNumberGenerator = std::mt19937(device());
        ballsDistributor = std::uniform_int_distribution<int>(std::uniform_int_distribution<>(0, 2));
    }

    void generateRandomly()
    {
        for (int a = 0; a < ballsArraySize; a++)
        {
            int generatedNumber = ballsDistributor(randomNumberGenerator);
            ballsArray.push_back(transformIntToCharBall(generatedNumber));
        }
    }

    void generateProportionally(int b, int g, int r)
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

};

class AlgorithmRunner
{
    //TODO
};

class InterfaceHandler
{
private:
    AlgorithmRunner algorithmRunner;
    ProgramExecutionTypeEnum programExecutionType;
    std::vector<std::string> arguments;
    std::string inputFile, outputFile;
    int numberOfArguments, problemSize, blueBalls, greenBalls, redBalls, numberOfProblems, step, numberOfInstances;
    void displayHelp()
    {
        std::cout << "\n"
                  << "--------------------------------------------------------------------------------------------------------------------------------------------------" << std::endl;
        std::cout << "MENU:" << std::endl;
        std::cout << "1) crane -m1 << in.txt >> out.txt gets data (in the form of series of B's, G's and R's) from in.txt, solves the problem and writes the result to out.txt" << std::endl;
        std::cout << "2) crane -m2 -n X -d B G R >> out.txt gets problem size X from user";
        std::cout << " followed by B,G and R which are respectfully the amount of blue, green and red balls and saves the result to out.txt" << std::endl;
        std::cout << "3) crane -m3 -n A -k B -step C -r D allows to perform the whole testing phase-A is the problem size (number of balls) "
                  << "B is the number of problems, C is the step and D is the amount of problem instances per problem. It generates a ballsArray saved in the output_ballsArray.txt file." << std::endl;
        std::cout << "--------------------------------------------------------------------------------------------------------------------------------------------------"
                  << "\n"
                  << std::endl;
    }

    bool isSyntaxCorrect()
    {
        try
        {
            if (numberOfArguments == 2)
            {
                programExecutionType = SINGLE_PROBLEM;
                parseSingleProblem();
                //runAlgorithm(SINGLE_PROBLEM);
            }
            else if (numberOfArguments == 8)
            {
                programExecutionType = PARAMETERIZED_PROBLEM;
                parseParameterizedProblem();
                //runAlgorithm(PARAMETERIZED_PROBLEM);
            }
            else if (numberOfArguments == 10)
            {
                programExecutionType = FULL_TESTING;
                parseFullTesting();
                //runAlgorithm(PARAMETERIZED_PROBLEM);
            }
            else
            {
                std::cout << "The specified amount of argument does not match with any type of program execution" << std::endl;
                std::cout << "Please refer to the help below:" << std::endl;
                displayHelp();
                return false;
            }
        }
        catch (const char *exceptionMessage)
        {
            std::cout << "\n"
                      << "Parsing unsuccessful. Your syntax appears to be incorrect. Error type: " << exceptionMessage << std::endl;
            std::cout << "Please refer to the help below:" << std::endl;
            displayHelp();
            return false;
        }
        return true;
    }

    void parseSingleProblem()
    {
        if (arguments[1] != "-m1")
            throw "You used an amount of arguments characteristic for mode 1, but there's no -m1 modifier";
    }

    void parseParameterizedProblem()
    {
        //crane -m2 -n X -d A B C >> out.txt
        if (arguments[1] != "-m2")
            throw "You used an amount of arguments characteristic for mode 2, but there's no -m2 modifier";
        if (arguments[2] != "-n")
            throw "Used a wrong specifier, there should be -n after -m2";
        try
        {
            problemSize = std::stoi(arguments[3]);
            blueBalls = std::stoi(arguments[5]);
            greenBalls = std::stoi(arguments[6]);
            redBalls = std::stoi(arguments[7]);
        }
        catch (const std::invalid_argument &invalidArgument)
        {
            throw invalidArgument.what();
        }
        if (problemSize < 1)
            throw "Invalid problem size";
        if (blueBalls + greenBalls + redBalls != problemSize)
            throw "The number of blue balls, green balls and red balls should equal the problem size";
        if (arguments[4] != "-d")
            throw "Used a wrong specifier, there should be -d after the problem size";
    }

    void parseFullTesting()
    {
        //crane -m3 -n A -k B -step C -r D
        if (arguments[1] != "-m3")
            throw "You used an amount of arguments characteristic for mode 3, but there's no -m3 modifier";
        if (arguments[2] != "-n")
            throw "Used a wrong specifier, there should be -n after -m3";
        try
        {
            problemSize = std::stoi(arguments[3]);
            numberOfProblems = std::stoi(arguments[5]);
            step = std::stoi(arguments[7]);
            numberOfInstances = std::stoi(arguments[9]);
        }
        catch (const std::invalid_argument &invalidArgument)
        {
            throw invalidArgument.what();
        }
    }

public:
    InterfaceHandler(int argc, char **&argv)
    {
        this->numberOfArguments = argc;
        std::vector<std::string> temp(argv, argv + argc);
        this->arguments = temp;
    }
    int startInterface()
    {
        if (numberOfArguments <= 1)
        {
            displayHelp();
            return 0;
        }
        else
        {
            if (!isSyntaxCorrect())
                return 0;
        }
    }
};

int main(int argc, char **argv)
{
    InterfaceHandler interface(argc, argv);
    interface.startInterface();
}