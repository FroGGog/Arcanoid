#pragma once
#include "Bonuses.h"

class Targets
{
private:

	sf::RectangleShape shape;

	int hp;

	bufType type;


public:

	Targets(sf::Vector2f pos, int _hp);
	
	bool gotHit();

	sf::FloatRect getGBounds() const;
	sf::Vector2f getCenter() const;

	void setBufType(bufType b_type);
	bufType getBufType() const;

	void render(sf::RenderTarget& target);

	void updateColor();
};

