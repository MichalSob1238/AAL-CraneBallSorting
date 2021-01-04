#include "AlgorithmRunner.hpp"

void AlgorithmRunner::SortBallsBetter()
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

void AlgorithmRunner::SortBallsWorse()
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
    int index = 0;
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
void AlgorithmRunner::SortBallsBrutally()
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
    moveCount=moves;
}

void AlgorithmRunner::executeSingleProblem()
{
    generator.generateFromShellInput(ballsArray);
    //sortByLongestColour();
    printArray();
    sortByLongestColourProcedure();
    printArray();
    //SortBallsBetter();
    //printArray();
}

void AlgorithmRunner::executeProbabilisticProblem(int problemSize, double probability)
{
    generator.generateProbabilistically(ballsArray, problemSize, probability);
    printArray();
    //SortBallsBrutally();
    SortBallsBetter();
    printArray();
}

void AlgorithmRunner::executeParameterizedProblem(int ballsArraySize, int blueBalls, int greenBalls, int redBalls)
{
    generator.generateProportionally(ballsArray, ballsArraySize, blueBalls, greenBalls, redBalls);
    printArray();
    clock.start();
    SortBallsBetter();
    clock.end();
    printArray();
    std::cout << clock.elapsedTime() << "\n"
              << moveCount;
}

void AlgorithmRunner::executeFullTesting(int problemSize, int numberOfProblems, int step, int numberOfInstances)
{

    std::fstream outputTableFile;
    outputTableFile.open("output_table.txt", std::ios::out | std::ios::trunc);
    if (outputTableFile.good() == false)
    {
        std::cout << "Proba stworzenie pliku nie powiodla sie" << std::endl;
        return;
    }
    outputTableFile << "n"
                    << "\t"
                    << "k"
                    << "\t"
                    << "t"
                    << "\t"
                    << "time"
                    << "\t"
                    << "moveCount" << std::endl;
    int currentProblemSize = problemSize;
    for (int a = 0; a < numberOfProblems; a++)
    {
        for (int b = 0; b < numberOfInstances; b++)
        {
            moveCount = 0;
            generator.generateRandomly(ballsArray, currentProblemSize);
            clock.start();
            SortBallsWorse();
            clock.end();
            outputTableFile << currentProblemSize << "\t" << b << "\t" << a << "\t" << clock.elapsedTime() << "\t" << moveCount << std::endl;
            ballsArray.clear();
        }
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
        printArray();
        int head = ballsArray.size() + 1;
        int tail = ballsArray.size() + 1;
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
                    if (print)
                        printArray(head,tail);
                    move(head);
                    tail -= 3;
                    barrelsOutsideTail += LiczI;
                    if (print)
                        printArray(head,tail);
                }
                else
                {
                    stepsDone++;
                }
            }
            else
            {

                int PoczTMP = tail;
                for (PoczTMP; PoczTMP <= tail + 2; PoczTMP++)
                {
                    positionBall(PoczTMP, findNextDifferentBall(c, PoczTMP));
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
                        if (print)
                            printArray(head,tail);
                        move(tail);
                        tail = ballsArray.size() - 2;
                        if (print)
                            printArray(head,tail);
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
            if (print)
                printArray(head,tail);
            move(unsortedBeginning);
            if (print)
                printArray(head,tail);
        }
        int Pocz = unsortedBeginning;
        for (int k = 0; k < stepsNeeded; k++)
        {
            while (ballsArray[Pocz - 1] == c)
                Pocz++;
            if (print)
                printArray(head,tail);
            move(Pocz);
            if (print)
                printArray(head,tail);
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
    printArray();
}

void AlgorithmRunner::positionBall(int unsortedBegining, int positionOfBall)
{
    int tempLength = 0;
    tempLength = ballsArray.size() - unsortedBegining + 1;

    if (tempLength > 5)
    {

        if ((positionOfBall - unsortedBegining) % 3 == 0)
        {
            for (int i = 0; i < ((positionOfBall - unsortedBegining) / 3); i++)
                move(unsortedBegining);
        }
        else
        {
            int k = tempLength % 3;
            switch (k)
            {
            case 0:
                if (positionOfBall + 2 > ballsArray.size())
                {
                    move(unsortedBegining);
                    positionOfBall -= 3;
                }
                move(positionOfBall);

                for (int i = 0; i < tempLength / 3 - 1; i++)
                    move(unsortedBegining);
                break;
            case 1:

                if (positionOfBall < unsortedBegining + 2)
                {
                    move(unsortedBegining);
                    positionOfBall = ballsArray.size() - 1;
                }
                move(positionOfBall - 2);
                for (int i = 0; i < tempLength / 3; i++)
                {
                    move(unsortedBegining);
                }
                break;
            case 2:
                if (positionOfBall == ballsArray.size())
                {
                    move(unsortedBegining);
                    positionOfBall -= 3;
                }
                move(positionOfBall - 1);
                for (int i = 0; i < tempLength / 3; i++)
                {
                    move(unsortedBegining);
                }
                break;
            }
        }
    }
    else if (tempLength == 5)
    {

        switch (positionOfBall - unsortedBegining)
        {
        case 1:

            move(unsortedBegining);
            move(unsortedBegining);
            break;
        case 2:

            move(unsortedBegining + 1);
            move(unsortedBegining);
            break;
        case 3:

            move(unsortedBegining);
            break;
        case 4:

            move(unsortedBegining);
            move(unsortedBegining);
            move(unsortedBegining);
            break;
        default:
            break;
        }
    }
    else
    {
        switch (positionOfBall - unsortedBegining)
        {
        case 1:
            move(unsortedBegining);
            move(unsortedBegining);
            move(unsortedBegining);
            break;
        case 2:
            move(unsortedBegining);
            move(unsortedBegining);
            break;
        case 3:
            move(unsortedBegining);
            break;
        default:
            break;
        }
    }
}

void AlgorithmRunner::printArray(int head, int tail)
{   std::cout<<std::endl;
    if (head > -1 )
    {
        for(int p=1; p < head; p++)
            {std::cout<<"  ";}
        std::cout<<"H"<<std::endl;
    }
    for (std::vector<char>::iterator it = ballsArray.begin(); it != ballsArray.end(); ++it)
        std::cout << *it << ' ';
    if (tail > -1 )
    {
        std::cout<<std::endl;
        for(int p= 1; p < tail; p++)
            {std::cout<<"  ";}
        std::cout<<"T"<<std::endl;
    }
}

std::pair<int,int> AlgorithmRunner::longestColour(int beggining, char colour)
{
    std::pair<int, int> pair1;
    char currentColour = colour;
    int longestColour = 0;
    int maxLength=1;
    int pointing =0; //element of 0...n of vector that starts the longest colour chain
    for (int i = beggining-1; i < ballsArray.size(); i++) {
        if(ballsArray[i] == currentColour)
        {   std::cout<<std::endl<<ballsArray[i];
            if (ballsArray[i] == ballsArray[i+1] ) {
                maxLength++; std::cout<<" maxL: "<<maxLength;
        }
            else {
                if (maxLength > longestColour)
                {
                    longestColour = maxLength;
                    pointing = i - longestColour + 2 ;
                    std::cout<<std::endl<<"Else happene";
                }
                maxLength = 1;
            }
        }

    }
    pair1.first =  pointing;
    pair1.second = longestColour;
    std::cout<<std::endl<<"longestColour "<<longestColour<<"  "<<"pointing"<<pointing<<std::endl;
    return pair1;
}

void AlgorithmRunner::sortByLongestColour(std::pair<int,int> sequence, int beginning)
{
    int start = sequence.first;
    int lenOfSequence = sequence.second;
    std::cout<<std::endl<<"thing points to letter "<<ballsArray[start-1]<<std::endl;
    if(start==beginning)
        return;
    if (lenOfSequence == 1)
    {
        positionBall(beginning,start);
        return;
    }

    int tempLength = ballsArray.size() - beginning + 1;
    if (tempLength > 5)
    {
        if ((start - beginning) % 3 == 0)
        {   std::cout<<std::endl<<"easiest case"<<std::endl;
            for (int i = 0; i < ((start - beginning) / 3)  ; i++)
                move(beginning);
        }
        else
        {
            int k = tempLength % 3;
            switch (k)
            {
                case 0:
                    std::cout<<std::endl<<"case 0"<<std::endl;
                    if (start + 2 > ballsArray.size())
                    {
                        move(beginning);
                        start -= 3;
                    }

                    for (int i = 0; i < (lenOfSequence-1)/3 + 1; ++i) {
                        move(start);
                    }

                    for (int i = 0; i < (tempLength - lenOfSequence) / 3 ; i++)
                        move(beginning);
                    break;
                case 1:
                    std::cout<<std::endl<<" case 1"<<std::endl;
                    if (start < beginning + 2)
                    {
                        for (int i = 0; i < lenOfSequence/3; ++i) {
                            move(beginning);
                            start = ballsArray.size() - 1;
                        }

                    }
                    for (int i = 0; i < (lenOfSequence+1)/3 + 1; ++i) {
                        move(start - 2);
                    }
                    for (int i = 0; i < (tempLength - lenOfSequence)/ 3; i++)
                    {
                        move(beginning);
                    }
                    break;
                case 2:
                    if (start == ballsArray.size())
                    {
                        move(beginning);
                        start -= 3;
                    }

                    for (int i = 0; i < (lenOfSequence)/3+1; ++i) {
                        move(start - 1);
                    }
                    for (int i = 0; i < (tempLength - lenOfSequence)/ 3; i++)
                    {
                        move(beginning);
                    }
                    break;
            }
        }
    }
    else
    {
        std::cout<<"this case invoked!";
        //positionBall(beginning,start);
    }
//    if((start-beggining)%3==0)
//    {
//        for (int i = 0; i < (start-beggining)/3; ++i) {
//            move(beggining);
//        }
//        return;
//    }
//    if ((ballsArray.size()+1 - start)%3==1)
//    {
//        move(start-2);
//        for (int i = 0; i < (start-beggining)/3; ++i) {
//            move(beggining);
//        }
//        for (int i = 0; i < (start-beggining)/3; ++i) {
//            move(beggining);
//        }
//    }
//    if ((ballsArray.size()+1 - start)%3==2)
//    {
//        move(start-1);
//    }

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
    std::pair<int,int> parameters;
    int iterations = 1;
//    parameters = longestColour(beginning);
 //   std::cout<<std::endl<<"pointing to: "<<parameters.first<<" of length: "<<parameters.second;
    while (beginning < countRed+1 )
    {
        std::cout<<std::endl<<"Iteration number: "<<iterations<<"current progress: "<<beginning-1<<"/"<<countRed<<" state of array";
        printArray();
        //TODO: sort
        parameters = longestColour(beginning, 'R');
        sortByLongestColour(parameters,beginning);
        beginning+= parameters.second;
        iterations++;
    }
    std::cout<<"AAAAAAAA"; iterations=1; int b = beginning;
    while (beginning < countGreen+b )
    {
        //TODO: sort
        std::cout<<std::endl<<"Iteration number: "<<iterations<<"current progress: "<<beginning-b<<"/"<<countGreen<<" state of array";
        printArray();
        parameters = longestColour(beginning, 'G');
        sortByLongestColour(parameters,beginning);
        beginning+= parameters.second;
        iterations++;
    }

}