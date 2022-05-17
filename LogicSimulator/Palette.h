#pragma once
#include "Object.h"
#include "AndGate.h"
#include "OrGate.h"
#include "XorGate.h"
#include "NotGate.h"
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
	OrGate *OR;
	NotGate *NOT;
	XorGate* XOR;

	
public:
	Palette(sf::RenderWindow* window)	
	{	
		AND = new AndGate(window);
		OR = new OrGate(window);
		NOT = new NotGate(window);
		XOR = new XorGate(window);
		AND->sprite.setPosition(10, 50);
		AND->next = OR;
		OR->sprite.setPosition(10, 150);
		OR->next = NOT;
		NOT->sprite.setPosition(10, 250);
		NOT->next = XOR;
		XOR->sprite.setPosition(10, 350);
		XOR->next = nullptr;
	}
	Object* getTop()
	{
		return AND;
	}
	
};