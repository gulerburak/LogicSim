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
#include "Pin.h"
using namespace std;

void drawLinkedObjects(sf::RenderWindow* window, Object* obj)
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
	Logic_1* L1;
	Logic_0* L0;
	LED* led;
	StartStopButton* startstop;
	
public:
	Palette(sf::RenderWindow*);
	Object* getTop();
	Object* GetObjectOnClick(float, float);
};

Palette::Palette(sf::RenderWindow* window)
{
	// create tool palette objects
	AND = new AndGate(window, 75, 100);
	OR = new OrGate(window, 75, 200);
	NOT = new NotGate(window, 75, 300);
	XOR = new XorGate(window, 75, 400);
	DFF = new DffGate(window, 75, 500);
	CLOCK = new Clock(window, 75, 600);
	L1 = new Logic_1(window, 75, 700);
	L0 = new Logic_0(window, 75, 800);
	led = new LED(window, 75, 900);
	led->state = true; // LED on the palette is on.
	startstop = new StartStopButton(window, 150, 0);

	// assign palette objects to linked list
	AND->next = OR;
	OR->next = NOT;
	NOT->next = XOR;
	XOR->next = DFF;
	DFF->next = CLOCK;
	CLOCK->next = L1;
	L1->next = L0;
	L0->next = led;
	led->next = startstop;
	startstop->next = nullptr;
}

Object* Palette::getTop()
{
	// return the top object in the linked list
	return AND;
}

Object* Palette::GetObjectOnClick(float x, float y)
{
	// check if the click is on an object
	Object* temp = AND;
	while (temp != nullptr)
	{
		if (temp->sprite.getGlobalBounds().contains(x, y))
			return temp;
		temp = temp->next;
	}
	return nullptr;

}