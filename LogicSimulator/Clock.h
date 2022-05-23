#pragma once
#include "LogicElement.h"
#include "Pin.h"
#include <SFML/Graphics.hpp>

class Clock : public LogicElement
{
public:
	Clock(sf::RenderWindow* window, float, float);
	int calculateState(LogicElement*);
	~Clock();
	void drawObject(sf::RenderWindow*);
};

Clock::Clock(sf::RenderWindow* window, float x, float y)
{
	// assign special values of element
	objID = CLOCK;
	this->window = window;
	// assign pin values
	numPins = 1;
	pins[0].setType(OUTPUT);
	pins[0].setState(1);
	state = 0;
	pins[0].parent = this;
	textures[0].loadFromFile("../assets/CLOCK.png");
	sprite.setTexture(textures[0]);
	sprite.setOrigin(30.0f, 30.0f);
	sprite.setPosition(x, y);
}

int Clock::calculateState(LogicElement* x)
{
	// return assigen state of clock as state
	x->pins[0].setState(state);
	return x->pins[0].getState();
	
}

void Clock::drawObject(sf::RenderWindow*)
{
	window->draw(sprite);
}

Clock::~Clock() {

}