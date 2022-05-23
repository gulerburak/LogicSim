#pragma once
#include "LogicElement.h"
#include "Pin.h"

class NotGate : public LogicElement {
public:

	NotGate(sf::RenderWindow* window, float x, float y);
	int calculateState(LogicElement*);
	~NotGate();
	void drawObject(sf::RenderWindow*);
};

NotGate::NotGate(sf::RenderWindow* window, float x, float y)
{
	// assign special values of element
	objID = NOT;
	this->window = window;
	// assign pin values
	numPins = 2;
	pins[0].setType(INPUT);
	pins[1].setType(OUTPUT);

	pins[0].parent = this;
	pins[1].parent = this;

	textures[0].loadFromFile("../assets/NOT.png");
	sprite.setTexture(textures[0]);
	sprite.setOrigin(50.0f, 30.0f);
	sprite.setPosition(x, y);
}

int NotGate::calculateState(LogicElement* x)
{
	// reverse the input
	(x->pins[0].getState()) ? x->pins[1].setState(0) : x->pins[1].setState(1);
	return x->pins[1].getState();
}

NotGate::~NotGate()
{
	delete next;
}

void NotGate::drawObject(sf::RenderWindow* window)
{
	window->draw(sprite);
}



