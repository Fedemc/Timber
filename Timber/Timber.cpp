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



	while (window.isOpen())
	{
		/* Handle inputs */
		if (Keyboard::isKeyPressed(Keyboard::Space))
		{
			window.close();
		}

		/* Update scene */


		/* Draw scene */

		//Clear scene from the last frame
		window.clear();

		//Draw scene here
		window.draw(spriteBackground);

		//Show everything we just drew
		window.display();

	}


	return 0;	
}
