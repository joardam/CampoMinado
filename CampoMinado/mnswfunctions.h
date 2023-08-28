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
void actionConsequece(Matrixt2d& sMatrix, Matrixt2d matrix, bool eventMouseLeft, bool changeGrid, int x, int y, Sprite sprite, RenderWindow& app , int spriteSize);