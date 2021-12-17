#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Network.hpp>//Mojno ubrat

/*
	Class kotorye rabotaet kak dvizok igry
*/

class Game
{
	private:
		//Variables
		//Window
		sf::RenderWindow* window;
		sf::VideoMode videoMode;
		sf::Event ev;

		//Private functions
		void initVar();
		void initWindow();

	public:
		//Constructory / Destructory
		Game();
		virtual ~Game();
		//Accessors
		const bool running() const;
		//Functions
		void pollEvents();
		void update();
		void render();
};

