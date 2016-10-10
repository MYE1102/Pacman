#ifndef OPENINGSCREEN_H
#define OPENINGSCREEN_H

#include <SFML/Graphics.hpp>
#include "ResourcePath.h"
#include "main.h"
#include <iostream>
void Opening_Mode(sf::RenderWindow& window, sf::Event event, sf::Font font)
{
	sf::Text text1("Pacman", font, 99);
	text1.setPosition(210, 100);
	text1.setColor(sf::Color(250, 218, 94)); //royal yellow

	sf::Text startMessage("press P to play", font, 50);
	startMessage.setPosition(190, 250);
	startMessage.setColor(sf::Color(250, 218, 94));

	sf::Text creditMessage("press C to view credit", font, 50);
	creditMessage.setPosition(90, 350);
	creditMessage.setColor(sf::Color(250, 218, 94));

	sf::Texture backgroundTexture;
	backgroundTexture.loadFromFile(resourcePath() + "assets/background.png");

	sf::Sprite backgroundSprite(backgroundTexture);
	
	window.clear();
	window.draw(backgroundSprite);
	window.draw(text1);
	window.draw(startMessage);
	window.draw(creditMessage);
	window.display();

	handleEvent(window, event);
}
#endif