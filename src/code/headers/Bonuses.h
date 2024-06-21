#pragma once

// TODO : add other buff types
enum class bufType{ADDBALL, INCLENGHT, INCSPEED, SLOWMOV, NONE};

class Bonuses
{
protected:

	sf::Sprite b_sprite;

	sf::Vector2f dir;

	float duraction;

	bufType type;

	bool isOnScreen;
	bool isActive;
	bool wasPickedUp;

	void updateDuration();
	void updateDownCollsion();

public:

	Bonuses(std::shared_ptr<sf::Texture> texture, sf::Vector2f spawnPos, float _duraction = 0);

	bufType getType() const;
	bool getOnScreen() const;
	bool getActive() const;
	sf::FloatRect getRect() const;

	void setPickedUp();
	bool getPickedUp() const;

	virtual void update(sf::Time deltaTime);

	//hides bonus and apply buff of it
	virtual void hideBonus() = 0;

	void render(sf::RenderTarget& target);


};

class addBallBonus : public Bonuses {

public:

	addBallBonus(std::shared_ptr<sf::Texture> texture, sf::Vector2f spawnPos, float _duraction = 0);

	void update(sf::Time deltaTime) override;
	
	void hideBonus() override;

};


class incrLenght : public Bonuses {

public:

	incrLenght(std::shared_ptr<sf::Texture> texture, sf::Vector2f spawnPos, float _duraction = 0);

	void update(sf::Time deltaTime) override;

	void hideBonus() override;

};

class incrSpeed : public Bonuses {

private:
	bool wasPickedUp;

public:

	incrSpeed(std::shared_ptr<sf::Texture> texture, sf::Vector2f spawnPos, float _duraction = 150);


	void update(sf::Time deltaTime) override;

	void hideBonus() override;
};