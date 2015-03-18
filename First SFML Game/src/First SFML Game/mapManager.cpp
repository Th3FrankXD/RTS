#include <iostream>
#include <fstream>
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

	const Value& mapArray = doc["layers"][0]["data"];
	map->height = doc["layers"][0]["height"].GetInt();
	map->width = doc["layers"][0]["width"].GetInt();

	map->tileSet->image = doc["tilesets"][0]["image"].GetString();
	map->tileSet->tileHeight = doc["tilesets"][0]["tileheight"].GetInt();
	map->tileSet->tileWidth = doc["tilesets"][0]["tilewidth"].GetInt();
	map->tileSet->imageHeight = doc["tilesets"][0]["imageheight"].GetInt();
	map->tileSet->imageWidth = doc["tilesets"][0]["imagewidth"].GetInt();

	int itr = 0;
	for (int i = 0; i < map->height; i++)
	{
		std::vector<int> row;
		for (int j = 0; j < map->width; j++)
		{
			row.push_back(mapArray[itr].GetInt());
			itr++;
		}
		map->data.push_back(row);
	}
}

void Map::createMap(Map* map, std::string mapName)
{
	std::string txt;
	getFile(&txt, mapName);
	parser(&txt, map);
}