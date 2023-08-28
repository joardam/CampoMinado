#include <vector>
#include <SFML/Graphics.hpp>
#include <time.h>
#include "mnswfunctions.h"



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
		if (x >= 1 && x <= (cols - 2) && y >= 1 && y <= (rows - 2)) {
			if (event.key.code == Mouse::Left) {
				eventMouseLeft = true;
				if (sMatrix[x][y] != matrix[x][y]) {
					changeGrid = true;
					sMatrix[x][y] = matrix[x][y];
				}
			}
			else if (event.key.code == Mouse::Right) {
				if (sMatrix[x][y] == 10) sMatrix[x][y] = 11;
				else if (sMatrix[x][y] == 11) sMatrix[x][y] = 10;
			}
		}
	}
}


void actionConsequece(Matrixt2d& sMatrix, Matrixt2d matrix, bool eventMouseLeft, bool changeGrid, int x, int y, Sprite sprite, RenderWindow& app , int spriteSize) {
	int rows = matrix.size();
	int cols = matrix[0].size();

	auto analyzeEmptySpaces = [](Matrixt2d& sMatrix, Matrixt2d& matrix, int row, int col, int x, int y) {
		for (int k = -1; k <= 1; k++) {
			for (int l = -1; l <= 1; l++) {
				if (matrix[x + k][y + l] != 9) sMatrix[x + k][y + l] = matrix[x + k][y + l];
			}
		}
		};


	for (int row = 1; row <= 10; row++) {
		for (int col = 1; col <= 10; col++) {

			if (eventMouseLeft) {
				if (x >= 1u && x <= (cols - 2) && y >= 1u && y <= (rows - 2)) {
					if (sMatrix[x][y] == 9) sMatrix[row][col] = matrix[row][col];
					if (sMatrix[x][y] == 0 && changeGrid == true) {
						analyzeEmptySpaces(sMatrix, matrix, row, col, x, y);

					}
				}
			}


			sprite.setTextureRect(IntRect(sMatrix[row][col] * spriteSize, 0, spriteSize, spriteSize));
			sprite.setPosition(float(row * spriteSize), float(col * spriteSize));
			app.draw(sprite);
		}
	}
}