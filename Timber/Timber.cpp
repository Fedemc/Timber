#include "pch.h"
#include "SFML/Graphics.hpp"


using namespace sf;

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


	while (window.isOpen())
	{
		/* Handle inputs */
		if (Keyboard::isKeyPressed(Keyboard::Space))
		{
			window.close();
		}

		/* Update scene */

		//Measure time
		Time dt = clock.restart();

		//Setup the bee
		if (!beeActive)
		{
			//How fast the bee is gonna be
			srand((int)time(0));
			beeSpeed = (rand() % 200) + 200;

			//How high is the bee
			srand((int)time(0)*10);
			float height = (rand() % 500) + 500;
			spriteBee.setPosition(2000, height);
			beeActive = true;
		}
		else 
		//Move the bee
		{
			spriteBee.setPosition(spriteBee.getPosition().x - (beeSpeed * dt.asSeconds()), spriteBee.getPosition().y);
			//Has the bee reached the right edge of the screen
			if (spriteBee.getPosition().x < -100)
			{
				//Set it up ready to be a new cloud next frame
				beeActive = false;
			}

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


		//Show everything we just drew
		window.display();

	}


	return 0;	
}
