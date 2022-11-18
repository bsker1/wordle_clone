#pragma once

#include <iostream>
#include <fstream>
#include <ctime>
#include <vector>
#include <stdlib.h>

std::string pickAnswer();
bool chooseMode();
bool ynChoice();
void throwInputError();
void clearBuffer();
void initVector(std::vector<std::string> &);
void guessLoop(std::vector<std::string> &);
void generateGrid(std::vector<std::string>, std::vector<std::string>);
void getGuess(std::string &);
void getGuess(std::string &, std::string, std::string);
bool validateGuess(std::string &);
bool validateHard(std::string, std::string, std::string);
bool inDictionary(std::string);
void generateHints(std::string, std::string, std::string &);
void checkGreen(std::string, std::string, std::string &);
void checkYellow(std::string, std::string, std::string &);