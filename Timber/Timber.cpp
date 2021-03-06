#include "pch.h"
#include "SFML/Graphics.hpp"
#include <sstream>

//Pagina 156

using namespace sf;


//Functions declaration
void updateBranches(int seed);
const int NUM_BRANCHES = 6;
Sprite branches[NUM_BRANCHES];

//Where is the player branch?
//LEFT or RIGHT
enum class side { LEFT, RIGHT, NONE };
side branchPositions[NUM_BRANCHES];


int main()
{
	//Create video mode object
	VideoMode vm(1920, 1080);

	//Create and open a window for the game RenderWindow
	RenderWindow window(vm, "Timber!!!", Style::Fullscreen);

	//Create a texture to hold the graphic on the GPU
	Texture textureBackground;
	//Load a graphic into the texture
	textureBackground.loadFromFile("graphics/background.png");

	//Create a sprite
	Sprite spriteBackground;
	//Attach the texture to the sprite
	spriteBackground.setTexture(textureBackground);
	//Set the spriteBackground to cover the entire screen
	spriteBackground.setPosition(0, 0);

	//Make a tree sprite
	Texture textureTree;
	textureTree.loadFromFile("graphics/tree.png");
	Sprite spriteTree;
	spriteTree.setTexture(textureTree);
	spriteTree.setPosition(810, 0);

	//Prepare the bee
	Texture textureBee;
	textureBee.loadFromFile("graphics/bee.png");
	Sprite spriteBee;
	spriteBee.setTexture(textureBee);
	spriteBee.setPosition(0, 800);
	//Is bee moving?
	bool beeActive = false;
	//Bee's speed
	float beeSpeed = 0.0f;

	//Make 3 clouds from a texture
	Texture textureCloud;
	textureCloud.loadFromFile("graphics/cloud.png");

	Sprite spriteCloud1, spriteCloud2, spriteCloud3;
	spriteCloud1.setTexture(textureCloud);
	spriteCloud2.setTexture(textureCloud);
	spriteCloud3.setTexture(textureCloud);

	spriteCloud1.setPosition(0, 0);
	spriteCloud2.setPosition(0, 250);
	spriteCloud3.setPosition(0, 500);

	bool cloud1Active = false;
	bool cloud2Active = false;
	bool cloud3Active = false;

	float cloud1Speed = 0.0f;
	float cloud2Speed = 0.0f;
	float cloud3Speed = 0.0f;

	//Variables to control time itself
	Clock clock;

	//Time bar
	RectangleShape timeBar;
	float timeBarStartWidth = 400;
	float timeBarHeight = 80;
	timeBar.setSize(Vector2f(timeBarStartWidth, timeBarHeight));
	timeBar.setFillColor(Color::Red);
	timeBar.setPosition((1920 / 2) - timeBarStartWidth / 2, 980);

	Time gameTimeTotal;
	float timeRemaining = 6.0f;
	float timeBarWidthPerSecond = timeBarStartWidth / timeRemaining;

	//Track if game is paused or not
	bool paused = true;

	//Draw some text
	int score = 0;
	sf::Text messageText;
	sf::Text scoreText;

	//Choose font
	Font font;
	font.loadFromFile("fonts/KOMIKAP_.ttf");

	//Set font for our messages
	messageText.setFont(font);
	scoreText.setFont(font);

	//Assign messages
	messageText.setString("Press enter to start!");
	scoreText.setString("Score = 0");

	//Adjust text size
	messageText.setCharacterSize(75);
	scoreText.setCharacterSize(100);

	//Choose a color
	messageText.setFillColor(Color::White);
	scoreText.setFillColor(Color::White);

	//Set text position
	FloatRect textRect = messageText.getLocalBounds();	//Creo un rectangulo con floats y le asigno el tamaño del texto
	messageText.setOrigin(textRect.left + textRect.width / 2.0f, textRect.top + textRect.height / 2.0f);	//Seteo el punto de origen (movimiento y rotacion) para q sea el centro del rectangulo

	messageText.setPosition(1920 / 2.0f, 1080 / 2.0f);
	scoreText.setPosition(20, 20);

	//Prepare 6 branches
	Texture textureBranch;
	textureBranch.loadFromFile("graphics/branch.png");

	//Set texture for each branch sprite
	for (int i = 0; i < NUM_BRANCHES; i++)
	{
		branches[i].setTexture(textureBranch);
		branches[i].setPosition(-2000, -2000);
		//Set sprite's origin to dead center
		//We can spin it around without changing position
		branches[i].setOrigin(220, 20);
	}


	while (window.isOpen())
	{
		/* Handle inputs */
		if (Keyboard::isKeyPressed(Keyboard::Space))
		{
			window.close();
		}

		//Start game
		if (Keyboard::isKeyPressed(Keyboard::Return))
		{
			paused = false;

			//Reset time and score
			score = 0;
			timeRemaining = 5;

		}

		/* Update scene */

		if (!paused)
		{
			//Measure time
			Time dt = clock.restart();

			//Substract time from timeBar
			timeRemaining -= dt.asSeconds();
			//Refresh timeBar size
			timeBar.setSize(Vector2f(timeBarWidthPerSecond * timeRemaining, timeBarHeight));

			if (timeRemaining <= 0.0f)
			{
				//Pause the game
				paused = true;

				//Change text shown to player
				messageText.setString("Out of time!!!");

				//Reposition text based on its new size
				FloatRect textRect = messageText.getLocalBounds();
				messageText.setOrigin(textRect.left + textRect.width / 2, textRect.top + textRect.height / 2);
				messageText.setPosition(1920 / 2.0f, 1080 / 2.0f);

			}

			//Setup the bee
			if (!beeActive)
			{
				//How fast the bee is gonna be
				srand((int)time(0));
				beeSpeed = (rand() % 200) + 200;

				//How high is the bee
				srand((int)time(0) * 10);
				float height = (rand() % 500) + 500;
				spriteBee.setPosition(2000, height);
				beeActive = true;
			}
			else
				//Move the bee
			{
				spriteBee.setPosition(spriteBee.getPosition().x - (beeSpeed * dt.asSeconds()), spriteBee.getPosition().y);	//Setear X como resta entre pos anterior y pos actual
				//Has the bee reached the right edge of the screen
				if (spriteBee.getPosition().x < -100)
				{
					//Set it up ready to be a new cloud next frame
					beeActive = false;
				}

			}

			//Manage clouds
			//Cloud1
			if (!cloud1Active)
			{
				//How fast is the cloud
				srand((int)time(0) * 10);
				cloud1Speed = (rand() % 200);

				//How high is the cloud
				srand((int)time(0) * 10);
				float height = (rand() % 150);
				spriteCloud1.setPosition(-200, height);
				cloud1Active = true;
			}
			else
				//Move the cloud
			{
				spriteCloud1.setPosition(spriteCloud1.getPosition().x + (cloud1Speed * dt.asSeconds()), spriteCloud1.getPosition().y);
				if (spriteCloud1.getPosition().x > 1920)	//Si paso el limite derecho
				{
					cloud1Active = false;
				}
			}

			//Cloud2
			if (!cloud2Active)
			{
				//How fast is the cloud
				srand((int)time(0) * 20);
				cloud2Speed = (rand() % 200);

				//How high is the cloud
				srand((int)time(0) * 20);
				float height = (rand() % 300);
				spriteCloud2.setPosition(-200, height);
				cloud2Active = true;
			}
			else
				//Move the cloud
			{
				spriteCloud2.setPosition(spriteCloud2.getPosition().x + (cloud2Speed * dt.asSeconds()), spriteCloud2.getPosition().y);
				if (spriteCloud2.getPosition().x > 1920)	//Si paso el limite derecho
				{
					cloud2Active = false;
				}
			}

			//Cloud3
			if (!cloud3Active)
			{
				//How fast is the cloud
				srand((int)time(0) * 30);
				cloud3Speed = (rand() % 200);

				//How high is the cloud
				srand((int)time(0) * 30);
				float height = (rand() % 450);
				spriteCloud3.setPosition(-200, height);
				cloud3Active = true;
			}
			else
				//Move the cloud
			{
				spriteCloud3.setPosition(spriteCloud3.getPosition().x + (cloud3Speed * dt.asSeconds()), spriteCloud3.getPosition().y);
				if (spriteCloud3.getPosition().x > 1920)	//Si paso el limite derecho
				{
					cloud3Active = false;
				}
			}

			//Update score text
			std::stringstream ss;
			ss << "Score = " << score;
			scoreText.setString(ss.str());

			//Update branch sprites
			for (int i = 0; i < NUM_BRANCHES; i++)
			{
				float height = i * 150;
				if (branchPositions[i] == side::LEFT)
				{
					//Move sprite to the left side
					branches[i].setPosition(610, height);
					//Flip sprite the other way
					branches[i].setRotation(180);
				}
				else if (branchPositions[i] == side::RIGHT)
				{
					//Move sprite to the right side
					branches[i].setPosition(1330, height);
					//Set rotation to normal
					branches[i].setRotation(0);
				}
				else
				{
					//Hide the branch
					branches[i].setPosition(3000, 0);
				}
			}



			//End if(!paused)
		}


		/* Draw scene */

		//Clear scene from the last frame
		window.clear();

		//Draw scene here
		window.draw(spriteBackground);
		window.draw(spriteCloud1);
		window.draw(spriteCloud2);
		window.draw(spriteCloud3);
		window.draw(spriteTree);
		window.draw(spriteBee);
		for (int i = 0; i < NUM_BRANCHES; i++)
		{
			window.draw(branches[i]);
		}

		//Draw the score
		window.draw(scoreText);

		//Draw the timeBar
		window.draw(timeBar);

		//Check if paused
		if (paused)
		{
			window.draw(messageText);
		}

		//Show everything we just drew
		window.display();
	}

	return 0;	
}


void updateBranches(int seed)
{
	//Move all branches down one place
	for (int j = NUM_BRANCHES - 1; j > 0; j--)
	{
		branchPositions[j] = branchPositions[j - 1];
	}

	//Spawn new branch at pos 0
	//LEFT, RIGHT or NONE
	srand((int)time(0) + seed);
	int r = (rand() % 5);
	switch (r)
	{
		case 0:
			branchPositions[0] = side::LEFT;
			break;
		
		case 1:
			branchPositions[0] = side::RIGHT;
			break;

		default:
			branchPositions[0] = side::NONE;
			break;

	}
}

