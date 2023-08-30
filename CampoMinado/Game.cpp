#include <vector>
#include <SFML/Graphics.hpp>
#include <time.h>
#include "GameFunctions.h"





using namespace sf;

int startGame()
{
	srand(3u);

	int rows = 18;
	int cols = 18;
	int spriteSize = 32;

	unsigned int videoSizex = static_cast<unsigned int>(rows * spriteSize);
	unsigned int videoSizey = static_cast<unsigned int>(cols * spriteSize);

	sf::RenderWindow app(VideoMode(videoSizex, videoSizey), "Campo Minado", Style::Close);


	//Cria matrizes
	std::vector<std::vector<int>> matrix(rows, std::vector<int>(cols));
	std::vector<std::vector<int>> sMatrix(rows, std::vector<int>(cols));


	Texture texture;
	texture.loadFromFile("images/newsprites.jpg");
	Sprite sprite(texture);

	fillMatrix(sMatrix, rows - 2 ,cols -2);
	fillMatrix(matrix, rows -2 , cols - 2);

	placeBonusLamp(matrix);

	placeBombs(matrix);
	placeBombELampCounters(matrix);




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

			eventButtonpressed(sMatrix, matrix, event, x, y);
		}

		app.clear(Color::White);
		fieldDraw(sMatrix, matrix, sprite, app, spriteSize);



		app.display();
	}
	return 0;
}
