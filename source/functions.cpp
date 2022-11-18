#include "functions.h"

static const int wordCount = 21952;

//  Picks random word from dictionary to become the desired answer
std::string generateAnswer()
{
    std::ifstream dictionary;
    dictionary.open("wordledictionary.txt");
    if (!dictionary)
    {
        std::cerr << "fstream error" << std::endl;
        std::cin.get();
    }

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

//  Prompts the user to enable hard mode or not, returns true is enabled
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
    bool hardMode = chooseMode();

    std::string answer = generateAnswer();
    std::cout << "TESTING: answer is " << answer << std::endl;
    std::vector<std::string> hints;
    initVector(hints);

    int turn = 0;
    bool loopFlag = true;

    generateGrid(guessedWords, hints);
    while (loopFlag)
    {
        if (hardMode && turn > 0)
        {
            getGuess(guessedWords[turn], guessedWords[turn - 1], hints[turn - 1]);
        }
        else
        {
            getGuess(guessedWords[turn]);
        }

        generateHints(answer, guessedWords[turn], hints[turn]);

        generateGrid(guessedWords, hints);

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

//  Prompts the user to enter a word
void getGuess(std::string &guess)
{
    bool loopFlag = true;
    while (loopFlag)
    {
        std::cout << "Guess a word" << std::endl;
        std::cout << "\n*__ ";
        std::cin >> guess;
        if (validateGuess(guess))
        {
            loopFlag = false;
        }
        else
        {
            clearBuffer();
        }
    }
}

//  Prompts user to enter a word
void getGuess(std::string &guess, std::string prevGuess, std::string prevHints)
{
    bool loopFlag = true;
    while (loopFlag)
    {
        std::cout << "Guess a word" << std::endl;
        std::cout << "\n*__ ";
        std::cin >> guess;
        if (validateGuess(guess) && validateHard(guess, prevGuess, prevHints))
        {
            loopFlag = false;
        }
        else
        {
            clearBuffer();
        }
    }
}

//  Returns false if input fails any format check, true otherwise
bool validateGuess(std::string &guess)
{
    if (std::cin.fail())
    {
        throwInputError();
        return false;
    }

    if (guess.size() != 5)
    {
        std::cerr << "ERROR: word must be 5 letters long" << std::endl;
        return false;
    }

    for (int i = 0; i < 5; ++i)
    {
        guess[i] = tolower(guess[i]);
        if (guess[i] < 97 || guess[i] > 122)
        {
            std::cerr << "ERROR: word must only contain letters" << std::endl;
            return false;
        }
    }

    if (!inDictionary(guess))
    {
        std::cerr << "ERROR: word does not exist" << std::endl;
        return false;
    }

    return true;
}

//  Outputs false if guess is missing any revealed hints, true otherwise
bool validateHard(std::string guess, std::string prevGuess, std::string prevHints)
{
    bool checkedIndexes[5] = {false, false, false, false, false};

    //  Checks if all green hints are present
    for (int i = 0; i < 5; ++i)
    {
        if (prevHints[i] != 'G')
        {
            continue;
        }
        if (guess[i] != prevGuess[i])
        {
            std::cerr << "ERROR: word must contain all revealed hints" << std::endl;
            return false;
        }
        //  Marks current index as checked if the letter is present
        checkedIndexes[i] = true;
    }

    //  Checks if all yellow hints are present
    for (int i = 0; i < 5; ++i)
    {
        bool hintIsPresent = false;
        if (prevHints[i] != 'Y')
        {
            continue;
        }

        //  Checks each character of guess to see if the yellow hint is present
        for (int j = 0; j < 5; ++j)
        {
            if (checkedIndexes[j])
            {
                continue;
            }
            if (guess[j] == prevGuess[i])
            {
                hintIsPresent = true;
                checkedIndexes[j] = true;
                break;
            }
        }
        if (!hintIsPresent)
        {
            std::cerr << "ERROR: word must contain all revealed hints" << std::endl;
            return false;
        }
    }

    return true;
}

//  Returns true if the given word is in the Wordle dictionary, true otherwise
bool inDictionary(std::string inString)
{
    std::ifstream dictionary;
    dictionary.open("wordledictionary.txt");
    if (!dictionary)
    {
        std::cerr << "fstream error" << std::endl;
        std::cin.get();
    }
    std::string currentWord;

    while (dictionary >> currentWord)
    {
        if (inString == currentWord)
        {
            dictionary.close();
            return true;
        }
    }

    dictionary.close();
    return false;
}

//  Fills hint string with G or Y for each character present in the answer
void generateHints(std::string answer, std::string guess, std::string &hint)
{
    hint = "xxxxx";
    checkGreen(answer, guess, hint);
    checkYellow(answer, guess, hint);
}

//  Changes character to G if the letter is in the correct position to the answer
void checkGreen(std::string answer, std::string guess, std::string &hint)
{
    for (int i = 0; i < 5; ++i)
    {
        if (guess[i] == answer[i])
        {
            hint[i] = 'G';
        }
    }
}

//  Changes character to Y if the letter is present anywhere else in the word
void checkYellow(std::string answer, std::string guess, std::string &hint)
{
    for (int i = 0; i < 5; ++i)
    {
        //  Don't consider the character if it's already been marked green
        if (hint[i] == 'G')
        {
            continue;
        }
        for (int j = 0; j < 5; ++j)
        {
            //  Don't consider the character if it's already been marked as a hint
            if (hint[j] != 'x')
            {
                continue;
            }
            if (guess[i] == answer[j])
            {
                hint[i] = 'Y';
            }
        }
    }
}