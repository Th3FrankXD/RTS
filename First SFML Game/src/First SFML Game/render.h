#include<SFML\Graphics.hpp>
#include <iostream>
#include "world.h"
#include "gameObjects.h"//

Wrath* enemy;

class Render
{
public:
	sf::RenderWindow window;
	sf::View view;
	sf::View miniMapView;

public:
	Render(int resX, int resY, std::string name);
	~Render();
	void update(World& world);
	void drawSprite(sf::RenderWindow* window, const sf::Texture* texture, sf::Vector2f location, float rotation = 0, sf::Color color = sf::Color(255, 255, 255), std::string origin = "");
	void drawMap(sf::RenderWindow* window, sf::View view);
	void zoomView(int mouseWheel);

private:
	MiniMap miniMap;
};

class MiniMap
{
public:
	sf::View miniMap;
	bool captureMap = true;
	int miniMapXOffSet;
	int miniMapYOffSet;
	sf::Texture* miniMapTex = new sf::Texture;

public:
	MiniMap();
	~MiniMap();
	void drawMiniMap(sf::RenderWindow* window);
	sf::Vector2f getMiniMapSize();
	void createMiniMap();
};