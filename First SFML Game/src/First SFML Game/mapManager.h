#include <SFML/Graphics.hpp>
class TileSet
{
public:
	TileSet();
	~TileSet();
	std::string image;
	int imageHeight;
	int imageWidth;
	int tileHeight;
	int tileWidth;
	std::vector<sf::Texture*> data;
	void setTextureData();
};

class Map
{
public:
	Map();
	~Map();
	TileSet* tileSet = new TileSet;
	int height;
	int width;
	std::vector<std::vector<int>> data;
	void createMap(Map* map, std::string mapName);
	sf::Texture* getTexture(int x, int y);
};