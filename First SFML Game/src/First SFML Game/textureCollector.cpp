#include <SFML/Graphics.hpp>
#include "textureCollector.h"
 
TextureCollection::TextureCollection()
{
       wrath = new sf::Texture;
       wrath->loadFromFile("wrath.png");
}
 
TextureCollection::~TextureCollection()
{
       delete wrath;
}