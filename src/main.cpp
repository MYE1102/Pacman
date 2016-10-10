
#include <SFML/Graphics.hpp>
#include <cstdlib> //for rand
#include <iostream>
#include <sstream> //converttostring

#include "ResourcePath.h"
#include "Overlap.h"
#include "main.h"
#include "OpeningScreen.h"
#include "GameoverScreen.h"
#include "VictoryScreen.h"
#include "CreditScreen.h"
#include "Draw.h"

void findCandy(sf::Vector2f candyPosition, sf::Sprite *candyArr, bool arr[][COL], int &numcandy, int &score);
bool handleWallCollision(sf::Sprite *tileArr, sf::Sprite Sprite, int counter);
void MonsterUpdate(sf::Sprite& monsterSprite, sf::Sprite* tileArr, int numtile, int& MonsterDirection, sf::Time& time, sf::Clock& clock, int speed);
sf::Vector2f update(sf::Sprite* candyArr, sf::Sprite *tileArr, sf::Sprite& PacmanSprite, sf::Sprite& monsterSprite, sf::Sprite& monsterSprite2,
	sf::Event event, int numtile, int numCandy, int& MonsterDirection1, int& MonsterDirection2, int& numHeart, sf::Time& time, sf::Time &totalTime, sf::Clock& clock);
void Play_Mode(sf::RenderWindow& window, sf::Event event, sf::Texture candyTexture, sf::Texture wallTexture, sf::Sprite *tileArray,
	sf::Texture heartTexture, sf::Sprite& pacmanSprite, sf::Sprite& monsterSprite, sf::Sprite& monsterSprite2, int numtile,
	int map[][COL], bool boolwall[][COL], sf::Clock& clock, sf::Text& scoreText, sf::Text info);

int main()
{
	//need rand() for random direction change for monsterSprites
	srand((unsigned int)time(NULL));

	sf::RenderWindow window(sf::VideoMode(832, 576), "SFML Works!");
	window.setVerticalSyncEnabled(true);

	//Texture for walls
	sf::Texture wallTexture;
	wallTexture.loadFromFile(resourcePath() + "assets/wall.png");

	//Texture and Sprite for pacman
	sf::Texture pacmanTexture;
	pacmanTexture.loadFromFile(resourcePath() + "assets/pacman.png");

	sf::Sprite pacmanSprite(pacmanTexture);
	pacmanSprite.setScale(1.65f, 1.65f); //original size is 32*32
	pacmanSprite.setOrigin(18, 18);

	//Texture for candy
	sf::Texture candyTexture;
	candyTexture.loadFromFile(resourcePath() + "assets/candy.png");

	//Texture and Sprites for 2 monsters 
	sf::Texture monsterTexture;
	monsterTexture.loadFromFile(resourcePath() + "assets/monster.png");

	sf::Sprite monsterSprite(monsterTexture);
	monsterSprite.setScale(1.69f, 1.69f);
	monsterSprite.setOrigin(18, 18);
	monsterSprite.setPosition(36 * 10 - 8, monsterSprite.getLocalBounds().height * 2 + 25);

	sf::Sprite monsterSprite2(monsterTexture);
	monsterSprite2.setScale(1.69f, 1.69f);
	monsterSprite2.setOrigin(18, 18);
	monsterSprite2.setPosition((36 * 10) - 8, (36 * 10) - 8);

	//Texture for hearts
	sf::Texture heartTexture;
	heartTexture.loadFromFile(resourcePath() + "assets/heart.png");
	
	//Font that is used on this game
	sf::Font font;
	if (!font.loadFromFile(resourcePath() + "assets/SNAP.TTF"))
	{
		std::cout << "CANNOT OPEN THE FILE." << std::endl;
	}

	//To show the current points the user have
	sf::String score;
	sf::Text scoreText(score, font, 45);
	scoreText.setColor(sf::Color::White);
	scoreText.setPosition(750, 516);

	//To prompt the user that the score is score
	sf::String words;
	sf::Text info(words, font, 40);
	info.setString("SCORE: ");
	info.setColor(sf::Color::White);
	info.setPosition(560, 516);
	
	// map array. This is the master map of the game.
	int map[ROW][COL] =
	{
		{ 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1 },
		{ 1, 0, 0, 0, 0, 0, 1, 0, 0, 0, 1, 0, 1 },
		{ 1, 1, 1, 0, 1, 0, 1, 0, 1, 0, 0, 0, 1 },
		{ 1, 0, 0, 0, 1, 0, 0, 0, 0, 0, 1, 1, 1 },
		{ 1, 0, 1, 1, 1, 1, 1, 0, 1, 0, 0, 0, 1 },
		{ 1, 0, 0, 0, 1, 0, 0, 0, 1, 1, 1, 0, 1 },
		{ 1, 0, 1, 0, 0, 0, 1, 0, 0, 0, 0, 0, 1 },
		{ 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1 }
	};

	//bool array for the map
	int numtile = 0;
	bool wall[ROW][COL];
	for (int r = 0; r < ROW; r++)
	{
		for (int c = 0; c < COL; c++)
		{
			if (map[r][c] == 1)
			{
				wall[r][c] = true; // there is a wall
				numtile++;
			}
			if (map[r][c] == 0)
				wall[r][c] = false; // blank
		}
	}
	//Dynamic Allocation of the wall (I call this tile)
	//so wall is a array of boolian values, and the tile is array of Sprites
	sf::Sprite *tileArray = new sf::Sprite[numtile];

	//set gameState to OPENING
	gameState = OPENING;

	//Clock is need to make monsters more random
	sf::Clock clock; 

	//main loop
	while (window.isOpen())
	{
		sf::Event event;
		handleEvent(window, event);

		switch (gameState)
		{
		case OPENING:
			Opening_Mode(window, event, font);
			break;
		case PLAY:
			Play_Mode(window, event, candyTexture, wallTexture, tileArray, heartTexture, pacmanSprite, monsterSprite, monsterSprite2,
				numtile, map, wall, clock, scoreText, info);
			break;
		case VICTORY:
			Victory_Mode(window, event, gameState, font);
		case GAME_OVER:
			GameOver_Mode(window, event, gameState, font);
			break;
		case CREDIT:
			Credit_Mode(window, event, gameState, font);
			break;
		}
	}

	delete[] tileArray;
	
	return 0;
}

/*******************************************************************
Definition of findCandy function

This function finds the row and col for the overlapped candy sprite.
When the candy location is found, Then changes the candy array of 
boolian values to false and decrements the numcandy and increments 
the score.
********************************************************************/
void findCandy(sf::Vector2f candyPosition, sf::Sprite *candyArr, bool arr[][COL], int &numcandy, int &score)
{
	int col = (int)candyPosition.x;
	int row = (int)candyPosition.y;

	col = (col - 32) / 64;
	row = (row - 32) / 64;

	if (row != 0 && col != 0)
	{
		arr[row][col] = false;
		numcandy--;
		score++;
	}


}
/*******************************************************************
Definition of handleWallCollision function

This function finds if the two sprites are overlapped. If there is
an overlap, then it returns true, otherwise false.
********************************************************************/
bool handleWallCollision(sf::Sprite *tileArr, sf::Sprite Sprite, int counter)
{
	for (int i = 0; i < counter; i++)
	{
		if (overlap(tileArr[i], Sprite))
			return true; // there is collision
	}

	return false;
}

/*******************************************************************
Definition of MonsterUpdate function

This function updates the monster Sprite. Every 3 seconds, the 
monster Sprite is given new random direction and when the monster
is overlapped with wall/tile, it is also given the new direction.
********************************************************************/
void MonsterUpdate(sf::Sprite& monsterSprite, sf::Sprite* tileArr, int numtile, int& MonsterDirection, sf::Time& time, sf::Clock& clock, int speed)
{
	sf::Vector2f currMonsPos = monsterSprite.getPosition();
	bool wallMonsterCollision = false;
	float Speed = (float)speed;
	//changes direction every 3 seconds
	if (time.asSeconds() < 3)
	{
		if (MonsterDirection == 0)
		{
			monsterSprite.move(-Speed, 0.0);
		}
		else if (MonsterDirection == 1)			
		{
			monsterSprite.move(Speed, 0.0);
		
		}
		else if (MonsterDirection == 2)
		{
			monsterSprite.move(0.0, -Speed);
		}
		else if (MonsterDirection == 3)
		{
			monsterSprite.move(0.0, Speed);
		}
	}
	//detects overlap
	wallMonsterCollision = handleWallCollision(tileArr, monsterSprite, numtile);
	//if there is an overlap then gives new direction to monster Sprite
	if (wallMonsterCollision)
	{
		monsterSprite.setPosition(currMonsPos);
		int newMonsterDirection = rand() % 4;
		while (newMonsterDirection == MonsterDirection)
		{
			newMonsterDirection = rand() % 4;
		}

		MonsterDirection = newMonsterDirection;
	}
}

/*******************************************************************
Definition of update function

This function updates the whole game. The direction of Pacman Sprite,
two monster Sprites, and the number of candies left. After this
function detects that the Pacman Sprite has overlapped with certain
candy Sprite, then it returns the position of that candy Sprite.
Otherwise, it returns (0,0) where there is no candy Sprite.
********************************************************************/
sf::Vector2f update(sf::Sprite* candyArr, sf::Sprite *tileArr, sf::Sprite& PacmanSprite, sf::Sprite& monsterSprite, sf::Sprite& monsterSprite2,
	sf::Event event, int numtile, int numCandy, int& MonsterDirection1, int& MonsterDirection2, int& numHeart, sf::Time& time, sf::Time& totalTime, sf::Clock& clock)
{
	//get the current position of the pacman so when it overlap, it can go back to current position
	sf::Vector2f currPacPos = PacmanSprite.getPosition();

	if (event.key.code == sf::Keyboard::Left) //keeps it moving even though key is not pressed
	{
		PacmanSprite.setRotation(180);
		PacmanSprite.move(-2, 0);
	}
	else if ((event.key.code == sf::Keyboard::Right))
	{
		PacmanSprite.setRotation(0);
		PacmanSprite.move(2, 0);
	}
	else if ((event.key.code == sf::Keyboard::Up))
	{
		PacmanSprite.setRotation(270);
		PacmanSprite.move(0, -2);
	}
	else if ((event.key.code == sf::Keyboard::Down))
	{
		PacmanSprite.setRotation(90);
		PacmanSprite.move(0, 2);
	}

	// if pacman hits a wall, set position back to currPos
	bool wallPacmanCollision = false;
	wallPacmanCollision = handleWallCollision(tileArr, PacmanSprite, numtile);

	if (wallPacmanCollision)
	{
		PacmanSprite.setPosition(currPacPos);
		sf::Vector2f currMonsPos = monsterSprite.getPosition();
	}
	

	//update monsterSprite and monsterSprite1. They are both AI
	MonsterUpdate(monsterSprite, tileArr, numtile, MonsterDirection1, time, clock, 2);
	MonsterUpdate(monsterSprite2, tileArr, numtile, MonsterDirection2, time, clock, 2);
	
	//std:: cout << time.asSeconds() << std::endl; //to check time. (not needed)

	//when time is more than 3 seconds, then restart the clock
	if (time.asSeconds() > 3.00)
	{
		totalTime += clock.getElapsedTime();
		clock.restart();
		MonsterDirection1 = rand() % 4;
		MonsterDirection2 = rand() % 4;
	}

	//if pacman and candy overlaps that candy disappears
	for (int x = 0; x < numCandy; x++)
	{
		if (overlap(PacmanSprite, candyArr[x]))
		{
			sf::Vector2f candyposition = candyArr[x].getPosition();
			return candyposition;
		}
	}

	//when pacman overlap with a monster, heart decreases
	if (overlap(PacmanSprite, monsterSprite))
	{
		PacmanSprite.setPosition(64 + 34, 250 + 36);
		numHeart--;
	}
	if (overlap(PacmanSprite, monsterSprite2))
	{
		PacmanSprite.setPosition(64 + 34, 250 + 36);
		numHeart--;
	}

	//If there is no overlap candy, then return sf::Vector(0,0) so it will not remove the candy
	sf::Vector2f noOverlap;
	noOverlap.x = 0;
	noOverlap.y = 0;
	return noOverlap; // candy is there
}

/*******************************************************************
Definition of Play_Mode function

This function starts the game. Every time this function is called,
it is going to create an array of candy boolian value from master 
map, array of candy Sprites, array of heart Sprites, and resets 
the position of pacman Sprite and position and direction for two 
monster Sprites. Inside the play mode loop, when numcandy reaches
0, then the gameState changes to VICTORY, when numhearts reaches 0,
then the gameState changes to GAME_OVER.
********************************************************************/
void Play_Mode(sf::RenderWindow& window, sf::Event event, sf::Texture candyTexture, sf::Texture wallTexture, sf::Sprite *tileArray,
	sf::Texture heartTexture, sf::Sprite& pacmanSprite, sf::Sprite& monsterSprite, sf::Sprite& monsterSprite2, int numtile, 
	int map[][COL], bool boolwall[][COL], sf::Clock& clock, sf::Text& scoreText, sf::Text info)
{
	//need to set boolcandy here so when everytime the user choses Play_Mode, the boolCandy reset to original
	int numcandy = 0;
	bool boolcandy[ROW][COL];
	for (int r = 0; r < ROW; r++)
	{
		for (int c = 0; c < COL; c++)
		{
			if (map[r][c] == 0)
			{
				boolcandy[r][c] = true; // there is a candy	
				numcandy++;
			}
			if (map[r][c] == 1)
				boolcandy[r][c] = false; // blank
		}
	}

	sf::Sprite*candyArray = new sf::Sprite[numcandy];

	//reset everything for the new game
	int numHeart = 3;
	sf::Sprite*heartArray = new sf::Sprite[numHeart];

	pacmanSprite.setPosition(64 + 34, 250 + 36);
	monsterSprite.setPosition(36 * 10 - 8, monsterSprite.getLocalBounds().height * 2 + 25);
	monsterSprite2.setPosition((36 * 10) - 8, (36 * 10) - 8);

	int MonsterDirection1 = rand() % 4;
	int MonsterDirection2 = rand() % 4;

	int points = 0;
	//To keep track of the total time played for one game
	sf::Time totalTime;

	//the Play_Mode loop
	while (window.isOpen() && gameState == PLAY)
	{
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();
		}
		//this time is to check every 3 seconds. The 3 second rule for the monster.
		sf::Time time = clock.getElapsedTime();
		//Keeps track of the total time played
		totalTime += clock.getElapsedTime();

		//this will update the game
		sf::Vector2f overlapCandy = update(candyArray, tileArray, pacmanSprite, monsterSprite, monsterSprite2, event, numtile, 
											numcandy, MonsterDirection1, MonsterDirection2, numHeart, time, totalTime, clock);
		//if there is overlap then find it and delete it from the rendering window
		findCandy(overlapCandy, candyArray, boolcandy, numcandy, points);

		//convert int to string to display it to the rendering window
		std::stringstream convertToString;
		convertToString << points;
		scoreText.setString(convertToString.str());

		//draw sprites
		window.clear();

		drawWall(window, boolwall, tileArray, wallTexture);
		drawCandy(window, boolcandy, candyArray, candyTexture);
		drawHeart(window, heartArray, heartTexture, numHeart);
		draw(window, pacmanSprite, monsterSprite, monsterSprite2, numtile);

		//maybe display the total time elapsed to the user.
		window.draw(scoreText);
		window.draw(info);

		window.display();

		//when the player gets all the candy before losing all hearts, then  player win
		if (numcandy == 0 && numHeart > 0)
		{
			gameState = VICTORY;
		}
		//when the player loses all the hearts before getting all candies, then player lose
		if (numHeart == 0 && numcandy != 0)
		{
			gameState = GAME_OVER;
		}
		
	}
	
	delete[] candyArray;
}