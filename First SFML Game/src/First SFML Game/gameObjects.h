#include "textureCollector.h"

extern TextureCollection textures;

class Unit
{
public:
	Unit();
};

class Wrath :public Unit
{
public:
	Wrath();
	sf::Texture* texture = textures.wrath;
	sf::Vector2f location;
	sf::Vector2f size = sf::Vector2f(2, 2);
	sf::Color color = sf::Color(255, 255, 255);
	sf::Vector2f scale;
	float rotation = 0.0;
	float speed = 3.0;
	bool selected;
	sf::Vector2f target;
};


class Spartan :public Unit
{
public:
	Spartan();
	//sf::Texture* texture = textures.spartan;
	sf::Vector2f location;
	sf::Vector2f size = sf::Vector2f(1, 1);
	sf::Color color = sf::Color(255, 255, 255);
	sf::Vector2f scale;
	float rotation = 0.0;
	float speed = 3.0;
	bool selected;
	sf::Vector2f target;
};


class building{};


class Environement{};