#ifndef GAMEOVERSCREEN_H
#define GAMEOVERSCREEN_H

#include <SFML/Graphics.hpp>
#include "ResourcePath.h"
#include "main.h"

void GameOver_Mode(sf::RenderWindow& window, sf::Event event, typeName &gameState, sf::Font font)
{
	sf::String sentence;
	sf::Text gameoverText(sentence, font, 77);
	gameoverText.setString("GAME OVER!");
	gameoverText.setPosition(120, 100);
	gameoverText.setColor(sf::Color(250, 218, 94)); //royal yellow

	sf::Text retryMessage("press P to play again", font, 50);
	retryMessage.setPosition(120, 250);
	retryMessage.setColor(sf::Color(250, 218, 94)); //royal yellow

	sf::Text creditMessage("press C to view credit", font, 50);
	creditMessage.setPosition(90, 350);
	creditMessage.setColor(sf::Color(250, 218, 94));

	sf::Texture backgroundTexture;
	backgroundTexture.loadFromFile(resourcePath() + "assets/background.png");

	sf::Sprite backgroundSprite(backgroundTexture);
	
	while (window.isOpen() && gameState == GAME_OVER)
	{
		handleEvent(window, event);

		window.clear();
		window.draw(backgroundSprite);
		window.draw(gameoverText);
		window.draw(retryMessage);
		window.draw(creditMessage);
		window.display();
	}
}

#endif