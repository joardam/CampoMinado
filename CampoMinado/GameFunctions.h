#pragma once

#include <vector>
#include <SFML/Graphics.hpp>
#include <time.h>



using namespace sf;


using Matrixt2d = std::vector<std::vector<int>>; 

void fillMatrix(Matrixt2d& matrix, int rows , int cols);
void placeBombs(Matrixt2d& matrix , int difficulty);
void placeBombCounters(Matrixt2d& matrix);
void lampAction(Matrixt2d& matrix, Matrixt2d& sMatrix, int x, int y);
void eventButtonpressed(Matrixt2d& sMatrix, Matrixt2d& matrix, Event event, int x, int y);
void fieldDraw(Matrixt2d& sMatrix, Matrixt2d matrix, Sprite sprite, RenderWindow& app , int spriteSize);
void loopEdges(Matrixt2d& reveal, Matrixt2d& sMatrix, Matrixt2d& matrix, int x, int y, int rows, int cols);
void analyzeEmptySpaces(Matrixt2d& reveal, Matrixt2d& sMatrix, Matrixt2d& matrix, int x, int y, int rows, int  cols);
bool availableSpace(int x, int y, int rows, int cols);
void gameOver(Matrixt2d& sMatrix, Matrixt2d& matrix, int rows, int cols);
int startGame(int difficulty = 25, bool lamp = false, int matrixSize = 16);
void placeBonusLamp(Matrixt2d& matrix);