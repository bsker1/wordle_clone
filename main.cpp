#include <iostream>
#include <fstream>
#include <ctime>
#include <vector>
#include <stdlib.h>

#include "functions.h"

int main()
{
    std::string answer = pickAnswer();

    std::vector<std::string> guessedAnswers;
    initVector(guessedAnswers);

    guessLoop(guessedAnswers);

    return 0;
}

/*
    | . | . | . | . | . |
    | . | . | . | . | . |
    | . | . | . | . | . |
    | . | . | . | . | . |
    | . | . | . | . | . |
    | . | . | . | . | . |
*/