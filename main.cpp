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
    int arraySize;
    int table[];
    public:
    Generator(int ballsNumber)
    {
        arraySize = ballsNumber;
    }
    
    void generateRandomly()
    {
        std::random_device device;
        std::mt19937 randomNumberGenerator(device());
        std::uniform_int_distribution<std::mt19937::result_type> distBalls(0, 2);
        for (int a = 0; a < arraySize; a++)
        {
            table[a] = distBalls(randomNumberGenerator);
            std::cout<<table[a]<<std::endl;
        }

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
                  << "B is the number of problems, C is the step and D is the amount of problem instances per problem. It generates a table saved in the output_table.txt file." << std::endl;
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
            throw "Incorrect syntax or incorrect number of arguments";
    }

    void parseParameterizedProblem()
    {
        //crane -m2 -n X -d A B C >> out.txt
        if (arguments[1] != "-m2")
            throw "Used an incorrect amount of arguments";
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
            throw "Used an incorrect number of arguments";
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