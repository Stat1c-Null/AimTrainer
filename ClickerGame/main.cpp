#include <iostream>
#include "Game.h"



int main()
{
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