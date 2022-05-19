#pragma once
#include "LogicElement.h"
#include "Pin.h"

class DffGate : public LogicElement {
public:

	DffGate(sf::RenderWindow* window, float x, float y);
	int calculateState(LogicElement*);
	~DffGate();
	void drawObject(sf::RenderWindow*);
};

DffGate::DffGate(sf::RenderWindow* window, float x, float y)
{


	objID = DFF;
	this->window = window;
	numPins = 4;
	pins[0].setType(INPUT);
	pins[1].setType(INPUT);
	pins[2].setType(OUTPUT);
	pins[3].setType(OUTPUT);

	pins[0].dad = this;
	pins[1].dad = this;
	pins[2].dad = this;
	pins[3].dad = this;

	textures[0].loadFromFile("../assets/dff_edited.png");
	sprite.setTexture(textures[0]);
	sprite.setOrigin(37.0f, 30.0f);
	sprite.setPosition(x, y);
}
int DffGate::calculateState(LogicElement* x)
{
	return 0;
}
DffGate::~DffGate()
{

}


void DffGate::drawObject(sf::RenderWindow* window)
{
	window->draw(sprite);
}



