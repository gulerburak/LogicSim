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


	objID = OR;
	this->window = window;
	numPins = 3;
	pins[0].setType(INPUT);
	pins[1].setType(INPUT);
	pins[2].setType(OUTPUT);

	pins[0].dad = this;
	pins[1].dad = this;
	pins[2].dad = this;

	textures[0].loadFromFile("../assets/OR.png");
	sprite.setTexture(textures[0]);
	sprite.setOrigin(50.0f, 30.0f);
	sprite.setPosition(x, y);
}
int OrGate::calculateState(LogicElement* x)
{
	x->pins[2].setState(x->pins[0].getState() + x->pins[1].getState());
	return x->pins[2].getState();

}
OrGate::~OrGate()
{

}


void OrGate::drawObject(sf::RenderWindow* window)
{
	window->draw(sprite);
}

