#include "AlgorithmRunner.hpp"

void AlgorithmRunner::SortBallsBetter()
{
    int countRed = 0 , countBlue=0, countGreen = 0;
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
    for (std::vector<char>::iterator it = ballsArray.begin(); it != ballsArray.end(); ++it)
        std::cout << ' ' << *it;
    sortGivenColour('R', 1, countRed);
    sortGivenColour('G', 1 + countRed, countGreen);
    std::cout<<std::endl<<" ";
    for (std::vector<char>::iterator it = ballsArray.begin(); it != ballsArray.end(); ++it)
        std::cout << ' ' << *it;
    std::cout<<std::endl<<" ";
}

void AlgorithmRunner::executeSingleProblem()
{
    generator.generateFromShellInput(ballsArray);
    //TODO CORRECT ALGORITHM
    SortBallsBetter();
    //cout<<RESULT AND ALL THE OTHERS (IT GOES TO COUT CAUSE USER REDIRECT THE SHELL OUTPUT TO SOME FILE HE CHOOSES)
}

void AlgorithmRunner::executeParameterizedProblem(int ballsArraySize, int blueBalls, int greenBalls, int redBalls)
{
    generator.generateProportionally(ballsArray, ballsArraySize, blueBalls, greenBalls, redBalls);
    //TODO CORRECT ALGORITHM
    SortBallsBetter();
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
            SortBallsBetter();
            clock.end();
            //TODO SAVE
            outputTableFile<<currentProblemSize<<"\t"<<b<<"\t"<<a<<"\t"<<clock.elapsedTime()<<std::endl;
            ballsArray.clear();
        }
        currentProblemSize=currentProblemSize+step;
    }
    outputTableFile.close();
}

void AlgorithmRunner::sortGivenColour(char c, int unsortedBeginning, int amountOfBallsToSort ){
    if(amountOfBallsToSort < 5)
    {
        for(int i = unsortedBeginning; i < unsortedBeginning + amountOfBallsToSort; i++)
            positionBall(i,findNextBall(c,i));

    }
    else
    {
        //Prep
        int nd = ballsArray.size() + 1 - unsortedBeginning - amountOfBallsToSort;
        std::cout << "wyliczone nd to " << nd << "  " << ballsArray.size() << "  " << unsortedBeginning << " " << amountOfBallsToSort << std::endl;
        if (nd % 3 > 0)
        {
            positionBall(unsortedBeginning,findNextBall(c,unsortedBeginning));
            for (std::vector<char>::iterator it = ballsArray.begin(); it != ballsArray.end(); ++it)
                std::cout << ' ' << *it;
            if (nd % 3 == 1)
                positionBall(unsortedBeginning+1,findNextBall(c,unsortedBeginning+1));
            else
                positionBall(unsortedBeginning+1, findNextDifferentBall(c, unsortedBeginning + 1));

            std::cout<<std::endl;
            positionBall(unsortedBeginning+2, findNextDifferentBall(c, unsortedBeginning + 2));
            positionBall(unsortedBeginning+3,findNextBall(c,unsortedBeginning+3));
            positionBall(unsortedBeginning+4,findNextBall(c,unsortedBeginning+4));// <-- EDGE CHANCE it is necessary
        } else
        {
            positionBall(unsortedBeginning,findNextBall(c,unsortedBeginning));
            positionBall(unsortedBeginning+1,findNextBall(c,unsortedBeginning+1));
        }
        int head = ballsArray.size() + 1; int tail = ballsArray.size() + 1;
        int stepsNeeded = nd / 3; int stepsDone = 0; int barrelsOutsideTail = 0;
        // ENDOF Prep
        std::cout << "The contents of ballsArray at the end of prep are:";
        for (std::vector<char>::iterator it = ballsArray.begin(); it != ballsArray.end(); ++it)
            std::cout << ' ' << *it;
        std::cout<<std::endl;
        while (stepsDone < stepsNeeded)
        {
            std::cout << "glowna pentla while (stepsDone<stepsNeeded) \nobecnie stepsDone to " << stepsDone << " a stepsNeeded to " << stepsNeeded << std::endl
                      << "Z uwagi na barrelsOutsideTail = " << barrelsOutsideTail << " idziemy do";
            if (barrelsOutsideTail < 3)
            {
                //TODO: throwOutColour
                std::cout<<" throwOutColour\n";               // ALTVER:
                int LiczI = 0;                              // int LiczI = 1;
                head--; if (ballsArray[head - 1] != c) {LiczI++;}   // do {head--;} while (ballsArray[head-1]==c);
                head--; if (ballsArray[head - 1] != c) {LiczI++;}
                head--; if (ballsArray[head - 1] != c) {LiczI++;}
                std::cout << " head doszla do " << head << " patrzaz na " << ballsArray[head - 1] << " tail to " << tail << " a LiczI to " << LiczI << std::endl;
                std::cout<<" ";
                for(int p=1; p < head; p++)
                {std::cout<<"  ";}
                std::cout<<"H"<<std::endl;
                for (std::vector<char>::iterator it = ballsArray.begin(); it != ballsArray.end(); ++it)
                    std::cout << ' ' << *it;
                std::cout<<std::endl<<" ";
                for(int p= 1; p < tail; p++)
                {std::cout<<"  ";}
                std::cout<<"T"<<std::endl;
                if (LiczI<3)
                {
                    std::cout<<"LiczI bylo mniejsze niz 3, przesuwamy od head na koniec i zmniejszamy tail\n";
                    move(head);
                    tail-=3;
                    barrelsOutsideTail+=LiczI;
                    std::cout<<" ";
                    for(int p=1; p < head; p++)
                    {std::cout<<"  ";}
                    std::cout<<"H"<<std::endl;
                    for (std::vector<char>::iterator it = ballsArray.begin(); it != ballsArray.end(); ++it)
                        std::cout << ' ' << *it;
                    std::cout<<std::endl<<" ";
                    for(int p= 1; p < tail; p++)
                    {std::cout<<"  ";}
                    std::cout<<"T"<<std::endl;
                } else
                {
                    stepsDone++;
                    std::cout<<"stepsDone increased"<<std::endl;
                }
            }
            else
            {
                std::cout<<" sortTail\n";
                //TODO: sortTail

                std::cout<<" ";
                for(int p=1; p < head; p++)
                {std::cout<<"  ";}
                std::cout<<"H"<<std::endl;
                for (std::vector<char>::iterator it = ballsArray.begin(); it != ballsArray.end(); ++it)
                    std::cout << ' ' << *it;
                std::cout<<std::endl<<" ";
                for(int p= 1; p < tail; p++)
                {std::cout<<"  ";}
                std::cout<<"T"<<std::endl;

                //std::cout<<std::endl;
                int PoczTMP = tail;
                std::cout << "Zaczynamy porzadkowac tail\n";
                for(PoczTMP; PoczTMP <= tail + 2; PoczTMP++)      //altver: <=tail+2
                {
                    positionBall(PoczTMP, findNextDifferentBall(c, PoczTMP));
                }
                tail+=3; stepsDone++; barrelsOutsideTail-=3;

                std::cout<<" ";
                for(int p=1; p < head; p++)
                {std::cout<<"  ";}
                std::cout<<"H"<<std::endl;
                for (std::vector<char>::iterator it = ballsArray.begin(); it != ballsArray.end(); ++it)
                    std::cout << ' ' << *it;
                std::cout<<std::endl<<" ";
                for(int p= 1; p < tail; p++)
                {std::cout<<"  ";}
                std::cout<<"T"<<std::endl;

                if (barrelsOutsideTail == 0)
                    tail= ballsArray.size() + 1;
                else
                {
                    while (ballsArray[tail - 1] == c)
                        tail++;
                    if (tail < ballsArray.size() - 2)
                    {
                        move(tail);
                        tail= ballsArray.size() - 2;

                        std::cout<<"one extra move\n";

                        std::cout<<" ";
                        for(int p=1; p < head; p++)
                        {std::cout<<"  ";}
                        std::cout<<"H"<<std::endl;
                        for (std::vector<char>::iterator it = ballsArray.begin(); it != ballsArray.end(); ++it)
                            std::cout << ' ' << *it;
                        std::cout<<std::endl<<" ";
                        for(int p= 1; p < tail; p++)
                        {std::cout<<"  ";}
                        std::cout<<"T"<<std::endl;

                    }
                    else
                    {
                        tail = ballsArray.size() - 2;
                    }
                }
            }

        }
        if (nd % 3 > 0)
            move(unsortedBeginning);
        if (nd % 3 > 0)
        {
            std::cout << "nd%3>0 clause\n";
            std::cout<<" ";
            for(int p=1; p < head; p++)
            {std::cout<<"  ";}
            std::cout<<"H"<<std::endl;
            for (std::vector<char>::iterator it = ballsArray.begin(); it != ballsArray.end(); ++it)
                std::cout << ' ' << *it;
            std::cout<<std::endl<<" ";
            for(int p= 1; p < tail; p++)
            {std::cout<<"  ";}
            std::cout<<"T"<<std::endl;
        }
        int Pocz = unsortedBeginning;
        for (int k =0; k < stepsNeeded; k++)
        {
            while (ballsArray[Pocz-1]==c)
                Pocz++;
            move(Pocz);
            std::cout << "\nlast loop in which we move to the end \n";
            std::cout<<" ";
            for(int p=1; p < head; p++)
            {std::cout<<"  ";}
            std::cout<<"H"<<std::endl;
            for (std::vector<char>::iterator it = ballsArray.begin(); it != ballsArray.end(); ++it)
                std::cout << ' ' << *it;
            std::cout<<std::endl<<" ";
            for(int p= 1; p < tail; p++)
            {std::cout<<"  ";}
            std::cout<<"T"<<std::endl;
        }


    }
}

int AlgorithmRunner::findNextBall(char c, int unsBegin)
{
    int positionOfBall = unsBegin;
    while(ballsArray[positionOfBall-1]!=c)
        positionOfBall++;
    //std::cout<<"found next ball at "<<positionOfBall<<"\n";
    return positionOfBall;
}

int AlgorithmRunner::findNextDifferentBall(char c, int unsBegin)
{
    int positionOfBall = unsBegin;
    while(ballsArray[positionOfBall-1]==c)
        positionOfBall++;
    std::cout<<"found nextEdge ball at "<<positionOfBall<<"\n";
    return positionOfBall;
}

void AlgorithmRunner::move(int i) {
    char tmp[3];
    int j = i - 1;

    tmp[0] = ballsArray[j];
    tmp[1] = ballsArray[j + 1];
    tmp[2] = ballsArray[j + 2];
    std::cout<<std::endl;
    for (std::vector<char>::iterator it = ballsArray.begin(); it != ballsArray.end(); ++it)
        std::cout  << *it << ' ' ;
    std::cout<<std::endl;
    std::cout << '\n' << tmp[0] << " " << ballsArray[j] <<" "<< tmp[1]<<" "<< ballsArray[j+1] << " " << tmp[2]<<" "<< ballsArray[j+2] << std::endl;
   // std::cout << '\n' << ballsArray[j-1] <<"AAA"<<std::endl;
    ballsArray.erase(ballsArray.begin() + j);
    ballsArray.push_back(tmp[0]);
    std::cout<<std::endl;
    for (std::vector<char>::iterator it = ballsArray.begin(); it != ballsArray.end(); ++it)
        std::cout  << *it << ' ' ;
    std::cout<<std::endl;
    ballsArray.erase(ballsArray.begin() + j);
    ballsArray.push_back(tmp[1]);
    std::cout<<std::endl;
    for (std::vector<char>::iterator it = ballsArray.begin(); it != ballsArray.end(); ++it)
        std::cout  << *it << ' ' ;
    std::cout<<std::endl;
    ballsArray.erase(ballsArray.begin() + j);

    ballsArray.push_back(tmp[2]);

    std::cout<<std::endl;
    for (std::vector<char>::iterator it = ballsArray.begin(); it != ballsArray.end(); ++it)
        std::cout  << *it << ' ' ;
    std::cout<<std::endl;
}

void AlgorithmRunner::positionBall(int unsortedBegining, int positionOfBall) {
    int tempLength=0;
    tempLength = ballsArray.size() - unsortedBegining + 1;
    std::cout<<tempLength << "\n";
    if (tempLength > 5) {
        std::cout << "\n tL > 5\n";
        if ((positionOfBall - unsortedBegining) % 3 == 0) {
            for (int i = 0; i < ((positionOfBall - unsortedBegining) / 3); i++)
                move(unsortedBegining);
        } else {
            int k = tempLength % 3;
            switch (k) {
                case 0:
                    if (positionOfBall + 2 > ballsArray.size()) {
                        move(unsortedBegining);
                        positionOfBall -= 3;
                    }
                    move(positionOfBall);

                    for (int i = 0; i < tempLength / 3 - 1; i++)
                        move(unsortedBegining);
                    break;
                case 1:

                    if (positionOfBall < unsortedBegining + 2) {
                        move(unsortedBegining);
                        positionOfBall = ballsArray.size() - 1;
                    }
                    move(positionOfBall - 2);
                    for (int i = 0; i < tempLength / 3; i++) { move(unsortedBegining); }
                    break;
                case 2:
                    if (positionOfBall == ballsArray.size()) {
                        move(unsortedBegining);
                        positionOfBall -= 3;
                    }
                    move(positionOfBall - 1);
                    for (int i = 0; i < tempLength / 3; i++) { move(unsortedBegining); }
                    break;
            }
        }

    } else if (tempLength == 5) {
        std::cout << "\n tL = 5 \n";
        switch (positionOfBall - unsortedBegining) {
            case 1:
                std::cout << "\n case1\n";
                move(unsortedBegining);
                move(unsortedBegining);
                break;
            case 2:
                 std::cout << "\n case2\n";
                move(unsortedBegining + 1);
                move(unsortedBegining);
                break;
            case 3:
                std::cout << "\n case3\n";
                move(unsortedBegining);
                break;
            case 4:
                std::cout << "\n case4\n";
                move(unsortedBegining);
                move(unsortedBegining);
                move(unsortedBegining);
                break;
            default:
                std::cout << "\n defaulted\n";
                break;
        }
    } else {
        switch (positionOfBall-unsortedBegining)
        {
            case 1:
                // std::cout << "\n case1\n";
                move (unsortedBegining);
                move (unsortedBegining);
                move (unsortedBegining);
                break;
            case 2:
                // std::cout << "\n case2\n";
                move (unsortedBegining);
                move (unsortedBegining);
                break;
            case 3:
                // std::cout << "\n case3\n";
                move (unsortedBegining);
                break;
            default:
                // std::cout<< " \ndefualted \n";
                break;
        }
    }
}