#include <string>
#include "gameObjects.h"

Unit::Unit(std::string texture) : texture(texture)
{
}


Elite::Elite() :Unit("elite.png")
{
}


Spartan::Spartan() :Unit("elite.png")
{
}