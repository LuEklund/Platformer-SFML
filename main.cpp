#include "Game.h"

int main()
{
    sf::RenderWindow window(sf::VideoMode(600, 600), "2d-platformer-rogue");
    sf::Event event;

	// window.setFramerateLimit(15);

	Game game(window);
	if (!game.initGame())
		return (-1);

    while (window.isOpen())
    {
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
			if (event.type == sf::Event::KeyPressed)
				game.isKeyPressed(event.key.code);
			if (event.type == sf::Event::MouseButtonReleased)
				game.isMouseButtonReleased(event.mouseButton.button);
        }
		game.update();
		window.clear(sf::Color::Blue);
		window.draw(game);
		window.display();
    }
}
