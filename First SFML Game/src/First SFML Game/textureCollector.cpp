#include <SFML/Graphics.hpp>
#include "textureCollector.h"
 
TextureCollection::TextureCollection()
{
       elite = new sf::Texture;
       elite->loadFromFile("elite.png");
}
 
TextureCollection::~TextureCollection()
{
       delete elite;
}