#pragma once 
#include "LogicElement.h"

class Logic_0 : LogicElement
{
	Logic_0(sf::RenderWindow* window);
	Logic_0(sf::RenderWindow* window, float, float);
	~Logic_0();
	void drawObject(sf::RenderWindow*);
};