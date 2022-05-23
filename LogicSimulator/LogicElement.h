#pragma once
#include "Object.h"
#include "Pin.h"

class LogicElement :public Object {

public:
	Pin pins[4]; // Pins of the element
	int numPins; // Number of pins of the logic element
	
	// Calculate the output of the logic element
	virtual int calculateState(LogicElement*)=0;
};