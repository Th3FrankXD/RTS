class Map
{
public:
	void createMap(Map* map, std::string mapName);
	int height;
	int width;
	std::vector<std::vector<int>> data;
};

class TileSet
{
public:
	std::string image;
	int imageHeight;
	int imageWidth;
	int tileHeight = 32;
	int tileWidth = 32;
	std::vector<int> data;
};