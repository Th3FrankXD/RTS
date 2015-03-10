#include <SFML/Graphics.hpp>
#include "textureCollector.h"
 
TextureCollection::TextureCollection()
{
       wrath = new sf::Texture;
       wrath->loadFromFile("wrath.png");

	   grass = new sf::Texture;
	   grass->loadFromFile("grass.jpg");

	   rock = new sf::Texture;
	   rock->loadFromFile("rock.jpg");

	   tree = new sf::Texture;
	   tree->loadFromFile("tree.png");
}
 
TextureCollection::~TextureCollection()
{
       delete wrath;
	   delete grass;
	   delete rock;
	   delete tree;
}