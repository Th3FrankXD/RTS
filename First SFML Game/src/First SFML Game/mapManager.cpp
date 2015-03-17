#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <array>
#include "mapManager.h"
#include "rapidjson/document.h"
#include "rapidjson/writer.h"
#include "rapidjson/stringbuffer.h"

using namespace rapidjson;

void getFile(std::string* txt, std::string mapName)
{
	std::ifstream openFile(mapName);
	if (openFile.is_open())
	{
		while (!openFile.eof())
		{
			std::string currentChar;
			openFile >> currentChar;

			*txt += currentChar;
		}
		openFile.close();
	}
}

void parser(std::string* txt, Map* map)
{
	Document doc;
	doc.Parse(txt->c_str());
	StringBuffer buffer;
	Writer<StringBuffer> writer(buffer);
	doc.Accept(writer);

	assert(doc["layers"][0]["data"].IsArray());

	const Value& mapArray = doc["layers"][0]["data"];
	assert(mapArray.IsArray());

	for (int i = 0; i < mapArray.Size(); i++)
	{
		std::cout << doc["layers"][0]["data"][i].GetInt() << std::endl;
		//std::cout << doc["layers"][0]["data"][i].GetInt() << std::endl;
	}

	//std::array<int, 6> jsonData = ;
	//map->data = std::vector<int>(std::begin(jsonData), std::end(jsonData));
	//std::cout << buffer.GetString() << std::endl;
}

void Map::createMap(Map* map, std::string mapName)
{
	std::string txt;
	getFile(&txt, mapName);
	parser(&txt, map);
}