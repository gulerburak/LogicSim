#pragma once
#include "Object.h"
#include "AndGate.h"
#include "VDDGND.h"
#include "LED.h"
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
	Logic_1 *L1;
	Logic_0* L0;
	LED* led;
	
public:
	Palette(sf::RenderWindow* window)	
	{	
		
		L1 = new Logic_1(window, 75, 100);
		L0 = new Logic_0(window, 75, 200);
		led = new LED(window, 75, 300);
		led->state = true;
		AND = new AndGate(window, 75, 400);
		
		L1->next = L0;
		L0->next = led;
		led->next = AND;
		AND->next = nullptr;
	}
	Object* getTop()
	{
		return L1;
	}
	Object* GetObjectOnClick(float, float);
};

Object* Palette::GetObjectOnClick(float x, float y)
{
	Object* temp = L1;
	while (temp != nullptr)
	{

		if (temp->sprite.getGlobalBounds().contains(x, y))
			return temp;

		temp = temp->next;
	}
	return nullptr;

}