#pragma once
#include "Object.h"
#include "AndGate.h"
#include "OrGate.h"
#include "NotGate.h"
#include "XorGate.h"
#include "Dff.h"
#include "Clock.h"
#include "VDDGND.h"
#include "LED.h"
#include "StartStopButton.h"
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
	OrGate* OR;
	NotGate* NOT;
	XorGate* XOR;
	DffGate* DFF;
	Clock* CLOCK;
	Logic_1*L1;
	Logic_0* L0;
	LED* led;
	StartStopButton* startstop;
	
public:
	Palette(sf::RenderWindow* window)	
	{	
		
		L1 = new Logic_1(window, 75, 700);
		L0 = new Logic_0(window, 75, 800);
		led = new LED(window, 75, 900);
		led->state = true;
		AND = new AndGate(window, 75, 100);
		OR = new OrGate(window, 75, 200);
		NOT = new NotGate(window, 75, 300);
		XOR = new XorGate(window, 75, 400);
		DFF = new DffGate(window, 75, 500);
		CLOCK = new Clock(window, 75, 600);
		startstop = new StartStopButton(window, 150, 0);

		
		
		AND->next = OR;
		OR->next = NOT;
		NOT->next = XOR;
		XOR->next = DFF;
		DFF->next = CLOCK;
		CLOCK->next = L1;
		L1->next=L0;
		L0->next = led;
		led->next = startstop;
		startstop->next = nullptr;
	}
	Object* getTop()
	{
		return AND;
	}
	Object* GetObjectOnClick(float, float);
};

Object* Palette::GetObjectOnClick(float x, float y)
{
	Object* temp = AND;
	while (temp != nullptr)
	{

		if (temp->sprite.getGlobalBounds().contains(x, y))
			return temp;

		temp = temp->next;
	}
	return nullptr;

}