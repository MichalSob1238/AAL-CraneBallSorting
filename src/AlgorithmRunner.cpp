#include "AlgorithmRunner.hpp"

void AlgorithmRunner::executeSingleProblem()
{
    generator.generateFromShellInput(ballsArray);
    //TODO CORRECT ALGORITHM
    //cout<<RESULT AND ALL THE OTHERS (IT GOES TO COUT CAUSE USER REDIRECT THE SHELL OUTPUT TO SOME FILE HE CHOOSES)
}

void AlgorithmRunner::executeParameterizedProblem(int ballsArraySize, int blueBalls, int greenBalls, int redBalls)
{
    generator.generateProportionally(ballsArray, ballsArraySize, blueBalls, greenBalls, redBalls);
    //TODO CORRECT ALGORITHM
    //cout<<RESULT AND ALL THE OTHER STUFF (IT GOES TO COUT CAUSE USER REDIRECT THE SHELL OUTPUT TO SOME FILE HE CHOOSES)
}

void AlgorithmRunner::executeFullTesting(int problemSize, int numberOfProblems, int step, int numberOfInstances)
{
    std::fstream outputTableFile;
    outputTableFile.open("output_table.txt", std::ios::out|std::ios::trunc);
    if(outputTableFile.good()==false)
    {
        std::cout<<"Proba stworzenie pliku nie powiodla sie"<<std::endl;
        return;
    }
    outputTableFile<<"n"<<"\t"<<"k"<<"\t"<<"t"<<std::endl;
    int currentProblemSize = problemSize;
    for (int a = 0; a < numberOfProblems; a++)
    {
        for (int b = 0; b < numberOfInstances; b++)
        {
            generator.generateRandomly(ballsArray, currentProblemSize);
            clock.start();
            //TODO CORRECT ALGORITHM
            clock.end();
            //TODO SAVE
            outputTableFile<<currentProblemSize<<"\t"<<b<<"\t"<<a<<"\t"<<clock.elapsedTime()<<std::endl;
            ballsArray.clear();
        }
        currentProblemSize=currentProblemSize+step;
    }
    outputTableFile.close();
}
