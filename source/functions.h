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