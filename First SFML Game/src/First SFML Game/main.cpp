#include <SFML/Graphics.hpp>
#include <thread>
#include <iostream>
#include "gameObjects.h"

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
	std::cout << enemy1.texture;
	std::cout << ally1.texture;

	while (true)
	{
		world.update();
		renderer.update(world);
	}
}