#include <iostream>
#include <fstream>
#include <ctime>
#include <stdlib.h>

const int wordCount = 21952;

//  Picks random word from dictionary to become the desired answer
std::string pickAnswer()
{
    std::ifstream dictionary;
    dictionary.open("wordledictionary.txt");

    std::string answer;
    srand(time(NULL));
    int index = rand() % wordCount;
    for (int i = 0; i <= index; ++i)
    {
        dictionary >> answer;
    }

    dictionary.close();
    return answer;
}

//  Initializes passed string
void initString(std::string& inString)
{
    inString = "     ";
}

//  Generates grid where each guessed word is displayed
void generateGrid(std::string guessedWords[])
{
    for (int i = 0; i < 6; ++i)
    {
        for (int j = 0; j < 5; ++j)
        {
            std::cout << "| " << guessedWords[i][j] << " ";
        }
        std::cout << "|\n";
    }
}

int main()
{
    std::string answer = pickAnswer();

    std::string guessedWords[6];
    for (int i = 0; i < 6; ++i)
    {
        initString(guessedWords[i]);
    }

    generateGrid(guessedWords);

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