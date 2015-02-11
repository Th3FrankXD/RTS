#include <SFML/Graphics.hpp>
#include <thread>
#include <iostream>
#include "gameObjects.h"

sf::Texture setTexture(std::string texturePath)
{
	sf::Texture texture;
	if (!texture.loadFromFile(texturePath))
	{
		// error...
	}
	return texture;
}

sf::Sprite createSprite(sf::Texture texture)
{
	sf::Sprite sprite;
	sprite.setTexture(texture);
	return sprite;
}

sf::Sprite drawSprite(Elite obj, float xLoc, float yLoc, int rotation)
{
	sf::Vector2f location = sf::Vector2f(xLoc, yLoc);

	sf::Texture texture;
	sf::Sprite sprite;
	texture = setTexture(obj.texture);
	sprite = createSprite(texture);

	sprite.setPosition(location);
	sprite.setRotation(rotation);

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
	
	Elite enemy1;
	
	window.draw(drawSprite(enemy1, 0, 0, 0));

	// draw everything here...
	// window.draw(...);

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