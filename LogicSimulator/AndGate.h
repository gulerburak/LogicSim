#pragma once
#include "LogicElement.h"
#include "Pin.h"

class AndGate : public LogicElement {
public:
	//AndGate(sf::RenderWindow* window);
	
	AndGate(sf::RenderWindow* window, float x, float y);
	int calculateState(LogicElement*);
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
	
	
	objID = AND;
	this->window = window;
	numPins = 3;
	pins[0].setType(INPUT);
	pins[1].setType(INPUT);
	pins[2].setType(OUTPUT);
	
	pins[0].dad = this;
	pins[1].dad = this;
	pins[2].dad = this;
	
	textures[0].loadFromFile("../assets/AND.png");
	sprite.setTexture(textures[0]);
	sprite.setOrigin(50.0f, 30.0f);
	sprite.setPosition(x, y);
}
int AndGate::calculateState(LogicElement* x)
{
	x->pins[2].setState(x->pins[0].getState() * x->pins[1].getState());
	return x->pins[2].getState();

}
AndGate::~AndGate()
{
	
}


void AndGate::drawObject(sf::RenderWindow* window)
{
	window->draw(sprite);
}
