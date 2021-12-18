#include "Game.h"

//Constructory / Destructory
Game::Game()//Constructor - Nachal Igry
{
	this->initVar();
	this->initWindow();
	this->initFonts();
	this->initText();
	this->initEnemies();
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

const bool Game::getEndGame() const
{
	return this->endGame;
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

	
	if (this->endGame == false)
	{
		this->updateMousePositions();

		this->updateText();

		this->updateEnemies();
	}
	//Konec igry esli net zdorovia
	if (this->health <= 0)
	{
		this->endGame = true;
		std::cout << "Game Over" << std::endl;
	}
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
	this->window->clear(sf::Color(60, 100, 180, 255));
	//Risuem Objects
	this->renderEnemies(*this->window);
	this->renderText(*this->window);
	this->window->display();
}

//Private functions
void Game::initVar()
{
	this->window = nullptr;

	//Set Game Logic Variables
	this->endGame = false;
	this->points = 0;
	this->health = 50;
	this->enemySpawnTimerMax = 20.f;
	this->enemySpawnTimer = enemySpawnTimerMax;
	this->maxEnemies = 20;
	this->mouseHeld = false;
}

void Game::initWindow()
{
	//Renderim okno igry 
	this->videoMode.width = 960;
	this->videoMode.height = 640;

	this->window = new sf::RenderWindow(this->videoMode, "Aim Trainer", sf::Style::Titlebar | sf::Style::Close);
	//Limit FPS                                          
	this->window->setFramerateLimit(fps);
}

void Game::initEnemies()
{
	this->enemy.setPosition(50.f,50.f);//Position
	this->enemy.setSize(sf::Vector2f(100.f, 100.f));//Razmer
	this->enemy.setScale(sf::Vector2f(0.5f, 0.5f));
	this->enemy.setFillColor(sf::Color(184, 55, 234));//Color
	this->enemy.setOutlineColor(sf::Color(67, 51, 100));//Obvodka
	this->enemy.setOutlineThickness(5.f);//Zhir obvodki
}

void Game::initFonts()
{
	if (this->font.loadFromFile("Fonts/Roboto-Black.ttf")) 
	{
		std::cout << "ERROR: Failed to load font" << "\n";
	}
}

void Game::initText()
{
	this->uiText.setFont(this->font);
	this->uiText.setCharacterSize(textSize);
	this->uiText.setFillColor(sf::Color::Magenta);
	this->uiText.setString("NONE");
}

void Game::updateMousePositions()
{
	/*
	 @ return void

	 Obnovlyem mouse position
		- Mouse position otnositelno okna

	*/

	//Obnovlyem mouse position otnositelno okna
	//std::cout << "Mouse pos: "
		//<< sf::Mouse::getPosition(*this->window).x << " "
		//<< sf::Mouse::getPosition(*this->window).y << "\n";

	this->mousePosWindow = sf::Mouse::getPosition(*this->window);
	this->mousePosView = this->window->mapPixelToCoords(this->mousePosWindow);//Update mouse relative to view
}

void Game::updateText()
{
	std::stringstream ss;

	ss << "Points: " << this->points << "\n"
		<< "Health: " << this->health << "\n";
	this->uiText.setString(ss.str());
}


void Game::spawnEnemy()
{
	/*
		@return void

		Sozdaem vragom i ukazyvaem ih cveta i positions
		-Set Random Position
		-Set Random Color
		-Add enemy to vector
	*/

	this->enemy.setPosition(
		static_cast<float>(rand() % static_cast<int>(this->window->getSize().x - this->enemy.getSize().x)),
		0.f
	);

	this->enemy.setFillColor(sf::Color::Green);

	//Sozdaem Vraga
	this->enemies.push_back(this->enemy);

	//Udalyaem Vragov 


}

void Game::updateEnemies()
{
	/*
		@return void

		Obnovlyem timer i sozdaem vragov kak tolko timer zakanchivaetsy
		Dvigaet vragov
		Ubrat vraga ot kraya okna
	*/
	//Update Timer chto by sozdavat vragov po ego okonchaniu
	if (this->enemies.size() < this->maxEnemies)
	{
		if (this->enemySpawnTimer >= this->enemySpawnTimerMax)
		{//Obnulyem Timer i sozdaem vraga
			this->spawnEnemy();
			this->enemySpawnTimer = 0.f;
		}
		else {//Pribavlyem k timeru
			this->enemySpawnTimer += 1.f;
		}
	}

	//Move enemies down and update 
	for (int i = 0;i < this->enemies.size(); i++)
	{

		this->enemies[i].move(0.f, enemySpeed);

		//Esli vrag vnisu okna
		if (this->enemies[i].getPosition().y > this->window->getSize().y)
		{
			this->enemies.erase(this->enemies.begin() + i);

			this->health -= 1;
			this->points -= 2;
			std::cout << "Health: " << this->health << "\n";
		}

	}

	//Check if clicked on enemy

	if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
	{
		if (this->mouseHeld == false)
		{
			this->mouseHeld = true;
			bool deleted = false;
			for (size_t i = 0; i < this->enemies.size() && deleted == false; i++)
			{
				if (this->enemies[i].getGlobalBounds().contains(this->mousePosView))
				{
					//Udalit Vraga
					deleted = true;
					this->enemies.erase(this->enemies.begin() + i);

					//Gain Points
					this->points += 10;
					std::cout << "Points: " << this->points << "\n";
				}
			}
		}
	}
	else {
		this->mouseHeld = false;
	}
}

void Game::renderEnemies(sf::RenderTarget& target)
{
	//Risuem Vragov na Ekrane
	for (auto& e : this->enemies)
	{
		target.draw(e);
	}
}

void Game::renderText(sf::RenderTarget& target)
{
	target.draw(this->uiText);
}
