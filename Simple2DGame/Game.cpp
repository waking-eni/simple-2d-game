#include "Game.h"


// Private functions
void Game::initVariables()
{
	this->window = nullptr;

	this->points = 0;
	this->enemySpawnTimerMax = 10.f;
	this->enemySpawnTimer = this->enemySpawnTimerMax;
	this->maxEnemies = 5;
	this->mouseHeld = false;
}

void Game::initWindow()
{
	this->videoMode.height = 600;
	this->videoMode.width = 800;
	// create new window
	this->window = new sf::RenderWindow(this->videoMode, "Simple 2D Game", sf::Style::Default | sf::Style::Titlebar | sf::Style::Close);

	// set framerate
	this->window->setFramerateLimit(60);
}

void Game::initEnemies()
{
	this->enemy.setPosition(10.f, 10.f);
	this->enemy.setSize(sf::Vector2f(100.f, 100.f));
	this->enemy.setScale(sf::Vector2f(0.5f, 0.5f));
	this->enemy.setFillColor(sf::Color::Cyan);
	//this->enemy.setOutlineColor(sf::Color::Green);
	//this->enemy.setOutlineThickness(1.f);
}

// Constructors & Destructors
Game::Game()
{
	this->initVariables();
	this->initWindow();
	this->initEnemies();
}


Game::~Game()
{
	delete this->window;
}

// Accessors
const bool Game::running() const
{
	return this->window->isOpen();
}

// Functions
void Game::spawnEnemy()
{
	/*
		Spawns enemies and sets their colours and positions
			- sets a random position
			- sets a random colour ------------------------------ do next
			- add enemy to the vector
	*/

	// Enemy is dependent on the top left corner of the window
	// We want enemy to be as close to the right side of the window minus their size
	this->enemy.setPosition(
		static_cast<float>(rand() % static_cast<int>(this->window->getSize().x - this->enemy.getSize().x)),
		0.f
	);

	this->enemy.setFillColor(sf::Color::Green);

	// Spawn the enemy
	this->enemies.push_back(this->enemy);

	// Remove enemies at the bottom of the window
}

void Game::pollEvents()
{
	while (this->window->pollEvent(this->ev)) 
	{
		switch (this->ev.type) 
		{
		case sf::Event::Closed:
			this->window->close();
			break;
		case sf::Event::KeyPressed:
			if (this->ev.key.code == sf::Keyboard::Escape)
				this->window->close();
			break;
		}
	}
}

void Game::updateMousePositions()
{
	/*
		Updates the mouse positions
			- mouse position relative to window (Vector2i)
	*/
	this->mousePosWindow = sf::Mouse::getPosition(*this->window);
	// take a pixel from the window and map it to its coordinates
	// take mouse position relative to the window and map it to the view (as floats)
	this->mousePosView = this->window->mapPixelToCoords(this->mousePosWindow);
}

void Game::updateEnemies()
{
	/*
		Updates the enemy spawn timer and spawns emenies
		when the total amount of enemies is smaller than the maximum.
		Moves the enemies downwards.
		Removes the enemies at the edge of the screen
	*/

	// Updating the timer for enemy spawning
	if(this->enemies.size() < this->maxEnemies) 
	{
		if (this->enemySpawnTimer >= this->enemySpawnTimerMax) 
		{
			// when timer ends, spawn enemy
			this->spawnEnemy();
			this->enemySpawnTimer = 0.f; // reset timer
		}
		else
			this->enemySpawnTimer += 1.f;
	}

	// Moving and updateing the enemies
	// Gaining points

	// This way is memory heavy, change it -------------------------do this
	for (int i = 0; i < this->enemies.size(); i++)
	{
		this->enemies[i].move(0.f, 4.f);

		// Remove the enemy that got past the bottom of the window
		if (this->enemies[i].getPosition().y > this->window->getSize().y)
		{
			this->enemies.erase(this->enemies.begin() + i);
		}

	}

	//Check if clicked upon
	if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
	{
		if (this->mouseHeld == false)
		{
			this->mouseHeld = true;
			bool deleted = false;
			for (size_t i = 0; i < this->enemies.size() && deleted == false; i++)
			{
				// get the bounds around the enemy
				if (this->enemies[i].getGlobalBounds().contains(this->mousePosView))
				{
					//Gain points
					this->points += 1;
					//std::cout << "Points: " << this->points << "\n";

					//Delete the enemy
					deleted = true;
					this->enemies.erase(this->enemies.begin() + i);
				}
			}
		}
	}
	else
	{
		this->mouseHeld = false;
	}


}

void Game::update()
{
	this->pollEvents();

	this->updateMousePositions();
	this->updateEnemies();

}

void Game::renderEnemies()
{
	// Rendering all enemies
	for (auto& e : this->enemies)
	{
		this->window->draw(e);
	}
}

void Game::render()
{
	/*
		- clear old frame
		- render objects
		- display frame in window
		Renders the game objects
	*/
	this->window->clear(); // Clear old frame

	// Draw game objects
	this->renderEnemies();

	this->window->display(); // Tell app that window is done drawing
}

void Game::printPoints()
{
	std::cout << "Points: " << this->points << "\n";
}

