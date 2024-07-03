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
	std::shared_ptr<Player> playerObj;

	std::vector<std::shared_ptr<Targets>> allTargets;

	std::shared_ptr<Ball> ballObj;
	std::vector <std::shared_ptr<Ball>> allBalls;

	std::vector<std::shared_ptr<Bonuses>> allBonuses;

	//gui and textures
	std::map<std::string, std::shared_ptr<sf::Texture>> allTextures;

	//text
	sf::Font mainFont;
	sf::Text scoreText;
	sf::Text livesText;
	sf::Text upScore;
	sf::Text upLivesText;

	std::vector<sf::Text> allText;

	//gameLogicVars
	short lives;
	int score;
	bool startRound;

	//check if window is open
	bool isOpen;

	void initVars();
	void initWindow();
	void initGameField();
	void initTextures();
	void initFonts();

	void updateEvents();
	void updateBallCollision();
	void isAllBonusesOnScreen();
	void updateBallVector();
	void updateTexts();
	void updateLives();

	//restart round and all game
	void restartRound();

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

