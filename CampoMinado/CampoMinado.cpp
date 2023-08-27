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
		Event event;
		while (app.pollEvent(event))
		{
			if (event.type == Event::Closed)
				app.close();

		}
		app.clear(Color::White);

		for (int i = 1; i <= 10; i++)
			for (int j = 1; j <= 10; j++) {

				for (int j = 1; j <= 10; j++) {

					sgrid[i][j] = grid[i][j];



					sprite.setTextureRect(IntRect(sgrid[i][j] * SPRITE_SIZE, 0, SPRITE_SIZE, SPRITE_SIZE));
					sprite.setPosition(i * SPRITE_SIZE, j * SPRITE_SIZE);
					app.draw(sprite);
				}
			}
	

		app.display();
	}

}

