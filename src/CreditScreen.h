#ifndef CREDITSCREEN_H
#define CREDITSCREEN_H

#include <SFML/Graphics.hpp>
#include "ResourcePath.h"
#include "main.h"
#include <iostream>

void Credit_Mode(sf::RenderWindow& window, sf::Event event, typeName &gameState,sf::Font font)
{
	sf::Text title("Pacman", font, 99);
	title.setPosition(210, 50);
	title.setColor(sf::Color(250, 218, 94));

	sf::Text prompt("Developers: ", font, 32);
	prompt.setPosition(120, 180);
	prompt.setColor(sf::Color(250, 218, 94));

	sf::Text names("Ye-Eun Myung         Nhat Trinh\n"
		           "Abraham Kong         Vivian Wang\n"
		           "Cecilia Wu", font, 32);
	names.setPosition(120, 240);
	names.setColor(sf::Color(250, 218, 94));

	sf::Text startMessage("press P to play again", font, 50);
	startMessage.setPosition(120, 380);
	startMessage.setColor(sf::Color(250, 218, 94));

	sf::Texture backgroundTexture;
	backgroundTexture.loadFromFile(resourcePath() + "assets/background.png");

	sf::Sprite backgroundSprite(backgroundTexture);

	window.clear();
	window.draw(backgroundSprite);
	window.draw(title);
	window.draw(prompt);
	window.draw(names);
	window.draw(startMessage);
	window.display();
	
	handleEvent(window, event);
}
#endif