#include <SFML/Graphics.hpp>
#include <iostream>
#include <fstream>
#include <string>
#include <windows.h>
#include <unordered_map>
#include "gameObjects.h"
#include "mapManager.h"

extern TextureCollection textures;

int fpsCap = 60;

sf::Vector2i mapLoc = sf::Vector2i(0, 0);

Wrath* enemy = new Wrath;
Map* map = new Map;

sf::RenderWindow window(sf::VideoMode(1280, 720), "My window");

sf::Sprite* drawSprite(const sf::Texture* texture, sf::Vector2f location, float rotation = 0, sf::Color color = sf::Color(255, 255, 255), std::string origin = "")
{
	sf::Sprite* sprite = new sf::Sprite;

	sprite->setTexture(*texture);
	sprite->setColor(color);

	if (origin == "center")
	{
		sprite->setOrigin((texture->getSize().x / 2), (texture->getSize().y / 2));
	}

	sprite->setPosition(location);
	sprite->setRotation(rotation);

	return sprite;
}

class World
{
public:
	World();
	void update();
};

//INIT
World::World()
{
}

void rotateToVect(sf::Vector2i target)
{
	const float PI = 3.14159265;

	float dx = enemy->location.x - target.x;
	float dy = enemy->location.y - target.y;

	float rotation = (atan2(dy, dx)) * 180 / PI;
	if (target.x != enemy->location.x && target.y != enemy->location.y)
	{
		enemy->rotation = rotation;
	}
}

void moveToTarget()
{
	if (abs(enemy->location.x - enemy->target.x) > enemy->speed)
	{
		if (enemy->location.x < enemy->target.x)
		{
			enemy->location.x += enemy->speed;
		}
		else
		{
			enemy->location.x -= enemy->speed;
		}
	}
	else
	{
		enemy->location.x = enemy->target.x;
	}

	if (abs(enemy->location.y - enemy->target.y) > enemy->speed)
	{
		if (enemy->location.y < enemy->target.y)
		{
			enemy->location.y += enemy->speed;
		}
		else
		{
			enemy->location.y -= enemy->speed;
		}
	}
	else
	{
		enemy->location.y = enemy->target.y;
	}
}

void checkMouseEvents()
{
	if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
	{
		if (abs(sf::Mouse::getPosition(window).x - enemy->location.x) < 30 &&
			abs(sf::Mouse::getPosition(window).y - enemy->location.y) < 30)
		{
			enemy->selected = true;
			enemy->color = sf::Color(255, 255, 100);
		}
		else
		{
			enemy->selected = false;
			enemy->color = sf::Color(255, 255, 255);
		}
	}
	if (enemy->selected)
	{
		if (sf::Mouse::isButtonPressed(sf::Mouse::Right))
		{
			enemy->target = sf::Mouse::getPosition(window);
		}
	}
}

//WorldLoop
void World::update()
{
	checkMouseEvents();
	rotateToVect(enemy->target);
	moveToTarget();
}


class Render
{
public:
	Render();
	void update(World& world);
};


void drawMap(sf::RenderWindow* window)
{
	sf::Sprite tile;
	int itr = 0;
	int location;
	for (int y = 0; y < map->height; y++)
	{
		for (int x = 0; x < map->width; x++)
		{
			location = map->data[y][x];
			if (location != 0)
			{
				tile.setTexture(*map->tileSet->data[location]);
				tile.setPosition(sf::Vector2f(x * map->tileSet->tileWidth, y * map->tileSet->tileHeight));
				window->draw(tile);
			}
			itr++;
		}
	}
}

//INIT
Render::Render()
{
}

//RenderLoop
void Render::update(World& world)
{
	// run the program as long as the window is open
	// check all the window's events that were triggered since the last iteration of the loop
	sf::Event event;
	while (window.pollEvent(event))
	{
		// "close requested" event: we close the window
		if (event.type == sf::Event::Closed)
			window.close();
	}
	// clear the window with black color
	window.clear(sf::Color::Black);
	
	// draw everything here...
	drawMap(&window);

	sf::Sprite* sprite = drawSprite(enemy->texture, enemy->location, enemy->rotation, enemy->color, "center");
	window.draw(*sprite);
	delete sprite;

	// end the current frame
	window.display();
}

int main()
{
	World world;
	Render renderer;

	std::clock_t start;
	std::clock_t end;
	double duration;
	double sleepTime;

	map->createMap(map, "test.json");

	while (true)
	{
		start = std::clock();

		world.update();
		renderer.update(world);

		end = std::clock();

		duration = (end - start) / (CLOCKS_PER_SEC / 1000);
		std::cout << duration << std::endl;
		sleepTime = 1000 / fpsCap - duration;
		if (sleepTime > 0)
		{
			Sleep(sleepTime);
		}
	}
}