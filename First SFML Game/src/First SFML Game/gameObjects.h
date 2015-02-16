#ifndef __TEXTURECOLLECTOR_H__
#define __TEXTURECOLLECTOR_H__

#include "textureCollector.h"

extern TextureCollection textures;

class Unit
{
public:
	Unit();
};

class Elite :public Unit
{
public:
	Elite();
	sf::Texture* texture = textures.elite;
	float xLoc = 0.0;
	float yLoc = 0.0;
	float rotation = 0.0;
	float speed = 0.3;
	sf::Vector2i target;
};


class Spartan :public Unit
{
public:
	Spartan();
};


class building{};


class Environement{};

#endif