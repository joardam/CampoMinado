#include <vector>
#include <SFML/Graphics.hpp>
#include <time.h>



using namespace sf;

using Matrixt2d = std::vector<std::vector<int>>;
void fillMatrix(Matrixt2d& matrix ,int size) {
	for (int i = 1; i <= size; i++){
		for (int j = 1; j <= size; j++) {
			matrix[i][j] = 10;
		}
	}
}



int main()
{
	srand(time(0));
	

	RenderWindow app(VideoMode(400, 400), "Campo Minado");

	constexpr auto SPRITE_SIZE = 32;
	
	// Note que Lines
	int rows= 12;
	int cols = 12;

	//Cria matrizes
	std::vector<std::vector<int>> grid(rows, std::vector<int>(cols));
	std::vector<std::vector<int>> sgrid(rows, std::vector<int>(cols));


	Texture texture;
	texture.loadFromFile("images/tiles.jpg");
	Sprite sprite(texture);
	
	fillMatrix(sgrid, rows - 2);
	fillMatrix(grid, cols -2);

	for (int i = 1; i <= 10; i++)
		for (int j = 1; j <= 10; j++) {
			if (rand() % 5 == 0) grid[i][j] = 9;
			else grid[i][j] = 0;
		}

	for (int i = 1; i <= 10; i++)
		for (int j = 1; j <= 10; j++) {
			int n = 0;
			if (grid[i][j] == 9) continue;
			
			for (int k = -1; k <= 1; k++) {
				for (int l = -1; l <= 1; l++) {
					if (grid[i + k][j + l] == 9) n++;
				
				}
			}
			

			grid[i][j] = n;
		}

	

	while (app.isOpen())
	{
		Vector2i pos = Mouse::getPosition(app);
		int x = pos.x / SPRITE_SIZE;
		int y = pos.y / SPRITE_SIZE;

		Event event;
		bool eventMouseLeft = false;
		bool changegrid = false;
		while (app.pollEvent(event))
		{
			if (event.type == Event::Closed)
				app.close();

			if (event.type == Event::MouseButtonPressed){
				if (x >= 1 && x <= 10 && y >= 1 && y <= 10) {
					if (event.key.code == Mouse::Left) {
						eventMouseLeft = true;
						if (sgrid[x][y] != grid[x][y]) {
							changegrid = true;
							sgrid[x][y] = grid[x][y];
						}
					}
					else if (event.key.code == Mouse::Right) {
						if (sgrid[x][y] == 10) sgrid[x][y] = 11;
						else if (sgrid[x][y] == 11) sgrid[x][y] = 10;
					}
				}
			}
				


		}
		app.clear(Color::White);
		for (int i = 1; i <= 10; i++)
			for (int j = 1; j <= 10; j++) {

				if (eventMouseLeft) {
					if (x >= 1 && x <= 10 && y >= 1 && y <= 10) {
						if (sgrid[x][y] == 9) sgrid[i][j] = grid[i][j];
						if (sgrid[x][y] == 0 && changegrid == true) {
								
							for (int k = -1; k <= 1; k++) {
								for (int l = -1; l <= 1; l++) {
									if (grid[x + k][y + l] != 9) sgrid[x + k][y + l] = grid[x + k][y + l];

								}
							}

	
								
						}
					}
				}


				sprite.setTextureRect(IntRect(sgrid[i][j] * SPRITE_SIZE, 0, SPRITE_SIZE, SPRITE_SIZE));
				sprite.setPosition(float(i * SPRITE_SIZE), float(j * SPRITE_SIZE));
				app.draw(sprite);
			}

	

		app.display();
	}

}

