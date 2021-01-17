#include "AlgorithmRunner.hpp"

void AlgorithmRunner::setType(int type)
{
    algorithmType = type;
}
void AlgorithmRunner::runAlgorithm()
{
    switch (algorithmType)
    {
    case 1:
        sortBallsBetter();
        break;
    case 2:
        sortBallsWorse();
        break;
    case 3:
        sortBallsBrutally();
        break;
    case 4:
        sortByLongestColourProcedure();
        break;
    default:
        std::cout << "Something went wrong while trying to run the algorithm" << std::endl;
    }
}
void AlgorithmRunner::sortBallsBetter()
{
    int countRed = 0, countBlue = 0, countGreen = 0;
    for (std::vector<char>::iterator it = ballsArray.begin(); it != ballsArray.end(); ++it)
    {
        switch (*it)
        {
        case 'R':
            countRed++;
            break;
        case 'G':
            countGreen++;
            break;
        case 'B':        //
            countBlue++; //<-superfluous in our case
            break;       //
        }
    }
    sortGivenColour('R', 1, countRed);
    sortGivenColour('G', 1 + countRed, countGreen);
}

void AlgorithmRunner::sortBallsWorse()
{
    int countRed = 0, countBlue = 0, countGreen = 0;

    for (std::vector<char>::iterator it = ballsArray.begin(); it != ballsArray.end(); ++it)
    {
        switch (*it)
        {
        case 'R':
            countRed++;
            break;
        case 'G':
            countGreen++;
            break;
        case 'B':        //
            countBlue++; //<-superfluous in our case
            break;       //
        }
    }
    for (int i = 1; i <= countRed; i++)
    {
        positionBall(i, findNextBall('R', i));
    }

    for (int i = countRed + 1; i <= countGreen + countRed; i++)
    {
        positionBall(i, findNextBall('G', i));
    }
}

bool AlgorithmRunner::areBallsSorted()
{
    unsigned int index = 0;
    while (ballsArray[index] == 'R')
        index++;
    while (ballsArray[index] == 'G')
        index++;
    while (ballsArray[index] == 'B')
        index++;
    if (index == ballsArray.size())
        return true;
    return false;
}
void AlgorithmRunner::sortBallsBrutally()
{
    std::vector<std::vector<char>> possibilities;
    possibilities.push_back(ballsArray);
    std::vector<char> tmp = ballsArray;
    int moves = 0;
    int arrayIndex = 0;
    int lastMoveIndex = ballsArray.size() - 3;
    while (1)
    {
        ballsArray = possibilities[arrayIndex];
        if (areBallsSorted())
            break;
        moves++;
        for (int a = 0; a < lastMoveIndex; a++)
        {
            ballsArray = possibilities[arrayIndex];
            move(a + 1);
            possibilities.push_back(ballsArray);
        }
        arrayIndex++;
    }
    moveCount = moves;
}

void AlgorithmRunner::executeSingleProblem()
{
    generator.generateFromShellInput(ballsArray);
    //printArray();
    runAlgorithm();
    //printArray();
    //sortBallsBetter();
    //printArray();
}

void AlgorithmRunner::executeProbabilisticProblem(int problemSize, double probability)
{
    generator.generateProbabilistically(ballsArray, problemSize, probability);
    //printArray();
    //clock.start();
    runAlgorithm();
    //clock.end();
    //printArray();

}

void AlgorithmRunner::executeParameterizedProblem(int ballsArraySize, int blueBalls, int greenBalls, int redBalls)
{
    generator.generateProportionally(ballsArray, ballsArraySize, blueBalls, greenBalls, redBalls);
    //clock.start();
    runAlgorithm();
    //clock.end();
}

void AlgorithmRunner::executeFullTesting(int problemSize, int numberOfProblems, int step, int numberOfInstances)
{
    std::fstream outputTableFile;
    outputTableFile.open("output_table.txt", std::ios::out);
    if (outputTableFile.good() == false)
    {
        std::cout << "Proba stworzenie pliku nie powiodla sie" << std::endl;
        return;
    }
    outputTableFile << "n"
                    << "\t"
                    << "time"
                    << "\t"
                    << "moveCount" << std::endl;
    int currentProblemSize = problemSize;
    double time = 0;
    int moves = 0;
    for (int a = 0; a < numberOfProblems; a++)
    {
        for (int b = 0; b < numberOfInstances; b++)
        {
            moveCount = 0;
            generator.generateRandomly(ballsArray, currentProblemSize);
            clock.start();
            runAlgorithm();
            clock.end();
            time += clock.elapsedTime();
            moves += moveCount;
            ballsArray.clear();
        }
        time = time / numberOfInstances;
        moves = moves / numberOfInstances;
        outputTableFile << currentProblemSize << "\t" << time << "\t" << moves << std::endl;
        time = 0;
        moves = 0;
        currentProblemSize = currentProblemSize + step;
    }
    outputTableFile.close();
}

void AlgorithmRunner::sortGivenColour(char c, int unsortedBeginning, int amountOfBallsToSort)
{
    if (amountOfBallsToSort < 5)
    {
        for (int i = unsortedBeginning; i < unsortedBeginning + amountOfBallsToSort; i++)
        {
            positionBall(i, findNextBall(c, i));
        }
    }
    else
    {
        //Prep
        int nd = ballsArray.size() + 1 - unsortedBeginning - amountOfBallsToSort;
        if (nd % 3 > 0)
        {
            positionBall(unsortedBeginning, findNextBall(c, unsortedBeginning));

            if (nd % 3 == 1)
                positionBall(unsortedBeginning + 1, findNextBall(c, unsortedBeginning + 1));
            else
                positionBall(unsortedBeginning + 1, findNextDifferentBall(c, unsortedBeginning + 1));

            positionBall(unsortedBeginning + 2, findNextDifferentBall(c, unsortedBeginning + 2));
            positionBall(unsortedBeginning + 3, findNextBall(c, unsortedBeginning + 3));
            positionBall(unsortedBeginning + 4, findNextBall(c, unsortedBeginning + 4)); // <-- EDGE CHANCE it is necessary
        }
        else
        {
            positionBall(unsortedBeginning, findNextBall(c, unsortedBeginning));
            positionBall(unsortedBeginning + 1, findNextBall(c, unsortedBeginning + 1));
        }
        //printArray();
        int head = ballsArray.size() + 1;
        unsigned int tail = ballsArray.size() + 1;
        int stepsNeeded = nd / 3;
        int stepsDone = 0;
        int barrelsOutsideTail = 0;
        while (stepsDone < stepsNeeded)
        {

            if (barrelsOutsideTail < 3)
            {

                int LiczI = 0;
                head--;
                if (ballsArray[head - 1] != c)
                {
                    LiczI++;
                }
                head--;
                if (ballsArray[head - 1] != c)
                {
                    LiczI++;
                }
                head--;
                if (ballsArray[head - 1] != c)
                {
                    LiczI++;
                }

                if (LiczI < 3)
                {

                    //printArray(head, tail);
                    move(head);
                    tail -= 3;
                    barrelsOutsideTail += LiczI;
                   //printArray(head, tail);
                }
                else
                {
                    stepsDone++;
                }
            }
            else
            {
                unsigned int begTMP = tail;
                for (begTMP=tail; begTMP <= tail + 2; begTMP++)
                {
                    positionBall(begTMP, findNextDifferentBall(c, begTMP));
                }
                tail += 3;
                stepsDone++;
                barrelsOutsideTail -= 3;

                if (barrelsOutsideTail == 0)
                    tail = ballsArray.size() + 1;
                else
                {
                    while (ballsArray[tail - 1] == c)
                        tail++;
                    if (tail < ballsArray.size() - 2)
                    {

                       // printArray(head, tail);
                        move(tail);
                        tail = ballsArray.size() - 2;

                        //printArray(head, tail);
                    }
                    else
                    {
                        tail = ballsArray.size() - 2;
                    }
                }
            }
        }
        if (nd % 3 > 0)
        {

            //printArray(head, tail);
            move(unsortedBeginning);
            //printArray(head, tail);
        }
        int beg = unsortedBeginning;
        for (int k = 0; k < stepsNeeded; k++)
        {
            while (ballsArray[beg - 1] == c)
                beg++;

            //printArray(head, tail);
            move(beg);
            //printArray(head, tail);
        }
    }
}

int AlgorithmRunner::findNextBall(char c, int unsBegin)
{
    int positionOfBall = unsBegin;
    while (ballsArray[positionOfBall - 1] != c)
        positionOfBall++;
    return positionOfBall;
}

int AlgorithmRunner::findNextDifferentBall(char c, int unsBegin)
{
    int positionOfBall = unsBegin;
    while (ballsArray[positionOfBall - 1] == c)
        positionOfBall++;
    return positionOfBall;
}

void AlgorithmRunner::move(int i)
{
    char tmp[3];
    int j = i - 1;

    tmp[0] = ballsArray[j];
    tmp[1] = ballsArray[j + 1];
    tmp[2] = ballsArray[j + 2];

    ballsArray.erase(ballsArray.begin() + j);
    ballsArray.push_back(tmp[0]);
    ballsArray.erase(ballsArray.begin() + j);
    ballsArray.push_back(tmp[1]);
    ballsArray.erase(ballsArray.begin() + j);
    ballsArray.push_back(tmp[2]);
    moveCount++;

}

void AlgorithmRunner::positionBall(int unsortedBeginning, int positionOfBall)
{
    int tempLength = 0;
    tempLength = ballsArray.size() - unsortedBeginning + 1;

    if (tempLength > 5)
    {

        if ((positionOfBall - unsortedBeginning) % 3 == 0)
        {
            for (int i = 0; i < ((positionOfBall - unsortedBeginning) / 3); i++)
                move(unsortedBeginning);
        }
        else
        {
            int k = tempLength % 3;
            switch (k)
            {
            case 0:
                if ((unsigned int)positionOfBall + 2 > ballsArray.size())
                {
                    move(unsortedBeginning);
                    positionOfBall -= 3;
                }
                move(positionOfBall);

                for (int i = 0; i < tempLength / 3 - 1; i++)
                    move(unsortedBeginning);
                break;
            case 1:

                if (positionOfBall < unsortedBeginning + 2)
                {
                    move(unsortedBeginning);
                    positionOfBall = ballsArray.size() - 1;
                }
                move(positionOfBall - 2);
                for (int i = 0; i < tempLength / 3; i++)
                {
                    move(unsortedBeginning);
                }
                break;
            case 2:
                if ((unsigned int) positionOfBall == ballsArray.size())
                {
                    move(unsortedBeginning);
                    positionOfBall -= 3;
                }
                move(positionOfBall - 1);
                for (int i = 0; i < tempLength / 3; i++)
                {
                    move(unsortedBeginning);
                }
                break;
            }
        }
    }
    else if (tempLength == 5)
    {

        switch (positionOfBall - unsortedBeginning)
        {
        case 1:

            move(unsortedBeginning);
            move(unsortedBeginning);
            break;
        case 2:

            move(unsortedBeginning + 1);
            move(unsortedBeginning);
            break;
        case 3:

            move(unsortedBeginning);
            break;
        case 4:

            move(unsortedBeginning);
            move(unsortedBeginning);
            move(unsortedBeginning);
            break;
        default:
            break;
        }
    }
    else
    {
        switch (positionOfBall - unsortedBeginning)
        {
        case 1:
            move(unsortedBeginning);
            move(unsortedBeginning);
            move(unsortedBeginning);
            break;
        case 2:
            move(unsortedBeginning);
            move(unsortedBeginning);
            break;
        case 3:
            move(unsortedBeginning);
            break;
        default:
            break;
        }
    }
}

void AlgorithmRunner::printArray(int head, int tail)
{
    if (print) {
        std::cout << std::endl;
        if (head > -1) {
            for (int p = 1; p < head; p++) {
                std::cout << "  ";
            }
            std::cout << "H" << std::endl;
        }
        for (std::vector<char>::iterator it = ballsArray.begin(); it != ballsArray.end(); ++it)
            std::cout << *it << ' ';
        if (tail > -1) {
            std::cout << std::endl;
            for (int p = 1; p < tail; p++) {
                std::cout << "  ";
            }
            std::cout << "T" << std::endl;
        }
    }
}

std::pair<int, int> AlgorithmRunner::longestColour(int beginning, char colour)
{
    std::pair<int, int> pair1;
    char currentColour = colour;
    int longestColour = 0;
    int maxLength = 1;
    int pointing = 0; //element of 0...n of vector that starts the longest colour chain
    for (unsigned int i = beginning - 1; i < ballsArray.size(); i++)
    {
        if (ballsArray[i] == currentColour)
        {

            if (ballsArray[i] == ballsArray[i + 1])
            {
                maxLength++;

            }
            else
            {
                if (maxLength > longestColour)
                {
                    longestColour = maxLength;
                    pointing = i - longestColour + 2;
                }
                maxLength = 1;
            }
        }
    }
    pair1.first = pointing;
    pair1.second = longestColour;
//    std::cout << std::endl
//              << "longestColour " << longestColour << "  "
//              << "pointing" << pointing << std::endl;
    return pair1;
}

void AlgorithmRunner::sortByLongestColour(std::pair<int, int> sequence, int beginning)
{
    int start = sequence.first;
    int lenOfSequence = sequence.second;
//    std::cout << std::endl
//              << "thing points to letter " << ballsArray[start - 1] << std::endl;
    if (start == beginning)
        return;
    if (lenOfSequence == 1)
    {
        positionBall(beginning, start);
        return;
    }

    int tempLength = ballsArray.size() - beginning + 1;
    if (tempLength > 5)
    {
        if ((start - beginning) % 3 == 0)
        {
//            std::cout << std::endl
//                      << "easiest case" << std::endl;
            for (int i = 0; i < ((start - beginning) / 3); i++)
                move(beginning);
        }
        else
        {
            int k = tempLength % 3;
            switch (k)
            {
            case 0:
//                std::cout << std::endl
//                          << "case 0" << std::endl;
                if ((unsigned int)start + 2 > ballsArray.size())
                {
                    move(beginning);
                    start -= 3;
                }

                for (int i = 0; i < (lenOfSequence - 1) / 3 + 1; ++i)
                {
                    move(start);
                }

                for (int i = 0; i < (tempLength - lenOfSequence) / 3; i++)
                    move(beginning);
                break;
            case 1:
//                std::cout << std::endl
//                          << " case 1" << std::endl;
                if (start < beginning + 2)
                {
                    for (int i = 0; i < lenOfSequence / 3; ++i)
                    {
                        move(beginning);
                        start = ballsArray.size() - 1;
                    }
                }
                for (int i = 0; i < (lenOfSequence + 1) / 3 + 1; ++i)
                {
                    move(start - 2);
                }
                for (int i = 0; i < (tempLength - lenOfSequence) / 3; i++)
                {
                    move(beginning);
                }
                break;
            case 2:
                if ((unsigned int)start == ballsArray.size())
                {
                    move(beginning);
                    start -= 3;
                }

                for (int i = 0; i < (lenOfSequence) / 3 + 1; ++i)
                {
                    move(start - 1);
                }
                for (int i = 0; i < (tempLength - lenOfSequence) / 3; i++)
                {
                    move(beginning);
                }
                break;
            }
        }
    }
    else
    {
        std::cout << "this case invoked!";
        positionBall(beginning,start);
    }

}

void AlgorithmRunner::sortByLongestColourProcedure()
{
    int countRed = 0, countBlue = 0, countGreen = 0;
    for (std::vector<char>::iterator it = ballsArray.begin(); it != ballsArray.end(); ++it)
    {
        switch (*it)
        {
        case 'R':
            countRed++;
            break;
        case 'G':
            countGreen++;
            break;
        case 'B':        //
            countBlue++; //<-superfluous in our case
            break;       //
        }
    }
    int beginning = 1;
    std::pair<int, int> parameters;
    int iterations = 1;
    while (beginning < countRed + 1)
    {
//        std::cout << std::endl
//                  << "Iteration number: " << iterations
//                  << "current progress: " << beginning - 1 << "/" << countRed << " state of array";
       // printArray();
        parameters = longestColour(beginning, 'R');
        sortByLongestColour(parameters, beginning);
        beginning += parameters.second;
        iterations++;
        std::cout<<"BEGINNING "<<beginning<<" "<<countRed<<std::endl;
    }

    iterations = 1;
    int b = beginning;
    while (beginning < countGreen + b)
    {
        std::cout<<"GREEN "<<beginning<<" "<<countGreen<<" "<<countRed<<" "<<countGreen+b<<std::endl;
        //TODO: sort
//        std::cout << std::endl
//                  << "Iteration number: " << iterations << "current progress: " << beginning - b << "/" << countGreen << " state of array";
//        printArray();
        parameters = longestColour(beginning, 'G');
        sortByLongestColour(parameters, beginning);
        beginning += parameters.second;
        iterations++;
    }
}