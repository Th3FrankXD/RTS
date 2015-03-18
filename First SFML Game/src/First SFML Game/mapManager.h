class Map
{
public:
	TileSet* tileSet;
	int height;
	int width;
	std::vector<std::vector<int>> data;
	void createMap(Map* map, std::string mapName);
};

class TileSet
{
public:
	std::string image;
	int imageHeight;
	int imageWidth;
	int tileHeight;
	int tileWidth;
	std::vector<int> data;
};