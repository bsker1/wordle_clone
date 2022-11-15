#include "functions.h"

static const int wordCount = 21952;

//  Picks random word from dictionary to become the desired answer
std::string pickAnswer()
{
    std::ifstream dictionary;
    dictionary.open("wordledictionary.txt");

    srand(time(NULL));
    std::string answer;
    int index = rand() % wordCount;
    for (int i = 0; i <= index; ++i)
    {
        dictionary >> answer;
    }

    dictionary.close();
    return answer;
}

//  Initializes passed vector of strings
void initVector(std::vector<std::string> &inVect)
{
    for (int i = 0; i < 6; ++i)
    {
        inVect.push_back("     ");
    }
}

//  Main game loop
void guessLoop(std::vector<std::string> &guessedWords)
{
    for (int turn = 0; turn < 6; ++turn)
    {
        generateGrid(guessedWords);
        std::cout << "Guess a word: ";
        std::cin >> guessedWords[turn];
    }
    generateGrid(guessedWords);
}

//  Generates grid where each guessed word is displayed
void generateGrid(std::vector<std::string> guessedWords)
{
    for (int i = 0; i < 6; ++i)
    {
        for (int j = 0; j < 5; ++j)
        {
            char currentCharacter = toupper(guessedWords[i][j]);
            std::cout << "| " << currentCharacter << " ";
        }
        std::cout << "|\n";
    }
}