#pragma once
#include "LogicElement.h"

class AndGate : public LogicElement {
public:
	//AndGate(sf::RenderWindow* window);
	AndGate(sf::RenderWindow* window, float x, float y);
	~AndGate();
	void drawObject(sf::RenderWindow*);
};


//AndGate::AndGate(sf::RenderWindow* window) 
//{
//	objID = AND;
//	this->window = window;
//	numPins = 3;
//	textures[0].loadFromFile("../assets/AND.png");
//	sprite.setTexture(textures[0]);
//	//sprite.setOrigin(49.0f, 30.0f);
//}

AndGate::AndGate(sf::RenderWindow* window, float x, float y) 
{
	setPinsDad(this);
	
	objID = AND;
	this->window = window;
	numPins = 3;
	textures[0].loadFromFile("../assets/AND.png");
	sprite.setTexture(textures[0]);
	sprite.setOrigin(50.0f, 30.0f);
	sprite.setPosition(x, y);
}

AndGate::~AndGate()
{
	
}


void AndGate::drawObject(sf::RenderWindow* window)
{
	window->draw(sprite);
}
