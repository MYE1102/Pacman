#ifndef MAIN_H
#define MAIN_H

const int ROW = 8;
const int COL = 13;

enum typeName { OPENING, HOW_TO, PLAY, VICTORY, GAME_OVER, CREDIT } gameState;

void handleEvent(sf::RenderWindow& window, sf::Event &event)
{
	while (window.pollEvent(event))
	{
		if (event.type == sf::Event::Closed)
			window.close();
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::P))
			gameState = PLAY;
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::C))
			gameState = CREDIT;
	}
}


#endif