#include "world.h"

//Constructor
World::World()
{
}

//Destructor
World::~World()
{

}

//WorldLoop
void World::update()
{
	checkMouseEvents();
	rotateToVect(enemy->target);
	moveToTarget();
}

//Rotate sprite to target vector
void World::rotateToVect(sf::Vector2f target)
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

//move sprite to target vector
void World::moveToTarget()
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

//Checks for mouse events
void World::checkMouseEvents()
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