#include "InterfaceHandler.hpp"

void InterfaceHandler::displayHelp()
{
    std::cout << "\n"
              << "--------------------------------------------------------------------------------------------------------------------------------------------------" << std::endl;
    std::cout << "MENU:" << std::endl;
    std::cout << "1) crane -m1 << in.txt >> out.txt gets data (in the form of series of B's, G's and R's) from in.txt, solves the problem and writes the result to out.txt" << std::endl;
    std::cout << "2) crane -m2 -n X -d B G R >> out.txt gets problem size X from user";
    std::cout << " followed by B,G and R which are respectfully the amount of blue, green and red balls and saves the result to out.txt" << std::endl;
    std::cout << "3) crane -m3 -n A -k B -step C -r D allows to perform the whole testing phase-A is the problem size (number of balls) "
              << "B is the number of problems, C is the step and D is the amount of problem instances per problem. It generates a ballsArray saved in the output_ballsArray.txt file." << std::endl;
    std::cout<< "4) crane -m4 -n A -p B allows to generate a problem instance, where A is the problem size and B is the probability that every generated ball will be the same as the one before it"<<std::endl;
    std::cout << "--------------------------------------------------------------------------------------------------------------------------------------------------"
              << "\n"
              << std::endl;
}

bool InterfaceHandler::isSyntaxCorrect()
{
    try
    {
        if (numberOfArguments == 2)
            parseSingleProblem();
        else if (numberOfArguments == 6)
            parseProbabilisticProblem();
        else if (numberOfArguments == 4 || numberOfArguments == 8)
            parseParameterizedProblem();
        else if (numberOfArguments == 10)
            parseFullTesting();
        else
        {
            std::cout<<"The number of arguments is: "<<numberOfArguments<<std::endl;
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
void InterfaceHandler::parseProbabilisticProblem()
{
    //crane -m4 -n X -p A
    if (arguments[1] != "-m4")
        throw "You used an amount of arguments characteristic for mode 4, but there's no -m4 modifier";
    if (arguments[2] != "-n")
        throw "Used a wrong specifier, there should be -n after -m4";
    try
    {
        problemSize = std::stoi(arguments[3]);
    }
    catch (const std::invalid_argument &invalidArgument)
    {
        throw invalidArgument.what();
    }
    if (problemSize < 1)
        throw "Invalid problem size";
    if (arguments[4] != "-p")
        throw "Used a wrong specifire, there should be -p after the problem size";
    try
    {
        probability = std::stod(arguments[5]);
    }
    catch (const std::invalid_argument &invalidArgument)
    {
        throw invalidArgument.what();
    }
}
void InterfaceHandler::parseSingleProblem()
{
    if (arguments[1] != "-m1")
        throw "You used an amount of arguments characteristic for mode 1, but there's no -m1 modifier";
}

void InterfaceHandler::parseParameterizedProblem()
{
    //crane -m2 -n X -d A B C >> out.txt
    if (arguments[1] != "-m2")
        throw "You used an amount of arguments characteristic for mode 2, but there's no -m2 modifier";
    if (arguments[2] != "-n")
        throw "Used a wrong specifier, there should be -n after -m2";
    if (numberOfArguments == 4)
    {
        try
        {
            problemSize = std::stoi(arguments[3]);
        }
        catch (const std::invalid_argument &invalidArgument)
        {
            throw invalidArgument.what();
        }
        if (problemSize < 1)
            throw "Invalid problem size";
        blueBalls = -1;
        greenBalls = -1;
        redBalls = -1;
        return;
    }

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

void InterfaceHandler::parseFullTesting()
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
    if (problemSize <= 0 || numberOfProblems <= 0 || step <= 0 || numberOfInstances <= 0)
        throw "All the parameters have to be positive integers";
}

InterfaceHandler::InterfaceHandler(int argc, char **&argv)
{
    this->numberOfArguments = argc;
    std::vector<std::string> temp(argv, argv + argc);
    this->arguments = temp;
}

int InterfaceHandler::startInterface()
{
    if (numberOfArguments <= 1)
    {
        displayHelp();
        return 0;
    }
    if (!isSyntaxCorrect())
        return 0;
    if (numberOfArguments == 2)
    {
        algorithmRunner.executeSingleProblem();
    }
    if (numberOfArguments == 6)
    {
        algorithmRunner.executeProbabilisticProblem(problemSize, probability);
    }
    else if (numberOfArguments == 4 || numberOfArguments == 8)
    {
        algorithmRunner.executeParameterizedProblem(problemSize, blueBalls, greenBalls, redBalls);
    }
    else if (numberOfArguments == 10)
    {
        algorithmRunner.executeFullTesting(problemSize, numberOfProblems, step, numberOfInstances);
    }
    return 0;
}
