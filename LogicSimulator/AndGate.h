#pragma once
#include "LogicElement.h"

class AndGate : public LogicElement {
public:
	AndGate(sf::RenderWindow* window);
	~AndGate();
	void connectPin1(Object*);
	void drawObject(sf::RenderWindow*);
};

AndGate::AndGate(sf::RenderWindow* window)
{
	objID = AND;
	this->window = window;
	numPins = 3;
	textures[0].loadFromFile("../assets/AND.png");
	sprite.setTexture(textures[0]);
	//sprite.setOrigin(49.0f, 30.0f);
}

AndGate::~AndGate()
{
}

void AndGate::connectPin1(Object* in)
{
	
}

void AndGate::drawObject(sf::RenderWindow* window)
{
	window->draw(sprite);
}
