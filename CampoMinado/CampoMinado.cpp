#include <vector>
#include <SFML/Graphics.hpp>
#include <time.h>
#include "Gamelogic.h"




using namespace sf;

int main()
{
	srand(static_cast<unsigned int>(time(0)));
	
	int rows = 12;
	int cols = 12;
	int spriteSize = 32;

	unsigned int videoSizex = static_cast<unsigned int>(rows * spriteSize);
	unsigned int videoSizey = static_cast<unsigned int>(cols * spriteSize);

	sf::RenderWindow app(VideoMode(videoSizex, videoSizey), "Campo Minado" , Style::Close);


	//Cria matrizes
	std::vector<std::vector<int>> grid(rows, std::vector<int>(cols));
	std::vector<std::vector<int>> sgrid(rows, std::vector<int>(cols));


	Texture texture;
	texture.loadFromFile("images/tiles.jpg");
	Sprite sprite(texture);
	
	fillMatrix(sgrid, rows - 2);
	fillMatrix(grid, cols -2);

	placeBombs(grid);

	placeBombCounters(grid);

	

	while (app.isOpen())
	{
		Vector2i pos = Mouse::getPosition(app);
		int x = pos.x / spriteSize;
		int y = pos.y / spriteSize;

		Event event;
		bool eventMouseLeft = false;
		bool changeGrid = false;
		
		while (app.pollEvent(event))
		{
			if (event.type == Event::Closed)
				app.close();

			eventButtonpressed(sgrid, grid, event, eventMouseLeft, changeGrid , x, y);
		}
		
		app.clear(Color::White);
		actionConsequece(sgrid, grid, eventMouseLeft, changeGrid, x, y, sprite, app , spriteSize);

	

		app.display();
	}

}

