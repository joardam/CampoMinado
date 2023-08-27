#include <SFML/Graphics.hpp>
#include <time.h>

using namespace sf;


int main()
{
	srand(time(0));
	

	RenderWindow app(VideoMode(400, 400), "Campo Minado");

	constexpr auto SPRITE_SIZE = 32;
	int grid[12][12];
	int sgrid[12][12];

	Texture texture;
	texture.loadFromFile("images/tiles.jpg");
	Sprite sprite(texture);

	for (int i = 1; i <= 10; i++)
		for (int j = 1; j <= 10; j++) {
			sgrid[i][j] = 10;

			if (rand() % 5 == 0) grid[i][j] = 9;
			else grid[i][j] = 0;
		}

	for (int i = 1; i <= 10; i++)
		for (int j = 1; j <= 10; j++) {
			int n = 0;
			if (grid[i][j] == 9) continue;

			if (grid[i + 1][j] == 9) n++;
			if (grid[i - 1][j] == 9) n++;
			if (grid[i][j + 1] == 9) n++;
			if (grid[i][j - 1] == 9) n++;

			if (grid[i + 1][j + 1] == 9) n++;
			if (grid[i + 1][j - 1] == 9) n++;
			if (grid[i - 1][j + 1] == 9) n++;
			if (grid[i - 1][j - 1] == 9) n++;

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

				for (int j = 1; j <= 10; j++) {
					
					if (eventMouseLeft) {
						if (x >= 1 && x <= 10 && y >= 1 && y <= 10) {
							if (sgrid[x][y] == 9) sgrid[i][j] = grid[i][j];
							if (sgrid[x][y] == 0 && changegrid == true) {
		
								if (grid[x + 1][y] != 9) sgrid[x + 1][y] = grid[x + 1][y]; //Quando for colocar poderes , talvez sejam necessárias mudanças
								if (grid[x - 1][y] != 9) sgrid[x - 1][y] = grid[x - 1][y];
								if (grid[x][y + 1] != 9) sgrid[x][y + 1] = grid[x][y + 1];
								if (grid[x][y - 1] != 9) sgrid[x][y - 1] = grid[x][y - 1];

								if (grid[x + 1][y + 1] != 9) sgrid[x + 1][y + 1] = grid[x + 1][y + 1];
								if (grid[x + 1][y - 1] != 9) sgrid[x + 1][y - 1] = grid[x + 1][y - 1];
								if (grid[x - 1][y + 1] != 9) sgrid[x - 1][y + 1] = grid[x - 1][y + 1];
								if (grid[x - 1][y - 1] != 9) sgrid[x - 1][y - 1] = grid[x - 1][y - 1];
								
								
							}
						}
					}


					sprite.setTextureRect(IntRect(sgrid[i][j] * SPRITE_SIZE, 0, SPRITE_SIZE, SPRITE_SIZE));
					sprite.setPosition(i * SPRITE_SIZE, j * SPRITE_SIZE);
					app.draw(sprite);
				}
			}
	

		app.display();
	}

}

