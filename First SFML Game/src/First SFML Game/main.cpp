#include <SFML/Graphics.hpp>
#include <iostream>
#include <fstream>
#include <string>
#include <cmath>
#include <windows.h>
#include <unordered_map>
#include "gameObjects.h"
#include "mapManager.h"

extern TextureCollection textures;

float resX = 1280;
float resY = 720;

int fpsCap = 60;

bool captureMap = true;
int miniMapXOffSet;
int miniMapYOffSet;

sf::Texture* miniMapTex = new sf::Texture;

sf::Vector2i mapLoc = sf::Vector2i(0, 0);

Wrath* enemy = new Wrath;
Map* map = new Map;

sf::RenderWindow window(sf::VideoMode(resX, resY), "my rts");
sf::View view;
sf::View miniMap;

sf::Sprite* drawSprite(const sf::Texture* texture, sf::Vector2f location, float rotation = 0, sf::Color color = sf::Color(255, 255, 255), std::string origin = "")
{
	sf::Sprite* sprite = new sf::Sprite;

	sprite->setTexture(*texture);
	sprite->setColor(color);
	sprite->setScale(enemy->scale);

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

void rotateToVect(sf::Vector2f target)
{
	const float PI = 3.14159265;

	float dx = enemy->location.x - target.x;
	float dy = enemy->location.y - target.y;

	float rotation = (atan2(dy, dx)) * 180 / PI - 90;
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

void zoomView(int mouseWheel)
{
	if (mouseWheel < 0)
	{
		view.zoom(1.1);
	}
	if (mouseWheel > 0)
	{
		view.zoom(0.9);
	}
}

void checkMouseEvents()
{
	sf::Vector2f viewSize = view.getSize();
	sf::Vector2f windowSize = sf::Vector2f(window.getSize().x, window.getSize().y);
	float zoomLevel = abs(viewSize.x - viewSize.y) / 100;

	if (sf::Mouse::getPosition(window).x <= 0 && view.getCenter().x - viewSize.x / 2 > 0)
	{
		view.move(-(2 * zoomLevel), 0);
	}
	if (sf::Mouse::getPosition(window).x >= windowSize.x && view.getCenter().x + viewSize.x / 2 < map->width * map->tileSet->tileWidth)
	{
		view.move((2 * zoomLevel), 0);
	}
	if (sf::Mouse::getPosition(window).y <= 0 && view.getCenter().y - viewSize.y / 2 > 0)
	{
		view.move(0, -(2 * zoomLevel));
	}
	if (sf::Mouse::getPosition(window).y >= windowSize.y && view.getCenter().y + viewSize.y / 2 < map->height * map->tileSet->tileHeight)
	{
		view.move(0, (2 * zoomLevel));
	}

	sf::Vector2f mouseCoords = window.mapPixelToCoords(sf::Mouse::getPosition(window));
	if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
	{
		if (abs(mouseCoords.x - enemy->location.x) < 30 &&
			abs(mouseCoords.y - enemy->location.y) < 30)
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
			enemy->target = mouseCoords;
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


void drawMap(sf::RenderWindow* window, sf::View view)
{
	sf::Sprite tile;
	int itr = 0;
	int location;
	int maxWidth = nearbyint((view.getCenter().x + view.getSize().x / 2) / map->tileSet->tileWidth) + 1;
	int minWidth = nearbyint((view.getCenter().x - view.getSize().x / 2) / map->tileSet->tileWidth) - 1;
	int maxHeight = nearbyint((view.getCenter().y + view.getSize().y / 2) / map->tileSet->tileHeight) + 1;
	int minHeight = nearbyint((view.getCenter().y - view.getSize().y / 2) / map->tileSet->tileHeight) - 1;

	for (int y = minHeight; y < maxHeight && y < map->height; y++)
	{
		if (y < 0)
		{
			y = 0;
		}
		for (int x = minWidth; x < maxWidth && x < map->width; x++)
		{
			if (x < 0)
			{
				x = 0;
			}
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

void drawMiniMap(sf::RenderWindow* window)
{
	sf::Sprite miniMapSprite;
	miniMapSprite.setTexture(*miniMapTex);
	miniMapSprite.setPosition(sf::Vector2f(0, 0));
	window->draw(miniMapSprite);
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
		switch (event.type)
		{
		case sf::Event::Closed:
			window.close();
		case sf::Event::MouseWheelMoved:
			zoomView(event.mouseWheel.delta);
		}
	}
	// clear the window with black color
	window.clear(sf::Color::Black);

	// draw everything here...
	window.setView(miniMap);
	if (captureMap == true)
	{
		drawMap(&window, miniMap);
		sf::Image miniMapBG = window.capture();
		//miniMapBG.saveToFile("minimapcheck.jpg");
		miniMapTex->loadFromImage(miniMapBG, sf::IntRect(miniMapBG.getSize().x * 0.8, 0, miniMapBG.getSize().x * 0.2, miniMapBG.getSize().y * (resX / 5 / resY)));
		miniMap.setSize(miniMapBG.getSize().x * 0.2, miniMapBG.getSize().y * (resX / 5 / resY));
		miniMap.setCenter(sf::Vector2f(miniMap.getSize().x / 2, miniMap.getSize().y / 2));
		
		sf::RectangleShape rect;
		rect.setSize(sf::Vector2f(miniMapBG.getSize().x, miniMapBG.getSize().y));
		window.draw(rect);

		captureMap = false;
	}
	drawMiniMap(&window);

	sf::RectangleShape rect;
	rect.setSize(sf::Vector2f(10, 10));
	sf::Vector2f currentLoc = sf::Vector2f(enemy->location.x / (map->width * map->tileSet->tileWidth / (resX / 5)) - 5, enemy->location.y / (map->height * map->tileSet->tileHeight / (resY * (resX / 5 / resY))) - 5);
	float rectXPos = resX * 0.2 * (miniMapXOffSet / (map->width * map->tileSet->tileWidth)) / float(2);
	float rectYPos = resY * (resX / 5 / resY) * (miniMapYOffSet / (map->height * map->tileSet->tileHeight)) / float(2);
	rect.setPosition(sf::Vector2f(currentLoc.x + rectXPos, currentLoc.y + rectYPos));
	window.draw(rect);

	window.setView(view);
	drawMap(&window, view);

	sf::Sprite* sprite = drawSprite(enemy->texture, enemy->location, enemy->rotation, enemy->color, "center");
	window.draw(*sprite);
	delete sprite;

	// end the current frame
	window.display();
}

sf::Vector2f getMiniMapSize()
{
	sf::Vector2f mapPixelSize = sf::Vector2f(map->width * map->tileSet->tileWidth, map->height * map->tileSet->tileHeight);
	sf::Vector2f miniMapSize = mapPixelSize;
	bool xIncrease = false;
	float miniMapRatio = float(mapPixelSize.x) / float(mapPixelSize.y);
	if (miniMapRatio < 1)
	{
		xIncrease = true;
	}

	if (xIncrease == true)
	{
		for (int i = 0; miniMapRatio < 1; i++)
		{
			miniMapSize.x++;
			miniMapRatio = float(miniMapSize.x) / float(miniMapSize.y);
			miniMapXOffSet++;
		}
	}
	else
	{
		for (int i = 0; miniMapRatio > 1; i++)
		{
			miniMapSize.y++;
			miniMapRatio = float(miniMapSize.x) / float(miniMapSize.y);
			miniMapYOffSet++;
		}
	}
	return miniMapSize;
}

int main()
{
	World world;
	Render renderer;

	map->createMap(map, "test.json");
	view.setViewport(sf::FloatRect(0, 0, 0.8f, 1.0f));
	view.setSize(sf::Vector2f(resX * 0.8, resY));
	miniMap.setViewport(sf::FloatRect(0.8f, 0.0f, 0.2f, resX / 5 / resY));
	miniMap.setSize(getMiniMapSize());
	miniMap.setCenter(sf::Vector2f(map->width * map->tileSet->tileWidth / 2, map->height * map->tileSet->tileHeight / 2));

	std::clock_t start;
	std::clock_t end;
	double sleepTime;
	int duration;

	enemy->scale.x = map->tileSet->tileWidth / float(32);
	enemy->scale.y = map->tileSet->tileHeight / float(32);

	enemy->speed = enemy->speed * enemy->scale.x;

	int skip = 0;
	while (true)
	{
		start = std::clock();

		world.update();
		renderer.update(world);
		window.setView(view);

		end = std::clock();

		duration = (end - start) / (CLOCKS_PER_SEC / 1000);
		if (skip > 10) {
			std::cout << duration << "ms" << std::endl;
			skip = 0;
		}
		else {
			skip++;
		}
		sleepTime = 1000 / fpsCap - duration;
		if (sleepTime > 0)
		{
			Sleep(sleepTime);
		}
	}
}