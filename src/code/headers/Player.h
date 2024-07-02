#pragma once
class Player
{

private:

	sf::RectangleShape player_shape;

	float speed;

	sf::Vector2f dir;

	void updateMovement(sf::Time deltaTime);
	void updateBordersCollision();

public:

	Player();

	sf::Vector2f getCenter() const;
	sf::FloatRect getGBounds() const;

	void restartPos();

	void resize(sf::Vector2f newSize);

	void update(sf::Time deltaTime);

	void render(sf::RenderTarget& target);

};

