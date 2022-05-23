#pragma once
#include "LogicElement.h"
#include "Pin.h"

class OrGate : public LogicElement {
public:

	OrGate(sf::RenderWindow* window, float x, float y);
	int calculateState(LogicElement*);
	~OrGate();
	void drawObject(sf::RenderWindow*);
};

OrGate::OrGate(sf::RenderWindow* window, float x, float y)
{
	// assign special values of element
	objID = OR;
	this->window = window;
	// assign pin values
	numPins = 3;
	pins[0].setType(INPUT);
	pins[1].setType(INPUT);
	pins[2].setType(OUTPUT);

	pins[0].parent = this;
	pins[1].parent = this;
	pins[2].parent = this;

	textures[0].loadFromFile("../assets/OR.png");
	sprite.setTexture(textures[0]);
	sprite.setOrigin(50.0f, 30.0f);
	sprite.setPosition(x, y);
}

int OrGate::calculateState(LogicElement* x)
{
	// apply OR operator to the input pins
	x->pins[2].setState(x->pins[0].getState() + x->pins[1].getState());
	return x->pins[2].getState();

}
OrGate::~OrGate()
{
	delete next;
}

void OrGate::drawObject(sf::RenderWindow* window)
{
	window->draw(sprite);
}

