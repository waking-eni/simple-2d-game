#include "Game.h"


// Private functions
void Game::initVariables()
{
	this->window = nullptr;
}

void Game::initWindow()
{
	this->videoMode.height = 600;
	this->videoMode.width = 800;
	// create new window
	this->window = new sf::RenderWindow(this->videoMode, "Simple 2D Game", sf::Style::Default | sf::Style::Titlebar | sf::Style::Close);

	// set framerate
	this->window->setFramerateLimit(144);
}

void Game::initEnemies()
{
	this->enemy.setPosition(10.f, 10.f);
	this->enemy.setSize(sf::Vector2f(100.f, 100.f));
	this->enemy.setScale(sf::Vector2f(0.5f, 0.5f));
	this->enemy.setFillColor(sf::Color::Cyan);
	this->enemy.setOutlineColor(sf::Color::Green);
	this->enemy.setOutlineThickness(1.f);
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
}

void Game::pollEvents()
{
	while (this->window->pollEvent(this->ev)) {
		switch (this->ev.type) {
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
}

void Game::updateEnemies()
{

}

void Game::update()
{
	this->pollEvents();

	this->updateMousePositions();
	this->updateEnemies();

}

void Game::renderEnemies()
{
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

