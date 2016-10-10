//This Draw.h contains most of the draw functions need for the Play_Mode function
#ifndef DRAW_H
#define DRAW_H

#include <SFML/Graphics.hpp>

void draw(sf::RenderWindow& window, sf::Sprite pacmanSprite, sf::Sprite monsterSprite, sf::Sprite monsterSprite2, int counter)
{
	window.draw(pacmanSprite);
	window.draw(monsterSprite);
	window.draw(monsterSprite2);
}

void drawHeart(sf::RenderWindow& window, sf::Sprite* heartArr, sf::Texture heartTexture, int numHeart)
{
	int i = 0;
	for (int num = 0; num < numHeart; num++)
	{
		heartArr[i] = sf::Sprite(heartTexture);
		heartArr[i].setPosition(32 * (float)i, 542);
		window.draw(heartArr[i]);
		i++;
	}
}

void drawWall(sf::RenderWindow& window, bool arr[][COL], sf::Sprite *tileArr, sf::Texture wallTexture)
{
	int i = 0;

	for (int r = 0; r < ROW; r++)
	{
		for (int c = 0; c < COL; c++)
		{
			if (arr[r][c] == true)
			{
				tileArr[i] = sf::Sprite(wallTexture);
				tileArr[i].setPosition((float)c * 64, (float)r * 64);
				window.draw(tileArr[i]);
				i++;
			}
		}
	}
}

void drawCandy(sf::RenderWindow& window, bool arr[][COL], sf::Sprite *candyArr, sf::Texture candyTexture)
{
	int i = 0;

	for (int r = 0; r < ROW; r++)
	{
		for (int c = 1; c < COL; c++)
		{
			if (arr[r][c] == true)
			{
				candyArr[i] = sf::Sprite(candyTexture);
				candyArr[i].setPosition(((float)c * 64.f) + 32.f, ((float)r * 64.f) + 32.f); // c = x && r = y
				candyArr[i].setOrigin(10.0, 10.0);
				window.draw(candyArr[i]);
				i++;
			}
		}
	}
}
#endif