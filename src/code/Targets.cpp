#include "headers/stdafx.h"

#include "headers/Targets.h"

Targets::Targets(sf::Vector2f pos, int _hp)
{
	shape.setPosition(pos);
	shape.setSize(sf::Vector2f{ 59.f, 29.5f });

	type = bufType::NONE;

	hp = _hp;
	switch (hp)
	{
	case 1:
		shape.setFillColor(sf::Color::Red);
		break;
	case 2:
		shape.setFillColor(sf::Color::Yellow);
		break;
	case 3:
		shape.setFillColor(sf::Color::Green);
		break;
	case 4:
		shape.setFillColor(sf::Color::Blue);
		break;
	default:
		break;
	}
}

bool Targets::gotHit()
{
	hp--;
	if (hp == 0) {
		return true;
	}
	return false;
}

sf::FloatRect Targets::getGBounds() const
{
	return shape.getGlobalBounds();
}

sf::Vector2f Targets::getCenter() const
{
	return sf::Vector2f{ shape.getPosition().x + shape.getGlobalBounds().width / 2,
						shape.getPosition().y + shape.getGlobalBounds().height / 2 };
}

void Targets::setBufType(bufType b_type)
{
	type = b_type;
}

bufType Targets::getBufType() const
{
	return type;
}

void Targets::render(sf::RenderTarget& target)
{
	target.draw(shape);
}

void Targets::updateColor()
{
	switch (hp)
	{
	case 3:
		shape.setFillColor(sf::Color::Green);
		break;
	case 2:
		shape.setFillColor(sf::Color::Yellow);
		break;
	case 1:
		shape.setFillColor(sf::Color::Red);
	default:
		break;
	}
}
