#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>
#include "Wire.h"
using namespace std;
enum pinType { INPUT, OUTPUT };
enum pinState{ LOW, HIGH, HIGHZ };

class Pin 
{
protected:
	int index; // Index of the pin for an element
	// First input pin has index 0, second input pin has index 1, output pin has index 2, so on
	pinType type; // whether this pin is input or output
	int state; // Logic state of the signal on this pin 
	sf::Vector2f pos; // Screen position of the pin
	
public:

	Pin* connectedTo[5]; // List of other pins this pin is connected to
	Object* wires[5]; // Wires connected to this pin
	Object* parent; // Parent object of this pin
	int numConnections = 0; // number of wires that conencted to pin
	
	Pin();
	bool addWire(Object*); 
	void setIndex(int); 
	void setType(pinType);
	int getType();
	void setState(int);
	int getState();
	void setNumCon(int);
	void setPos(float, float);
	sf::Vector2f getPos();
};

Pin::Pin()
{
	cout << "Pin created" << endl;
	state = 2;
	numConnections = 0;
}
bool Pin::addWire(Object* wire)
{
	if (numConnections >= 5)
		return false;
	wires[numConnections] = wire;
	numConnections++;
	return true;
}

void Pin::setIndex(int i)
{
	index = i;
}

void Pin::setType(pinType t)
{
	type = t;
}

int Pin::getType()
{
	return type;
}

void Pin::setState(int s)
{
	state = s;
}

int Pin::getState()
{
	return state;
}

void Pin::setPos(float x, float y)
{
	pos.x = x;
	pos.y = y;
}

void Pin::setNumCon(int n)
{
	numConnections = n;
}

sf::Vector2f Pin::getPos()
{
	return pos;
}

