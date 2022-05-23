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
	// assign pin values
	objID = DFF;
	this->window = window;
	// assign pin values
	numPins = 4;
	pins[0].setType(INPUT);
	pins[1].setType(INPUT);
	pins[2].setType(OUTPUT);
	pins[3].setType(OUTPUT);

	pins[0].parent = this;
	pins[1].parent = this;
	pins[2].parent = this;
	pins[3].parent = this;

	textures[0].loadFromFile("../assets/dff_edited.png");
	sprite.setTexture(textures[0]);
	sprite.setOrigin(37.0f, 30.0f);
	sprite.setPosition(x, y);
}

int DffGate::calculateState(LogicElement* x)
{
	
	int prev2 = x->pins[2].getState();
	int prev3 = x->pins[3].getState();//previous Q values
	prev2 = 0;
	prev3 = 1;//initial condition
	if (x->pins[1].getState() == 1) {
		if (x->pins[0].getState() == 0) {
			x->pins[2].setState(0);
			x->pins[3].setState(1);
			
			if (&(x->pins[2])) {
				return x->pins[2].getState();
			}
			else if (&(x->pins[3])) {
				return x->pins[3].getState();
			}
			
		}
		else if(x->pins[0].getState() == 1) {
			x->pins[2].setState(1);
			x->pins[3].setState(0);
			if (&(x->pins[2])) {
				return x->pins[2].getState();
			}
			else if (&(x->pins[3])) {
				return x->pins[3].getState();
			}
		}
	}
	else if(x->pins[1].getState() == 0) {
		x->pins[2].setState(prev2);
		x->pins[3].setState(prev3);
		if (&(x->pins[2])) {
			return x->pins[2].getState();
		}
		else if (&(x->pins[3])) {
			return x->pins[3].getState();
		}
	}
}


DffGate::~DffGate()
{
	delete next;
}


void DffGate::drawObject(sf::RenderWindow* window)
{
	window->draw(sprite);
}



