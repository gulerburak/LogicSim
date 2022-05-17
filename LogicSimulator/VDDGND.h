#pragma once 
#include "LogicElement.h"

class Logic_1 : public LogicElement
{
public:
	Logic_1(sf::RenderWindow* window, float, float);
	~Logic_1();
	void drawObject(sf::RenderWindow*);
};

class Logic_0 : public LogicElement
{
public:
	Logic_0(sf::RenderWindow* window, float, float);
	~Logic_0();
	void drawObject(sf::RenderWindow*);
};

Logic_1::Logic_1(sf::RenderWindow* window, float x,float y)
{
	setPinsDad(this);
	objID = Logic1;
	this->window = window;
	numPins = 1;
	textures[0].loadFromFile("../assets/VDD.png");
	sprite.setTexture(textures[0]);
	sprite.setOrigin(30.0f, 30.0f);
	sprite.setPosition(x, y);
}

Logic_0::Logic_0(sf::RenderWindow* window, float x,float y)
{
	setPinsDad(this);
	objID = Logic0;
	this->window = window;
	numPins = 1;
	textures[0].loadFromFile("../assets/GND.png");
	sprite.setTexture(textures[0]);
	sprite.setOrigin(30.0f, 30.0f);
	sprite.setPosition(x, y);
}

void Logic_1::drawObject(sf::RenderWindow*)
{
	window->draw(sprite);
}
void Logic_0::drawObject(sf::RenderWindow*)
{
	window->draw(sprite);
}
