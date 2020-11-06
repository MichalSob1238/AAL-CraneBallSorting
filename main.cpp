#include <iostream>
#include <fstream>
#include <exception>
#include <string>
#include <vector>
#include <stdexcept>
enum programExecutionTypeEnum
{
    SINGLE_PROBLEM,
    PARAMETERIZED_PROBLEM,
    FULL_TESTING
};
class InterfaceHandler
{
public:
    int numberOfArguments;
    std::vector<std::string> arguments;
    std::string inputFile;
    std::string outputFile;
    programExecutionTypeEnum programExecutionType;
    int problemSize, blueBalls, greenBalls, redBalls;
    int numberOfProblems;
    int step;
    int numberOfInstances;
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
            }
            else if (numberOfArguments == 8)
            {
                programExecutionType = PARAMETERIZED_PROBLEM;
                parseParameterizedProblem();
            }
            else if (numberOfArguments == 10)
            {
                programExecutionType = FULL_TESTING;
                //parseFullTesting();
            }
            else
            {
                std::cout << "The specified amount of argument does not match with any type of program execution" << std::endl;
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
};

int main(int argc, char **argv)
{
    InterfaceHandler interface(argc, argv);
    interface.startInterface();
}