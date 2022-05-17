#pragma once
#include "LogicElement.h"

class NotGate : public LogicElement {
public:
	NotGate(sf::RenderWindow* window);
	NotGate(sf::RenderWindow* window, float x, float y);
	~NotGate();
	void drawObject(sf::RenderWindow*);
	void setPinsDad();
};

void NotGate::setPinsDad()
{
	for (int i = 0; i < numPins; i++)
	{
		pins[i].dad = this;
	}

}
NotGate::NotGate(sf::RenderWindow* window)
{
	objID = NOT;
	this->window = window;
	numPins = 2;
	textures[0].loadFromFile("../assets/NOT.png");
	sprite.setTexture(textures[0]);
	//sprite.setOrigin(49.0f, 30.0f);
	count++;
}

NotGate::NotGate(sf::RenderWindow* window, float x, float y)
{
	objID = NOT;
	this->window = window;
	numPins = 2;
	textures[0].loadFromFile("../assets/NOT.png");
	sprite.setTexture(textures[0]);
	sprite.setPosition(x, y);
	sprite.setOrigin(50.0f, 30.0f);
}

NotGate::~NotGate()
{

}


void NotGate::drawObject(sf::RenderWindow* window)
{
	window->draw(sprite);
}

