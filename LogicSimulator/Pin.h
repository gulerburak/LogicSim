#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>
using namespace std;

class _PinEnum
{
public:
	enum pinType { INPUT, OUTPUT }; //enum for pin type (input or output pin)
	enum pinState { LOW, HIGH, HIGHZ }; //enum for pin state
};

class Pin : public _PinEnum 
{
protected:
	int index; //Index of the pin for an element
	//First input pin has index 0, second input pin has index 1, output pin has index 2, so on…
	pinType type; //whether this pin is input or output
	pinState state; //Logic state of the signal on this pin 
	bool isSrc[5]; //whether this pin is the starting point of the wire connected to it or the ending point
								//for that wire for every connection it has
	int numConnections; //Number of connections on this pin
	sf::Vector2f pos; //Screen position of the pin
public:
	Pin* connectedTo[5]; //List of other pins this pin is connected to
	Object* wires[5]; //Wires connected to this pin
	
	Pin();

	void setIndex(int);	
	void setType(pinType);	
	int getType();	
	void setState(pinState);
	int getState();
	void setNumCon(int);	
	void setPos(float, float);
	sf::Vector2f getPos();
};

Pin::Pin()
{
	
	cout << "Pin created" << endl;
	state = HIGHZ;
	numConnections = 0;

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

void Pin::setState(pinState s)
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