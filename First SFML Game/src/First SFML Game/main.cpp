#include <SFML/Graphics.hpp>
#include <iostream>
#include "gameObjects.h"
#include "textureCollector.h"

TextureCollection textures;

sf::Sprite drawSprite(const Unit& obj, float xLoc, float yLoc, int rotation=0)
{
	sf::Sprite* sprite = new sf::Sprite;
	sf::Vector2f location = sf::Vector2f(xLoc, yLoc);

	sprite->setTexture(*textures.elite);

	sprite->setOrigin((textures.elite->getSize().x / 2), (textures.elite->getSize().y / 2));

	sprite->setPosition(location);
	sprite->setRotation(rotation);

	return *sprite;
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
	
	Elite enemy1;
	
	// draw everything here...
	window.draw(drawSprite(enemy1, 0.0, 0.0));


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