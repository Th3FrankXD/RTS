#include "render.h"

//Constructor
Render::Render(int resX, int resY, std::string name)
{
	window = sf::RenderWindow(sf::VideoMode(resX, resY), name);
	window.setFramerateLimit(60);
	window.setVerticalSyncEnabled(true);
}

//Destructor
Render::~Render()
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
	window.setView(miniMapView);
	miniMap.createMiniMap(&window)
	miniMap.drawMiniMap(&window);

	window.setView(view);
	drawMap(&window, view);

	drawSprite(&window, enemy->texture, enemy->location, enemy->rotation, enemy->color, "center");

	// end the current frame
	window.display();
}

//Function to draw sprites
void Render::drawSprite(sf::RenderWindow* window ,const sf::Texture* texture, sf::Vector2f location, float rotation = 0, sf::Color color = sf::Color(255, 255, 255), std::string origin = "")
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

	window->draw(*sprite);
	delete sprite;
}

//Function for zooming in and out
void Render::zoomView(int mouseWheel)
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

//Function to draw the map (with culling)
void Render::drawMap(sf::RenderWindow* window, sf::View view)
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


/////////////////MiniMap///////////////////

//Constructor
MiniMap::MiniMap()
{
}

//Destructor
MiniMap::~MiniMap()
{
	delete miniMapTex;
}

//Creates the minimap
void MiniMap::createMiniMap(sf::RenderWindow window)
{
	if (captureMap == true)
	{
		drawMap(window, miniMap);
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
}

//Draw the minimap
void MiniMap::drawMiniMap(sf::RenderWindow* window)
{
	sf::Sprite miniMapSprite;
	miniMapSprite.setTexture(*miniMapTex);
	miniMapSprite.setPosition(sf::Vector2f(0, 0));
	window->draw(miniMapSprite);
}

//Calculates the size of the minimap to maintain a 1:1 ratio
sf::Vector2f MiniMap::getMiniMapSize()
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


///////////Minimap location stuff//////////////////////////////////
//sf::RectangleShape rect;
//rect.setSize(sf::Vector2f(10, 10));
//sf::Vector2f currentLoc = sf::Vector2f(128, 128);
//float rectXPos = resX * 0.2 * (miniMapXOffSet / (map->width * map->tileSet->tileWidth)) / float(2);
//float rectYPos = resY * (resX / 5 / resY) * (miniMapYOffSet / (map->height * map->tileSet->tileHeight)) / float(2);
//rect.setPosition(sf::Vector2f(currentLoc.x + rectXPos, currentLoc.y + rectYPos));
//window.draw(rect);
/////////////////////////////////////////////////////////////////