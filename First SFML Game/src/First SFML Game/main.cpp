#include <SFML/Graphics.hpp>
#include <iostream>
#include <string>
#include "gameObjects.h"

Elite enemy;

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

//WorldLoop
void World::update()
{
}


class Render
{
public:
	Render();
	void update(World& world);

private:
	sf::RenderWindow window;
};

//INIT
Render::Render() : window(sf::VideoMode(800, 600), "My window")
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

	if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
	{
		enemy.target = sf::Mouse::getPosition(window);
	}

	if (enemy.xLoc < enemy.target.x)
	{
		enemy.xLoc += enemy.speed;
	}
	else
	{
		enemy.xLoc -= enemy.speed;
	}

	if (enemy.yLoc < enemy.target.y)
	{
		enemy.yLoc += enemy.speed;
	}
	else
	{
		enemy.yLoc -= enemy.speed;
	}

	// end the current frame
	window.display();
}


int main()
{
	World world;
	Render renderer;
	
	while (true)
	{
		world.update();
		renderer.update(world);
	}
}