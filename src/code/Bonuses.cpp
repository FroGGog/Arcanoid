#include "headers/stdafx.h"
#include "headers/Bonuses.h"

void Bonuses::updateDuration()
{
	duraction -= 1.f;
	if (duraction <= 0) {
		isActive = false;
		isOnScreen = false;
		std::cout << "Clock end\n";
	}
}

void Bonuses::updateDownCollsion()
{
	if (b_sprite.getPosition().y > 600) {
		isOnScreen = false;
	}
}

Bonuses::Bonuses(std::shared_ptr<sf::Texture> texture, sf::Vector2f spawnPos,float _duraction)
{
	b_sprite.setTexture(*texture);

	b_sprite.setPosition(spawnPos);

	dir.y = 150.f;

	duraction = _duraction;

	type = bufType::NONE;

	isOnScreen = true;
	isActive = false;
	wasPickedUp = false;
}

bufType Bonuses::getType() const
{
	return type;
}

bool Bonuses::getOnScreen() const
{
	return isOnScreen;
}

bool Bonuses::getActive() const
{
	return isActive;
}

sf::FloatRect Bonuses::getRect() const
{
	return b_sprite.getGlobalBounds();
}

void Bonuses::setPickedUp()
{
	wasPickedUp = true;
}

bool Bonuses::getPickedUp() const
{
	return wasPickedUp;
}

void Bonuses::update(sf::Time deltaTime)
{

	if (isActive && duraction != 0) {
		updateDuration();
	}
	else if(isOnScreen){
		updateDownCollsion();
		b_sprite.move(dir * deltaTime.asSeconds());
	}
	
}


void Bonuses::render(sf::RenderTarget& target)
{
	if (!isActive) {
		target.draw(b_sprite);
	}
	
}


addBallBonus::addBallBonus(std::shared_ptr<sf::Texture> texture, sf::Vector2f spawnPos, float _duraction)
	: Bonuses{ texture, spawnPos, _duraction }
{
	type = bufType::ADDBALL;
	b_sprite.setScale(sf::Vector2f{ 0.06,0.06 });
}

void addBallBonus::update(sf::Time deltaTime)
{
	Bonuses::update(deltaTime);

}

void addBallBonus::hideBonus()
{
	isActive = false;
	isOnScreen = false;
}



incrLenght::incrLenght(std::shared_ptr<sf::Texture> texture, sf::Vector2f spawnPos, float _duraction)
	: Bonuses{ texture, spawnPos, _duraction }
{
	type = bufType::INCLENGHT;
	
	b_sprite.setScale(sf::Vector2f{ 0.06,0.06 });

}

void incrLenght::update(sf::Time deltaTime)
{
	Bonuses::update(deltaTime);
}

void incrLenght::hideBonus()
{
	isActive = false;
	isOnScreen = false;
}



incrSpeed::incrSpeed(std::shared_ptr<sf::Texture> texture, sf::Vector2f spawnPos, float _duraction)
	: Bonuses{ texture, spawnPos, _duraction }
{

	type = bufType::INCSPEED;

	wasPickedUp = false;

	b_sprite.setScale(sf::Vector2f{ 0.06,0.06 });

}

void incrSpeed::update(sf::Time deltaTime)
{
	Bonuses::update(deltaTime);
}

void incrSpeed::hideBonus()
{
	isActive = true;
	isOnScreen = false;

	b_sprite.setPosition(sf::Vector2f{ 0,0 });

}


