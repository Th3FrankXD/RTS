#include <SFML/Graphics.hpp>
#include <iostream>
#include <string>
#include <windows.h>
#include "gameObjects.h"

int fpsCap = 60;

Elite enemy;
sf::RenderWindow window(sf::VideoMode(800, 600), "My window");

sf::Sprite* drawSprite(const sf::Texture* texture, float xLoc, float yLoc, float rotation)
{
	sf::Sprite* sprite = new sf::Sprite;
	sf::Vector2f location = sf::Vector2f(xLoc, yLoc);

	sprite->setTexture(*texture);

	sprite->setOrigin((texture->getSize().x / 2), (texture->getSize().y / 2));

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

void moveToTarget()
{
	if (enemy.xLoc - enemy.target.x < -enemy.speed || enemy.xLoc - enemy.target.x > enemy.speed)
	{
		if (enemy.xLoc < enemy.target.x)
		{
			enemy.xLoc += enemy.speed;
		}
		else
		{
			enemy.xLoc -= enemy.speed;
		}
	}
	else
	{
		enemy.xLoc = enemy.target.x;
	}

	if (enemy.yLoc - enemy.target.y < -enemy.speed || enemy.yLoc - enemy.target.y > enemy.speed)
	{
		if (enemy.yLoc < enemy.target.y)
		{
			enemy.yLoc += enemy.speed;
		}
		else
		{
			enemy.yLoc -= enemy.speed;
		}
	}
	else
	{
		enemy.yLoc = enemy.target.y;
	}
}

//WorldLoop
void World::update()
{
	if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
	{
		enemy.target = sf::Mouse::getPosition(window);
	}

	moveToTarget();
}


class Render
{
public:
	Render();
	void update(World& world);
};

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
	sf::Sprite* sprite = drawSprite(enemy.texture, enemy.xLoc, enemy.yLoc, enemy.rotation);
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

	while (true)
	{
		start = std::clock();

		world.update();
		renderer.update(world);

		end = std::clock();

		duration = (end - start) / (CLOCKS_PER_SEC / 1000);
		sleepTime = 1000 / fpsCap - duration;
		if (sleepTime > 0)
		{
			Sleep(sleepTime);
		}
	}
}