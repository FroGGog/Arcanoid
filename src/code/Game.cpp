#include "headers/stdafx.h"

#include "headers/Game.h"

// TODO : restart game when lives below 0

void Game::initVars()
{

	vidMode.width = 1000;
	vidMode.height = 600;

	isOpen = true;
 
	playerObj = std::make_shared<Player>();

	ballObj = std::make_shared<Ball>(sf::Vector2f{450, 400});
	allBalls.push_back(ballObj);
	
	score = 0;
	lives = 3;
	startRound = true;

}

void Game::initWindow()
{
	window = std::make_shared<sf::RenderWindow>(vidMode, "Arcanoid", sf::Style::Titlebar | sf::Style::Close);

	window->setFramerateLimit(60);

}

void Game::initGameField()
{
	int c_add = 7, c_lenght = 7, c_speed = 7;
	//59.f, 29.5f
	float startX = 20;
	float startY = 15;

	for (int y{ 0 }; y < 7; y++) {
		for (int x{ 0 }; x < 10; x++) {
			int setHp = 1;
			//set level design 
			if (y == 0 || y == 1) {
				setHp = 4;
			}
			else if (y == 2 || y == 3) {
				setHp = 3;
			}
			else if (y == 4 || y == 5) {
				setHp = 2;
			}

			auto temp = std::make_shared<Targets>(sf::Vector2f{ startX * (x + 1) + 59.f * x , startY * (y + 1) + 29.5f * y }, setHp);
			temp->setBufType(bufType::NONE);
			allTargets.push_back(temp);

		}
	}

	//randomly spawn add buffs
	for (; c_add > 0; ) {
		for (auto& target : allTargets) {
			int choice = rand() % (10 - 1 + 1) + 1;
			if (choice < 3) {
				target->setBufType(bufType::ADDBALL);
				c_add--;
			}
		}
	}
	// lenght buffs
	for (; c_lenght > 0; ) {
		for (auto& target : allTargets) {
			int choice = rand() % (10 - 1 + 1) + 1;
			if (choice < 3 && target->getBufType() == bufType::NONE) {
				target->setBufType(bufType::INCLENGHT);
				c_lenght--;
			}
		}
	}
	// speed buffs
	for (; c_speed > 0; ) {
		for (auto& target : allTargets) {
			int choice = rand() % (10 - 1 + 1) + 1;
			if (choice < 3 && target->getBufType() == bufType::NONE) {
				target->setBufType(bufType::INCSPEED);
				c_speed--;
			}
		}
	}

}

void Game::initTextures()
{
	auto tempText = std::make_shared<sf::Texture>();
	if (!tempText->loadFromFile("src/assets/bufficons/multiplyBall.png")) {
		std::cerr << "ERROR:LOADFROMFILE::multyplyBall.png\n";
	}
	allTextures["multiplyBall"] = tempText;

	tempText = std::make_shared<sf::Texture>();
	if (!tempText->loadFromFile("src/assets/bufficons/increaseLenght.png")) {
		std::cerr << "ERROR:LOADFROMFILE::increaseLenght.png\n";
	}
	allTextures["increaseLenght"] = tempText;


	tempText = std::make_shared<sf::Texture>();
	if (!tempText->loadFromFile("src/assets/bufficons/speedUp.png")) {
		std::cerr << "ERROR:LOADFROMFILE::speedUp.png\n";
	}
	allTextures["speedUp"] = tempText;

}

void Game::initFonts()
{
	if (!mainFont.loadFromFile("src/assets/fonts/First.otf")) {
		std::cerr << "ERROR::LOADFROMFILE::fonts\n";
	}

	upScore.setFont(mainFont);
	upScore.setCharacterSize(24);
	upScore.setPosition(sf::Vector2f{ 850, 40 });
	upScore.setString("Score: ");
	allText.push_back(upScore);

	upLivesText.setFont(mainFont);
	upLivesText.setCharacterSize(24);
	upLivesText.setPosition(sf::Vector2f{ 850, 110 });
	upLivesText.setString("Lives: ");
	allText.push_back(upLivesText);

	scoreText.setFont(mainFont);
	scoreText.setCharacterSize(24);
	scoreText.setPosition(sf::Vector2f{ 820, 80 });
	
	livesText.setFont(mainFont);
	livesText.setCharacterSize(24);
	livesText.setPosition(sf::Vector2f{ 900, 150 });
	

	std::stringstream ss;
	ss << std::to_string(lives);
	livesText.setString(ss.str());

	std::stringstream ss2;
	ss2 << std::to_string(score);
	scoreText.setString(ss2.str());


}

void Game::updateEvents()
{
	while (window->pollEvent(winEvents)) {

		switch (winEvents.type)
		{
		case sf::Event::Closed:
			window->close();
			isOpen = false;
			break;
		default:
			break;
		}

	}

}

void Game::updateBallCollision()
{
	//check if ball collide with targets
	for (auto& ball : allBalls) {
		for (int i{ 0 }; i < allTargets.size(); i++) {
			if (ball->getGBounds().intersects(allTargets[i]->getGBounds())) {

				if (ball->getGBounds().getPosition().x > allTargets[i]->getCenter().x) {
					ball->updateDir(allTargets[i]->getCenter(), true);
				}
				//on left
				else {
					ball->updateDir(allTargets[i]->getCenter(), false);
				}

				//target got hit and check if it is on 0 hp
				if (allTargets[i]->gotHit()) {
					score += 250;
					//if target got buff, create it when target destroy
					if (allTargets[i]->getBufType() == bufType::ADDBALL) {
						auto tempBonus = std::make_shared<addBallBonus>(allTextures["multiplyBall"],
							allTargets[i]->getGBounds().getPosition());
						std::cout << "got\n";
						allBonuses.push_back(tempBonus);
					}
					else if (allTargets[i]->getBufType() == bufType::INCLENGHT) {
						auto tempBonus = std::make_shared<incrLenght>(allTextures["increaseLenght"],
							allTargets[i]->getGBounds().getPosition());
						std::cout << "got\n";
						allBonuses.push_back(tempBonus);
					}
					else if (allTargets[i]->getBufType() == bufType::INCSPEED) {
						auto tempBonus = std::make_shared<incrSpeed>(allTextures["speedUp"],
							allTargets[i]->getGBounds().getPosition(), 150);
						std::cout << "got\n";
						allBonuses.push_back(tempBonus);
					}

					allTargets.erase(allTargets.begin() + i);
					
				}
				else {
					allTargets[i]->updateColor();
					score += 100;
				}
				
			}
		}
	}

	
	//check if ball collide with player
	for (auto& ball : allBalls) {
		//if ball collide with player 
		if (ball->getGBounds().intersects(playerObj->getGBounds())) {
			//if ball is on right to player
			if (ball->getGBounds().getPosition().x > playerObj->getCenter().x) {
				ball->updateDir(playerObj->getCenter(), true, true);
			}
			//on left
			else {
				ball->updateDir(playerObj->getCenter(), false, true);
			}

		}
	}
	//check if player collide with bonus
	for (auto& bonus : allBonuses) {
		if (playerObj->getGBounds().intersects(bonus->getRect())) {
			bonus->hideBonus();
			switch (bonus->getType())
			{
			case bufType::ADDBALL:
				addBalls();
				isAllBonusesOnScreen();
				return;
			case bufType::INCLENGHT:
				incrLenght_f(5.f);
				isAllBonusesOnScreen();
				return;
			case bufType::INCSPEED:
				incrSpeed_f(300.f);
				bonus->setPickedUp();
				isAllBonusesOnScreen();
				return;
			default:
				break;
			}
		}
	}

}

void Game::isAllBonusesOnScreen()
{
	//check if bonus is still in window borders
	for (int i{ 0 }; i < allBonuses.size(); i++) {
		if (!allBonuses[i]->getOnScreen() && !allBonuses[i]->getActive()) {
			if (allBonuses[i]->getType() == bufType::INCSPEED && 
				allBonuses[i]->getPickedUp()) {
				incrSpeed_f(-300.f);
			}
			allBonuses.erase(allBonuses.begin() + i);
			std::cout << "Deleted\n";
		}
		
	}
}

//check if ball is still on screen
void Game::updateBallVector()
{
	for (int index { 0 }; index < allBalls.size(); index++) {
		if (!allBalls[index]->onScreen()) {
			allBalls.erase(allBalls.begin() + index);
			std::cout << "DEL BALL\n";
		}
	}
}

void Game::updateTexts()
{
	std::stringstream ss;
	ss << std::to_string(lives);
	livesText.setString(ss.str());

	std::stringstream ss2;
	ss2 << std::to_string(score);
	scoreText.setString(ss2.str());

}

void Game::updateLives()
{
	if (allBalls.size() == 0) {
		restartRound();
		lives--;
	}

}

void Game::restartRound()
{
	ballObj = nullptr;
	playerObj->restartPos();
	ballObj = std::make_shared<Ball>(sf::Vector2f{ playerObj->getCenter().x - 5.f,
		playerObj->getCenter().y - 20.f});
	allBalls.push_back(ballObj);
	startRound = true;

}

void Game::addBalls()
{
	// we need to add x2 balls
	size_t ballsToAdd = allBalls.size() * 2 - allBalls.size();
	for (; ballsToAdd > 0; ballsToAdd--) {
		float randXDir = static_cast<float>(rand() % (1 - 0 + 1) - 1);
		if (randXDir == 0) {
			randXDir = 1.f;
		}

		float randYDir = static_cast<float>(rand() % (1 - 0 + 1) - 1);
		if (randYDir == 0) {
			randYDir = 1.f;
		}

		auto tempBall = std::make_shared<Ball>(allBalls[0]->getGBounds().getPosition(),
			sf::Vector2f{randXDir, randYDir});

		allBalls.push_back(tempBall);
	}

}

//for increase lenght buff
void Game::incrLenght_f(float addLen)
{
	playerObj->resize(sf::Vector2f{ playerObj->getGBounds().getSize().x + addLen, 10 });

}

void Game::incrSpeed_f(float addSpeed)
{
	for (auto& ball : allBalls) {
		ball->addSpeed(addSpeed);
	}

}

Game::Game()
{
	initTextures();

	initVars();

	initWindow();

	initGameField();

	initFonts();

}

bool Game::winOpen() const
{
	return isOpen;
}


void Game::render()
{
	window->clear();

	playerObj->render(*window);

	for (auto& i : allTargets) {
		i->render(*window);
	}
	
	for (auto& ball : allBalls) {
		ball->render(*window);
	}
	
	for (auto& bonus : allBonuses) {
		bonus->render(*window);
	}

	window->draw(scoreText);
	window->draw(livesText);

	for (auto& text : allText) {
		window->draw(text);
	}

	window->display();

}

void Game::update(sf::Time deltaTime)
{
	updateLives();

	updateEvents();

	playerObj->update(deltaTime);

	if (startRound) {
		allBalls[0]->updateStart(playerObj);
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space)) {
			startRound = false;
		}
	}
	else {
		for (auto& ball : allBalls) {
			ball->update(deltaTime);
		}
		updateBallVector();
	}
	
	

	for (auto& bonus : allBonuses) {
		bonus->update(deltaTime);
	}
	isAllBonusesOnScreen();

	updateBallCollision();

	updateTexts();

}
