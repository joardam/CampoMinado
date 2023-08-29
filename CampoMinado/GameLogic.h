#pragma once

#include <vector>
#include <SFML/Graphics.hpp>
#include <time.h>



using namespace sf;


using Matrixt2d = std::vector<std::vector<int>>; 

void fillMatrix(Matrixt2d& matrix, int size);
void placeBombs(Matrixt2d& matrix);
void placeBombCounters(Matrixt2d& matrix);
void eventButtonpressed(Matrixt2d& sMatrix, Matrixt2d& matrix, Event event, bool& eventMouseLeft, bool& changeGrid, int x, int y);
void fieldDraw(Matrixt2d& sMatrix, Matrixt2d matrix, bool eventMouseLeft, bool changeGrid, int x, int y, Sprite sprite, RenderWindow& app , int spriteSize);
void spriteDraw(Sprite sprite, RenderWindow& app, int spriteSize, Matrixt2d& sMatrix, int row, int col);
void analyzeEmptySpaces(Matrixt2d& sMatrix, Matrixt2d& matrix, int x, int y, int rows, int  cols);
bool availableSpace(int x, int y, int rows, int cols);