#include <vector>
#include <SFML/Graphics.hpp>
#include <time.h>
#include "GameFunctions.h"
#include "Definitions.hpp"



using namespace sf;


using Matrixt2d = std::vector<std::vector<int>>;
void fillMatrix(Matrixt2d& matrix, int rows , int cols) {
	for (int row = 1u; row <= rows; row++) {
		for (int col = 1u; col <= cols; col++) {
			matrix[row][col] = HOUSE_COVERED;
		}
	}
}


int randIntBetween(int min, int max) {
	int range = max - min + 1;
	int randmax = rand() % range + min;
	return randmax;

}

void placeBonusLamp(Matrixt2d& matrix) {
	int apparentMatrixSize = matrix.size() - 2;
	int lampsQuantity = int(apparentMatrixSize / 8 );

	for (int i = 0u; i < (lampsQuantity); i++) {

		int lampX = randIntBetween(1, apparentMatrixSize);
		int lampY = randIntBetween(1, apparentMatrixSize);

		if (matrix[lampX][lampY] == HOUSE_LAMP) {
			i--;
			continue;
		}
		else matrix[lampX][lampY] = HOUSE_LAMP;

	}
}


void placeBombs(Matrixt2d& matrix , int difficulty) {
	int apparentMatrixSize = matrix.size() - 2;
	int bombsQuantity = difficulty;

	for (int i = 0u; i < (bombsQuantity); i++) {

		int bombX = randIntBetween(1, apparentMatrixSize);
		int bombY = randIntBetween(1, apparentMatrixSize);

		if ((matrix[bombX][bombY] == HOUSE_BOMB) || matrix[bombX][bombY] == HOUSE_LAMP) {
			i--;
			continue;
		}
		else matrix[bombX][bombY] = HOUSE_BOMB;

	}
}
	




void placeBombCounters(Matrixt2d& matrix) {
	int rows = matrix.size();
	int cols = matrix[0].size();
	int apparentRows = rows - 2;
	int apparentCols = cols - 2;

	auto analyzeNearBombs = [](Matrixt2d& matrix, int row, int col) {
		int n = 0;

		for (int k = -1; k <= 1; k++) {
			for (int l = -1; l <= 1; l++) {
				int loopRow = row + k;
				int loopCol = col + l;
				if (matrix[loopRow][loopCol] == HOUSE_BOMB) n++;
			}
		}

		return n;
		};

	for (int row = 1u; row <= (apparentRows); row++)
		for (int col = 1u; col <= (apparentCols); col++) {
			if ((matrix[row][col] == HOUSE_BOMB ) || (matrix[row][col] == HOUSE_LAMP)) continue;
			matrix[row][col] = analyzeNearBombs(matrix, row, col);
		}

}



void lampAction(Matrixt2d& matrix, Matrixt2d& sMatrix ,int x ,int  y) {
	sMatrix[x][y] = HOUSE_LAMP;

	int rows = matrix.size();
	int cols = matrix[0].size();

	int apparentRows = rows - 2;
	int apparentCols = cols - 2;

	int n = 0;

		for (int k = -10; k <= 10; k++) {
			for (int l = -10; l <= 10; l++) {
				int loopX = x + k;
				int loopY = y + l;
				if (!availableSpace((loopX), (loopY), rows, cols) || sMatrix[loopX][loopY] == HOUSE_COVERED_BOMB) continue;
				else if (matrix[loopX][loopY] == HOUSE_BOMB) {
					sMatrix[loopX][loopY] = HOUSE_COVERED_BOMB;
					n++;
					if (n > 0) break;
				
				}
			}
			if (n > 0) break;
		}


}




void eventButtonpressed(Matrixt2d& sMatrix, Matrixt2d& matrix, Event event, int x, int y) {
	int rows = matrix.size();
	int cols = matrix[0].size();

	if (event.type == Event::MouseButtonPressed) {
		if (availableSpace(x, y, rows, cols)) {
			if (event.key.code == Mouse::Left) {
				if (matrix[x][y] == HOUSE_BOMB) gameOver(sMatrix, matrix);
				else if (sMatrix[x][y] != matrix[x][y]) {
					if (matrix[x][y] == HOUSE_LAMP) lampAction(matrix, sMatrix, x, y);
						std::vector<std::vector<int>> reveal(rows, std::vector<int>(cols));
						analyzeEmptySpaces(reveal, sMatrix, matrix, x, y);
					
				}

				
			}
			else if (event.key.code == Mouse::Right) {
				if (sMatrix[x][y] == 10) sMatrix[x][y] = FLAG;
				else if (sMatrix[x][y] == FLAG) sMatrix[x][y] = HOUSE_COVERED;
			}
		}
	}
}


bool availableSpace(int x, int y, int rows, int cols) {
	if ((x > 0 && x <= (cols - 2)) && (y > 0 && y <= (rows - 2))) return true;
	else return false;


}



void loopEdges(Matrixt2d& reveal, Matrixt2d& sMatrix, Matrixt2d& matrix, int x, int y) {
	int rows = matrix.size();
	int cols = matrix[0].size();
	
	for (int k = -1; k <= 1; k++) {
		for (int l = -1; l <= 1; l++) {
			int loopX = x + k;
			int loopY = y + l;
			analyzeEmptySpaces(reveal, sMatrix, matrix, loopX, loopY);
			l++;
		}
		k++;
	}

}


void analyzeEmptySpaces(Matrixt2d& reveal, Matrixt2d& sMatrix, Matrixt2d& matrix, int x, int y) {
	int rows = matrix.size();
	int cols = matrix[0].size();

	if (!(availableSpace(x, y, rows, cols)) || (reveal[x][y] == 1) || matrix[x][y] == HOUSE_BOMB) {
		return;
	}


	if (matrix[x][y] > HOUSE_EMPTY && matrix[x][y] < HOUSE_BOMB) {
		sMatrix[x][y] = matrix[x][y];
		reveal[x][y] = 1;

		//Analisa as casas laterais das com números , se a casa vizinha já tiver sido contada e for vazia , analiza as casas diagonais da mesma
		for (int k = -1; k <= 1; k++) {
			int loopX = x + k;
			int loopY = y + k;

			if (availableSpace(loopX, y, rows, cols) && (reveal[loopX][y] == 1) && (matrix[loopX][y] == HOUSE_EMPTY)) loopEdges(reveal, sMatrix, matrix, loopX, y);
			if (availableSpace(x, loopY, rows, cols) && (reveal[x][loopY] == 1) && (matrix[x][loopY] == HOUSE_EMPTY)) loopEdges(reveal, sMatrix, matrix, x , loopY);

			k++;
		}
	
		return;
	}



	if ((matrix[x][y] == HOUSE_LAMP)) {
		if (sMatrix[x][y] != HOUSE_LAMP) lampAction(matrix, sMatrix, x, y);
	}

	reveal[x][y] = 1;

	if (matrix[x][y] != HOUSE_BOMB) {
		sMatrix[x][y] = matrix[x][y];
		
		//Faz um Flood fill
		analyzeEmptySpaces(reveal, sMatrix, matrix, x - 1, y);
		analyzeEmptySpaces(reveal, sMatrix, matrix, x + 1, y);
		analyzeEmptySpaces(reveal, sMatrix, matrix, x, y - 1);
		analyzeEmptySpaces(reveal, sMatrix, matrix, x, y + 1);


	}
}


void gameOver(Matrixt2d& sMatrix, Matrixt2d& matrix) {
	int rows = matrix.size();
	int cols = matrix[0].size();

	int apparentRows = rows - 2;
	int apparentCols = cols - 2;
	
	for (int row = 1; (row <= apparentRows); row++) {
		for (int col = 1; col <= (apparentCols); col++) {
			sMatrix[row][col] = matrix[row][col];
		}
	}
}

void fieldDraw(Matrixt2d& sMatrix, Matrixt2d matrix, Sprite sprite, RenderWindow& app, int spriteSize) {
	int rows = matrix.size();
	int cols = matrix[0].size();

	int apparentRows = rows - 2;
	int apparentCols = cols - 2;

	for (int row = 1; (row <= apparentRows); row++) {
		for (int col = 1; col <= (apparentCols); col++) {
			sprite.setTextureRect(IntRect(sMatrix[row][col] * spriteSize, 0, spriteSize, spriteSize));
			sprite.setPosition(float(row * spriteSize), float(col * spriteSize));
			app.draw(sprite);
		}
	}

}