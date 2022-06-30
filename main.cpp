#include <iostream>
#include "Constants.h"
#include "Game.hpp"

int main(int argc, char *args[])
{

	std::cout << "Game is running" << std::endl;
	auto game{new Game()}; 

	game->initialize(WINDOW_WIDTH, WINDOW_HEIGHT);

	while (game->running())
	{
		game->processInput();
		game->update();
		game->render();
	}

	game->destroy();
	delete game;
	return 0;
}
