#pragma once
#include "LogicElement.h"
#include "Pin.h"
#include <SFML/Graphics.hpp>

class Clock : public LogicElement
{
	//sf::Clock clock;
public:
	Clock(sf::RenderWindow* window, float, float);
	int calculateState(LogicElement*);
	~Clock();
	void drawObject(sf::RenderWindow*);
};

Clock::Clock(sf::RenderWindow* window, float x, float y)
{

	objID = CLOCK;
	this->window = window;
	numPins = 1;
	pins[0].setType(OUTPUT);
	pins[0].setState(1);
	state = 1;
	pins[0].dad = this;
	textures[0].loadFromFile("../assets/CLOCK.png");
	sprite.setTexture(textures[0]);
	sprite.setOrigin(30.0f, 30.0f);
	sprite.setPosition(x, y);
}

int Clock::calculateState(LogicElement* x)
{
	x->pins[0].setState(state);
	return x->pins[0].getState();
	
}

void Clock::drawObject(sf::RenderWindow*)
{
	window->draw(sprite);
}
Clock::~Clock() {

}