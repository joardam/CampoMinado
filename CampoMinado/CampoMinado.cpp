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
		}

	while (app.isOpen())
	{
		Event eve;
		while (app.pollEvent(eve))
		{
			if (eve.type == Event::Closed)
				app.close();

		}
		app.clear(Color::White);

		for (int i = 1; i <= 10; i++)
			for (int j = 1; j <= 10; j++) {
				sprite.setTextureRect(IntRect(sgrid[i][j] * SPRITE_SIZE, 0, SPRITE_SIZE, SPRITE_SIZE));
				sprite.setPosition(i * SPRITE_SIZE, j * SPRITE_SIZE);
				app.draw(sprite);
			}
	

		app.display();
	}

}

