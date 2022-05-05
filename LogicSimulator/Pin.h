#pragma once
#include <SFML/Graphics.hpp>

class Pin
{
public:
	enum pinType { INPUT, OUTPUT }; //enum for pin type (input or output pin)
	enum pinState { HIGHZ, LOW, HIGH }; //enum for pin state
	int index; //Index of the pin for an element
	//First input pin has index 0, second input pin has index 1, output pin has index 2, so on…
	pinType type; //whether this pin is input or output
	bool isSrc[5]; //whether this pin is the starting point of the wire connected to it or the ending point
								//for that wire for every connection it has
	Pin* connectedTo[5]; //List of other pins this pin is connected to
	Object* wires[5]; //Wires connected to this pin
	int numConnections; //Number of connections on this pin
	sf::Vector2f pos; //Screen position of the pin
	pinState state; //Logic state of the signal on this pin 
};