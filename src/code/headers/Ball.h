#pragma once
#include "Player.h"

class Ball {

private:

	sf::CircleShape ball_shape;

	float speed;
	sf::Vector2f dir;
	bool isOnScreen;

	void checkBorderCollision();

public:

	Ball(sf::Vector2f pos);

	Ball(sf::Vector2f mainBallPos, sf::Vector2f moveDir);

	sf::FloatRect getGBounds() const;
	bool onScreen() const;
	void addSpeed(float addSpeed);

	void render(sf::RenderTarget& target);

	void update(sf::Time deltaTime);
	void updateStart(std::shared_ptr<Player> playerPtr);
	void updateDir(sf::Vector2f distance, bool right, bool player = false);

};