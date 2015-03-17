#include <iostream>
#include <vector>

class Map
{
public:
	std::vector<int> data;
	void createMap(Map* map, std::string mapName);
};