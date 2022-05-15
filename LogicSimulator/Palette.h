#pragma once
#include "Object.h"
#include "AndGate.h"
#include <SFML/Graphics.hpp>
using namespace std;

void drawPalette(sf::RenderWindow* window, Object* obj)
{
	while(obj != nullptr)
	{
		//if object is selected, draw a red border around it
		if (obj->selected)
		{
			sf::RectangleShape rect(sf::Vector2f(99.0f,61.0f));
			rect.setFillColor(sf::Color::Transparent);
			rect.setOutlineColor(sf::Color::Red);
			rect.setOutlineThickness(2.0f);
			rect.setPosition(obj->sprite.getPosition().x,
							 obj->sprite.getPosition().y);
			rect.setOrigin(50.0f, 30.0f);
			window->draw(rect);	
		}
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