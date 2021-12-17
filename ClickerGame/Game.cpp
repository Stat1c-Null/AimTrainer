#include "Game.h"

//Constructory / Destructory
Game::Game()//Constructor - Nachal Igry
{
	this->initVar();
	this->initWindow();
}

Game::~Game()//Destructory - Zaconchil igry
{
	//Delete okno posle konca igry
	delete this->window;
}

//Accessors
const bool Game::running() const
{
	//Proveryem esli okno otryto
	return this->window->isOpen();
}

//Functions
//Obnovlyem destvya so storony igroka
void Game::pollEvents()
{
	//Deistvya
	while (this->window->pollEvent(this->ev))
	{
		switch (this->ev.type)
		{
		case sf::Event::Closed://Zakryt igru po krestiku
			this->window->close();
			break;
		case sf::Event::KeyPressed:
			if (this->ev.key.code == sf::Keyboard::Escape)//Zakryt igru po escape
				this->window->close();
			break;
		}
	}
}

//Obnovlyem igru (FPS)
void Game::update()
{
	this->pollEvents();
}

void Game::render()
{
	/*
		@return void

		- Chistim starie kadry
		- Renderim objects
		- Obnovlyem kadry
		
		Renderim igrovye objects
	*/
	//Chistim okno
	this->window->clear(sf::Color(180, 40, 100, 255));
	//Potom risuem
	this->window->display();
}

//Private functions
void Game::initVar()
{
	this->window = nullptr;
}

void Game::initWindow()
{
	//Renderim okno igry 
	this->videoMode.width = 960;
	this->videoMode.height = 640;

	this->window = new sf::RenderWindow(this->videoMode, "Clicker Game", sf::Style::Titlebar | sf::Style::Close);
}
