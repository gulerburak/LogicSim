#pragma once
#include "LogicElement.h"

class OrGate : public LogicElement {
public:
	OrGate(sf::RenderWindow* window);
	OrGate(sf::RenderWindow* window, float x, float y);
	~OrGate();
	void drawObject(sf::RenderWindow*);
	void setPinsDad();
};

void OrGate::setPinsDad()
{
	for (int i = 0; i < numPins; i++)
	{
		pins[i].dad = this;
	}

}
OrGate::OrGate(sf::RenderWindow* window)
{
	objID = OR;
	this->window = window;
	numPins = 3;
	textures[0].loadFromFile("../assets/OR.png");
	sprite.setTexture(textures[0]);
	//sprite.setOrigin(49.0f, 30.0f);
	count++;
}

OrGate::OrGate(sf::RenderWindow* window, float x, float y)
{
	objID = OR;
	this->window = window;
	numPins = 3;
	textures[0].loadFromFile("../assets/OR.png");
	sprite.setTexture(textures[0]);
	sprite.setPosition(x, y);
	sprite.setOrigin(50.0f, 30.0f);
}

OrGate::~OrGate()
{

}


void OrGate::drawObject(sf::RenderWindow* window)
{
	window->draw(sprite);
}
