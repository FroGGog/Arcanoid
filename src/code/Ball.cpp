#include "headers/stdafx.h"

#include "headers/Ball.h"

void Ball::updateDir(sf::Vector2f distance, bool right, bool player)
{
	//ball can collide <20;  >20 and <30; >30 and <40; >40
	float newX = 0.f;
	//update dir if collide with player
	auto cDist = sqrt(pow((distance.x - ball_shape.getPosition().x), 2) + pow((distance.y - ball_shape.getPosition().y), 2));
	//update ball pos depend on center of player obj 
	if (cDist < 20) {
		//randomly generate new ball x dir
		int randNum = rand() % (75 - 60 + 1) + 60;
		newX = static_cast<float>(randNum);
	}
	else if (cDist > 20 && cDist < 30) {
		int randNum = rand() % (100 - 80 + 1) + 80;
		newX = static_cast<float>(randNum);
	}
	else if (cDist > 30 && cDist < 40) {
		int randNum = rand() % (125 - 105 + 1) + 105;
		newX = static_cast<float>(randNum);
	}
	else {
		int randNum = rand() % (150 - 130 + 1) + 130;
		newX = static_cast<float>(randNum);
	}
	// check from which side ball comming 
	if (!right) {
		// if ball come from left 
		newX = -newX;
	}
	dir.x = newX;
	// check if ball collide with player or with targets
	// and change y dir 
	if (player) {
		dir.y = -speed;
	}
	else {
		dir.y = speed;
	}
	

}

void Ball::checkBorderCollision()
{
	//check if ball collide left side of screen
	if (ball_shape.getPosition().x < 0) {
		dir.x = -dir.x;
	}
	//right side
	else if (ball_shape.getPosition().x > 800) {
		dir.x = -dir.x;
	}

	//top
	if (ball_shape.getPosition().y < 0) {
		int randNum = rand() % (150 - 130 + 1) + 130;
		randNum = static_cast<float>(randNum);
		dir.y = speed;
		if (dir.x > 0) {
			dir.x = randNum;
		}
		else {
			dir.x = -randNum;
		}
		
	}

	if (ball_shape.getPosition().y > 600) {
		isOnScreen = false;
	}
}


sf::FloatRect Ball::getGBounds() const
{
	return ball_shape.getGlobalBounds();
}

bool Ball::onScreen() const
{
	return isOnScreen;
}

void Ball::addSpeed(float addSpeed)
{
	speed += addSpeed;
}

Ball::Ball(sf::Vector2f pos)
{
	ball_shape.setRadius(7.f);
	ball_shape.setPosition(pos);
		
	isOnScreen = true;

	speed = 400.f;
	dir.y = speed;

}

//constructor for new balls spawning
Ball::Ball(sf::Vector2f mainBallPos, sf::Vector2f moveDir)
{
	ball_shape.setRadius(7.f);
	ball_shape.setPosition(mainBallPos);

	isOnScreen = true;

	speed = 400.f;

	int randDirX = rand() % (150 - 10 + 1) + 10;

	dir.x = randDirX * moveDir.x;
	dir.y = speed * moveDir.y;
}


void Ball::render(sf::RenderTarget& target)
{
	target.draw(ball_shape);
}

void Ball::update(sf::Time deltaTime)
{

	ball_shape.move(dir * deltaTime.asSeconds());

	checkBorderCollision();
}

//update func round start
void Ball::updateStart(std::shared_ptr<Player> pPtr)
{
	ball_shape.setPosition(sf::Vector2f{ pPtr->getCenter().x - 5.f, pPtr->getCenter().y - 20.f });
}
