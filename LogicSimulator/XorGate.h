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


	objID = XOR;
	this->window = window;
	numPins = 3;
	pins[0].setType(INPUT);
	pins[1].setType(INPUT);
	pins[2].setType(OUTPUT);

	pins[0].dad = this;
	pins[1].dad = this;
	pins[2].dad = this;

	textures[0].loadFromFile("../assets/XOR.png");
	sprite.setTexture(textures[0]);
	sprite.setOrigin(50.0f, 30.0f);
	sprite.setPosition(x, y);
}
int XorGate::calculateState(LogicElement* x)
{
	x->pins[2].setState(x->pins[0].getState() ^ x->pins[1].getState());
	return x->pins[2].getState();

}
XorGate::~XorGate()
{

}


void XorGate::drawObject(sf::RenderWindow* window)
{
	window->draw(sprite);
}



