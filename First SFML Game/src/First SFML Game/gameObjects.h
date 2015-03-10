#ifndef __TEXTURECOLLECTOR_H__
#define __TEXTURECOLLECTOR_H__

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
	sf::Color color = sf::Color(255, 255, 255);
	float rotation = 0.0;
	float speed = 3.0;
	bool selected;
	sf::Vector2i target;
};


class Spartan :public Unit
{
public:
	Spartan();
	//sf::Texture* texture = textures.spartan;
	sf::Vector2f location;
	sf::Color color = sf::Color(255, 255, 255);
	float rotation = 0.0;
	float speed = 3.0;
	bool selected;
	sf::Vector2i target;
};


class building{};


class Environement{};

#endif