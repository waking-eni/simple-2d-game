#pragma once

#include <iostream>
#include <vector>
#include <ctime>

#include "SFML/Graphics.hpp"
#include <SFML/System.hpp>
#include "SFML/Window.hpp"
#include "SFML/Audio.hpp"
#include "SFML/Network.hpp"

/*
	Class that acts as a game engine.
	Wrapper class.
*/

class Game
{
private:
	// Variables
	// Window
	sf::RenderWindow* window;
	sf::VideoMode videoMode;
	sf::Event ev;

	// Mouse positions
	sf::Vector2i mousePosWindow;
	// Most SFML operations are done with floats
	sf::Vector2f mousePosView;

	// Game logic
	unsigned points;
	float enemySpawnTimer;
	float enemySpawnTimerMax;
	int maxEnemies;
	bool mouseHeld;

	// Game objects
	std::vector<sf::RectangleShape> enemies;
	sf::RectangleShape enemy;

	// Private functions
	void initVariables();
	void initWindow();
	void initEnemies();
public:
	// Constructors & Destructors
	Game();
	virtual ~Game();

	// Accessors
	const bool running() const;

	// Functions
	void spawnEnemy();
	void pollEvents();
	void updateMousePositions();
	void updateEnemies();
	void update();
	void renderEnemies();
	void render();
	void printPoints();
};

