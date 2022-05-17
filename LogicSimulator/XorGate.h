#pragma once
#include "LogicElement.h"

class XorGate : public LogicElement {
public:
	XorGate(sf::RenderWindow* window);
	XorGate(sf::RenderWindow* window, float x, float y);
	~XorGate();
	void drawObject(sf::RenderWindow*);
	void setPinsDad();
};

void XorGate::setPinsDad()
{
	for (int i = 0; i < numPins; i++)
	{
		pins[i].dad = this;
	}

}
XorGate::XorGate(sf::RenderWindow* window)
{
	objID = XOR;
	this->window = window;
	numPins = 3;
	textures[0].loadFromFile("../assets/XOR.png");
	sprite.setTexture(textures[0]);
	//sprite.setOrigin(49.0f, 30.0f);
	count++;
}

XorGate::XorGate(sf::RenderWindow* window, float x, float y)
{
	objID = XOR;
	this->window = window;
	numPins = 3;
	textures[0].loadFromFile("../assets/XOR.png");
	sprite.setTexture(textures[0]);
	sprite.setPosition(x, y);
	sprite.setOrigin(50.0f, 30.0f);
}

XorGate::~XorGate()
{

}


void XorGate::drawObject(sf::RenderWindow* window)
{
	window->draw(sprite);
}
