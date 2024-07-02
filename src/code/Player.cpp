#include "headers/stdafx.h"
#include "headers/Player.h"


void Player::updateMovement(sf::Time deltaTime)
{
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) {
		dir.x = -speed;
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {
		dir.x = speed;
	}
	else {
		dir.x = 0;
	}

	player_shape.move(dir * deltaTime.asSeconds());

}

void Player::updateBordersCollision()
{
	if (player_shape.getPosition().x < 0) {
		player_shape.setPosition(sf::Vector2f{ 0, player_shape.getPosition().y });
	}
	if (player_shape.getPosition().x + player_shape.getGlobalBounds().width > 800) {
		player_shape.setPosition(sf::Vector2f{ 800 - player_shape.getGlobalBounds().width, player_shape.getPosition().y});
	}
}

Player::Player()
{
	speed = 350.f;
	dir = sf::Vector2f{ 0,0 };

	player_shape.setPosition(400, 500);
	player_shape.setSize(sf::Vector2f{ 75, 10 });


}

sf::Vector2f Player::getCenter() const
{
	return sf::Vector2f{ player_shape.getPosition().x + player_shape.getGlobalBounds().width / 2,
						player_shape.getPosition().y + player_shape.getGlobalBounds().height / 2 };
}

sf::FloatRect Player::getGBounds() const
{
	return player_shape.getGlobalBounds();
}

void Player::restartPos()
{
	player_shape.setPosition(sf::Vector2f{ 400, 500 });
	player_shape.setSize(sf::Vector2f{ 75, 10 });
}

void Player::resize(sf::Vector2f newSize)
{
	player_shape.setSize(newSize);
}

void Player::update(sf::Time deltaTime)
{
	updateMovement(deltaTime);

	updateBordersCollision();

}

void Player::render(sf::RenderTarget& target)
{
	target.draw(player_shape);
}
