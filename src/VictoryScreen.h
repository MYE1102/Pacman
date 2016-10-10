#ifndef VICTORY_H
#define VICTORY_H

#include <SFML/Graphics.hpp>
#include "ResourcePath.h"
#include "main.h"

void drawVictory(sf::RenderWindow& window, sf::Event event, sf::Font font)
{
	window.clear();
	sf::String sentence;
	sf::Text victoryText(sentence, font, 66);
	victoryText.setString("VICTORY");
	victoryText.setColor(sf::Color::White);
	victoryText.setOrigin(160, 32);
	victoryText.setPosition(350, 300);

	sf::Text retryMessage("press P to play again", font, 33);
	retryMessage.setPosition(280, 350);

	sf::Text creditMessage("press C to view credit", font, 33);
	creditMessage.setPosition(280, 400);
	window.draw(victoryText);
	window.draw(retryMessage);
	window.display();
}
void Victory_Mode(sf::RenderWindow& window, sf::Event event, typeName &gameState, sf::Font font)
{
	drawVictory(window, event, font);
	handleEvent(window, event);
}
#endif