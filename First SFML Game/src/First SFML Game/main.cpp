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

void drawSprite(Elite obj, sf::RenderWindow window)
{
	//texture = setTexture(obj.texture);
	//sprite = createSprite(texture);

	//window.draw(sprite);

	window.draw(createSprite(setTexture(obj.texture)));
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
	drawSprite(enemy1, window);

	// draw everything here...
	// window.draw(...);

	// end the current frame
	window.display();
}


int main()
{
	World world;
	Render renderer;
	
	Elite enemy1;
	Spartan ally1;
	
	while (true)
	{
		world.update();
		renderer.update(world);
	}
}