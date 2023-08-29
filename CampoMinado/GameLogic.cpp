#include <vector>
#include <SFML/Graphics.hpp>
#include <time.h>
#include "GameLogic.h"



using namespace sf;


using Matrixt2d = std::vector<std::vector<int>>;
void fillMatrix(Matrixt2d& matrix, int size) {
	for (int i = 1u; i <= size; i++) {
		for (int j = 1u; j <= size; j++) {
			matrix[i][j] = 10;
		}
	}
}


void placeBombs(Matrixt2d& matrix) {
	int rows = matrix.size();
	int cols = matrix[0].size();

	for (int i = 1u; i <= (rows - 2); i++)
		for (int j = 1u; j <= (cols - 2); j++) {
			if (rand() % 5 == 0) matrix[i][j] = 9;
			else matrix[i][j] = 0;
		}
}


void placeBombCounters(Matrixt2d& matrix) {
	int rows = matrix.size();
	int cols = matrix[0].size();

	auto analyzeNearBombs = [](Matrixt2d& matrix, int row, int col) {
		int n = 0;

		for (int k = -1; k <= 1; k++) {
			for (int l = -1; l <= 1; l++) {
				if (matrix[row + k][col + l] == 9) n++;
			}
		}

		return n;
		};

	for (int i = 1u; i <= (rows - 2); i++)
		for (int j = 1u; j <= (cols - 2); j++) {
			if (matrix[i][j] == 9) continue;
			matrix[i][j] = analyzeNearBombs(matrix, i, j);
		}

}

void eventButtonpressed(Matrixt2d& sMatrix, Matrixt2d& matrix, Event event, bool& eventMouseLeft, bool& changeGrid, int x, int y) {
	int rows = matrix.size();
	int cols = matrix[0].size();

	if (event.type == Event::MouseButtonPressed) {
		if (availableSpace(x,y,rows,cols)) {
			if (event.key.code == Mouse::Left) {
				if (matrix[x][y] == 9) gameOver(sMatrix, matrix, rows, cols);
				else if (sMatrix[x][y] != matrix[x][y]) {
					std::vector<std::vector<int>> reveal(rows, std::vector<int>(cols));
					analyzeEmptySpaces(reveal, sMatrix, matrix, x, y, rows, cols);
				}
			}
			else if (event.key.code == Mouse::Right) {
				if (sMatrix[x][y] == 10) sMatrix[x][y] = 11;
				else if (sMatrix[x][y] == 11) sMatrix[x][y] = 10;
			}
		}
	}
}


bool availableSpace(int x , int y, int rows , int cols) {
	if ((x > 0 && x <= (cols - 2)) && (y > 0 && y <= (rows - 2))) return true;
	else return false ;


}


void analyzeEmptySpaces(Matrixt2d& reveal, Matrixt2d& sMatrix, Matrixt2d& matrix, int x, int y, int rows, int  cols) {
	if (!(availableSpace(x, y, rows, cols)) || (reveal[x][y] == 1) || matrix[x][y] == 9) {
		return;
	}

	if (matrix[x][y] > 0 && matrix[x][y] < 9) {
		sMatrix[x][y] = matrix[x][y];
		return;
	}
	
	reveal[x][y] = 1;

	if (matrix[x][y] != 9) {
		sMatrix[x][y] = matrix[x][y];
		analyzeEmptySpaces(reveal, sMatrix, matrix, x - 1, y, rows, cols);
		analyzeEmptySpaces(reveal, sMatrix, matrix, x + 1, y, rows, cols);
		analyzeEmptySpaces(reveal, sMatrix, matrix, x, y - 1, rows, cols);
		analyzeEmptySpaces(reveal, sMatrix, matrix, x, y + 1, rows, cols);
	}
}


void gameOver(Matrixt2d& sMatrix, Matrixt2d& matrix, int rows, int cols) {
	for (int row = 1; (row <= rows - 2); row++) {
		for (int col = 1; col <= (cols - 2); col++) {
			sMatrix[row][col] = matrix[row][col];
		}
	}
}

void fieldDraw(Matrixt2d& sMatrix, Matrixt2d matrix, Sprite sprite, RenderWindow& app, int spriteSize) {
	int rows = matrix.size();
	int cols = matrix[0].size();
	
	for (int row = 1; (row <= rows - 2); row++) {
		for (int col = 1; col <= (cols - 2); col++) {
			sprite.setTextureRect(IntRect(sMatrix[row][col] * spriteSize, 0, spriteSize, spriteSize));
			sprite.setPosition(float(row * spriteSize), float(col * spriteSize));
			app.draw(sprite);
		}
	}

}