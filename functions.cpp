#include "functions.h"

static const int wordCount = 21952;

//  Picks random word from dictionary to become the desired answer
std::string generateAnswer()
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

//  Prompts the user to enable hard mode or not
bool chooseMode()
{
    std::cout << "Enable hard mode?" << std::endl;
    std::cout << "(If hard mode is enabled, each revealed letter must be used in\n"
              << "subsequent guesses)" << std::endl;

    return ynChoice();
}

//  Gets yes or no choice from user
bool ynChoice()
{
    char choice;
    bool loopFlag = true;
    while (loopFlag)
    {
        std::cout << "\n(Y/N) *__ ";
        std::cin >> choice;
        loopFlag = std::cin.fail() || (toupper(choice) != 'Y' && 
                                       toupper(choice) != 'N');
        if (loopFlag)
        {
            throwInputError();
        }
    }
    
    choice = toupper(choice);
    if (choice == 'Y')
    {
        return true;
    }
    else if (choice == 'N')
    {
        return false;
    }
    else
    {
        std::cerr << "ERROR: indeterminate return (ynChoice)" << std::endl;
        return false;
    }
}

//  Informs user of input error
void throwInputError()
{
    std::cerr << "\nERROR: invalid input\n";
    clearBuffer();
    std::cin.get();
}

//  Clears input buffer
void clearBuffer()
{
    std::cin.clear();
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
}

//  Initializes passed vector of strings with 6 strings with 5 spaces each
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
    bool mode = chooseMode();

    std::string answer = generateAnswer();
    std::vector<std::string> hints;
    initVector(hints);
    int turn = 0;
    bool loopFlag = true;
    while (loopFlag)
    {
        generateGrid(guessedWords, hints);

        std::cout << "Guess a word: ";
        clearBuffer();
        std::cin >> guessedWords[turn];
        if (++turn >= 6)
        {
            loopFlag = false;
        }
    }
}

//  Generates grid where each guessed word is displayed
void generateGrid(std::vector<std::string> guessedWords, 
                  std::vector<std::string> hints)
{
    std::cout << std::endl;
    for (int i = 0; i < 6; ++i)
    {
        for (int j = 0; j < 5; ++j)
        {
            char currentCharacter = toupper(guessedWords[i][j]);
            std::cout << "| " << currentCharacter << " ";
        }
        std::cout << "|\n";
        for (int j = 0; j < 5; ++j)
        {
            std::cout << "   " << hints[i][j];
        }
        std::cout << std::endl;
    }
}