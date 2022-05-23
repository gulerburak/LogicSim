#pragma once
#include "LogicElement.h"
#include "Pin.h"

class XorGate : public LogicElement {
	
public:
	XorGate(sf::RenderWindow* window, float x, float y);
	int calculateState(LogicElement*);
	~XorGate();
	void drawObject(sf::RenderWindow*);
};

XorGate::XorGate(sf::RenderWindow* window, float x, float y)
{
	// assign special values of element
	objID = XOR;
	this->window = window;
	
	// assign pin values
	numPins = 3;
	pins[0].setType(INPUT);
	pins[1].setType(INPUT);
	pins[2].setType(OUTPUT);

	pins[0].parent = this;
	pins[1].parent = this;
	pins[2].parent = this;

	textures[0].loadFromFile("../assets/XOR.png");
	sprite.setTexture(textures[0]);
	sprite.setOrigin(50.0f, 30.0f);
	sprite.setPosition(x, y);
}
int XorGate::calculateState(LogicElement* x)
{
	// apply XOR operator to the input pins
	x->pins[2].setState(x->pins[0].getState() ^ x->pins[1].getState());
	return x->pins[2].getState();
}

XorGate::~XorGate()
{
	delete next;
}

void XorGate::drawObject(sf::RenderWindow* window)
{
	window->draw(sprite);
}



