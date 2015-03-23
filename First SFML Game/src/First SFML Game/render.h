#include<SFML\Graphics.hpp>

class Render
{
public:
	Render();
	~Render();
	void update(World& world);
	sf::Sprite* drawSprite(const sf::Texture* texture, sf::Vector2f location, float rotation = 0, sf::Color color = sf::Color(255, 255, 255), std::string origin = "");
	void drawMap(sf::RenderWindow* window, sf::View view);
	void zoomView(int mouseWheel);
};

class MiniMap
{
public:
	MiniMap();
	~MiniMap();
	void drawMiniMap(sf::RenderWindow* window);
	sf::Vector2f getMiniMapSize();
};