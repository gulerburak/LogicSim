#pragma once
#include <SFML/Graphics.hpp>
#include "Object.h"
#include "Pin.h"
#include "LogicElement.h"

class Wire: public Object {
	sf::Vertex line[2]; // start and end of wire
	Pin* pins[2]; // pins connected to wire
public:
	Wire(float, float, sf::RenderWindow*, Pin*);
	~Wire();
	void setStartofWire(Pin*, float, float);
	void setEndOfWire(Pin*, float, float);
	sf::Vector2f getWireLine(int);
	Pin* getPinPtr(int);
	void drawObject(sf::RenderWindow* window);
	void connectPins();
};

Wire::Wire(float x, float y, sf::RenderWindow* window, Pin* start)
{
	objID = WIREtype;
	this->window = window;
	selected = false;
	state = 0;
	next = nullptr;

	//connect start of the wire
	pins[0] = start;
	
	line[0].position = sf::Vector2f(x, y);
	
	pins[1] = nullptr;
	line[1].position = sf::Vector2f(x, y);
}

Wire::~Wire()
{
	delete pins, next;
}

void Wire::setEndOfWire(Pin* end, float x, float y)
{
	pins[1] = end;
	line[1].position = sf::Vector2f(x, y);
}
void Wire::connectPins()
{
	// assign pins to each other's connected pins
	pins[0]->connectedTo[pins[0]->numConnections - 1] = pins[1];
	pins[1]->connectedTo[pins[1]->numConnections - 1] = pins[0];
}

Pin* Wire::getPinPtr(int index)
{
	return pins[index];
}

sf::Vector2f Wire::getWireLine(int index) 
{
	return line[index].position;
}

void Wire::drawObject(sf::RenderWindow* window)
{
	// draw line of wire
	if (selected) {
		line[0].color = sf::Color(220, 20, 20,220);
		line[1].color = sf::Color(220, 20, 20,220);
	}
	else {
		line[0].color = sf::Color(20, 20, 220);
		line[1].color = sf::Color(20, 20, 220);
	}
	
	window->draw(line, 2, sf::Lines);
}