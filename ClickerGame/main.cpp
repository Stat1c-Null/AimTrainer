#include <iostream>
#include "Game.h"



int main()
{
	//Init srand
	std::srand(static_cast<unsigned>(time(NULL)));

	//Startuem Dvizok Igry
	Game game;

	//loop igry
	//Igra ziva poka zivo okno
	while (game.running())
	{
		//Obnovlyaem ekran
		game.update();
		//Renderim ekran
		game.render();

	}

	//Konec
	return 0;
}