#pragma once
#include <SFML/Graphics.hpp>
#include "Object.h"
#include "Pin.h"
#include "LogicElement.h"

class Wire: public Object {
	sf::Vertex line[2];
	Pin* pins[2];
public:
	Wire(float, float, sf::RenderWindow*, Pin*);
	~Wire();
	
	void setStartofWire(Pin*, float, float);
	void setEndOfWire(Pin*, float, float);

	Pin* getPinPtr(int);
	void drawObject(sf::RenderWindow* window);
};

Wire::Wire(float x, float y, sf::RenderWindow* window, Pin* start)
{
	objID = WIREclass;
	this->window = window;
	selected = false;
	state = 0;
	next = nullptr;

	//connect start of the wire
	pins[0] = start;
	line[0].position = sf::Vector2f(x, y);
	pins[1] = nullptr;
	line[1].position = sf::Vector2f(x, y);
	
	count++;
}

Wire::~Wire()
{
	count--;
}

void Wire::setStartofWire(Pin* start, float x, float y)
{
	pins[0] = start;
	line[0].position = sf::Vector2f(x, y);
}

void Wire::setEndOfWire(Pin* end, float x, float y)
{
	pins[1] = end;
	line[1].position = sf::Vector2f(x, y);
}

Pin* Wire::getPinPtr(int index)
{
	return pins[index];
}

void Wire::drawObject(sf::RenderWindow* window)
{
	// draw line of wire
	line[0].color = sf::Color(220, 20, 60);
	line[1].color = sf::Color(220, 20, 60);
	window->draw(line, 2, sf::Lines);
}