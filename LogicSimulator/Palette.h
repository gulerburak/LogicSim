#pragma once
#include "Object.h"
#include "AndGate.h"
#include <SFML/Graphics.hpp>
using namespace std;

void drawPalette(sf::RenderWindow* window, Object* obj)
{
	while(obj != nullptr)
	{
		obj->drawObject(window);
		obj = obj->next;
	}
}

class Palette {
	AndGate *AND;
	AndGate *AND2;
	AndGate *AND3;
	
public:
	Palette(sf::RenderWindow* window)	
	{	
		AND = new AndGate(window);
		AND2 = new AndGate(window);
		AND3 = new AndGate(window);
		AND->sprite.setPosition(10, 50);
		AND->next = AND2;
		AND2->sprite.setPosition(10, 150);
		AND2->next = AND3;
		AND3->sprite.setPosition(10, 250);
		AND3->next = nullptr;
	}
	Object* getTop()
	{
		return AND;
	}
	
};