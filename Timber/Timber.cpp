#include "pch.h"
#include "SFML/Graphics.hpp"


using namespace sf;

int main()
{
	//Create video mode object
	VideoMode vm(1920, 1080);
	//Create and open a window for the game RenderWindow
	RenderWindow window(vm, "Timber!!!", Style::Fullscreen);

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

		//Show everything we just drew
		window.display();

	}


	return 0;	
}
