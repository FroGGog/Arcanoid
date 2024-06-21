#pragma once

#include "headers/Game.h"
#include "headers/Player.h"
#include "headers/Targets.h"
#include "headers/Ball.h"
#include "headers/Bonuses.h"

class Game
{
private:

	std::shared_ptr<sf::RenderWindow> window;
	sf::VideoMode vidMode;

	sf::Event winEvents;

	//game stuff
	std::unique_ptr<Player> playerObj;

	std::vector<std::shared_ptr<Targets>> allTargets;

	std::shared_ptr<Ball> ballObj;
	std::vector <std::shared_ptr<Ball>> allBalls;

	std::vector<std::shared_ptr<Bonuses>> allBonuses;

	//gui and textures
	std::map<std::string, std::shared_ptr<sf::Texture>> allTextures;

	//check if window is open
	bool isOpen;

	void initVars();
	void initWindow();
	void initGameField();
	void initTextures();

	void updateEvents();
	void updateBallCollision();
	void isAllBonusesOnScreen();
	void updateBallVector();

	//apply bonuses
	void addBalls();
	void incrLenght_f(float addLen);
	void incrSpeed_f(float addSpeed);

public:

	Game();

	bool winOpen() const;

	void render();

	void update(sf::Time deltaTime);



};

