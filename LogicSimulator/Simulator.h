#pragma once
#include "Object.h"
#include <SFML/Graphics.hpp>

class Simulator
{
public:
	sf::RenderWindow* window; //Pointer to SFML render window
	Object* objects; //Pointer to a list of objects on screen
};